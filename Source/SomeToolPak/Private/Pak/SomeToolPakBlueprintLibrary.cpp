#include "Pak/SomeToolPakBlueprintLibrary.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Dom/JsonObject.h"
#include "HAL/PlatformFileManager.h"
#include "IPlatformFilePak.h"
#include "Misc/App.h"
#include "Misc/FileHelper.h"
#include "Pak/SomeToolPakPrimaryAsset.h"
#include "Pak/SomeToolPakResourceRegistry.h"
#include "Misc/Paths.h"
#include "Misc/CoreDelegates.h"
#include "Misc/PackageName.h"
#include "Modules/ModuleManager.h"
#include "ShaderCodeLibrary.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY_STATIC(LogSomeToolPak, Log, All);

namespace
{
TMap<FString, FSomeToolMountedPakInfo> GSomeToolMountedPakInfo;
FCriticalSection GSomeToolMountedPakInfoLock;

FString NormalizeFilename(const FString& Path)
{
	FString Normalized = FPaths::ConvertRelativePathToFull(Path);
	FPaths::NormalizeFilename(Normalized);
	return Normalized;
}

FString NormalizeDirectory(const FString& Path)
{
	FString Normalized = FPaths::ConvertRelativePathToFull(Path);
	FPaths::NormalizeDirectoryName(Normalized);
	FPaths::MakeStandardFilename(Normalized);
	if (!Normalized.EndsWith(TEXT("/")))
	{
		Normalized += TEXT("/");
	}
	return Normalized;
}

FString NormalizeLongPackageRoot(const FString& Root)
{
	FString Normalized = Root;
	Normalized.TrimStartAndEndInline();
	Normalized.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Normalized.StartsWith(TEXT("/")))
	{
		Normalized.InsertAt(0, TEXT("/"));
	}
	if (!Normalized.EndsWith(TEXT("/")))
	{
		Normalized += TEXT("/");
	}
	return Normalized;
}

FString NormalizeLongPackagePath(const FString& Path)
{
	FString Normalized = Path;
	Normalized.TrimStartAndEndInline();
	Normalized.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Normalized.StartsWith(TEXT("/")))
	{
		Normalized.InsertAt(0, TEXT("/"));
	}
	while (Normalized.EndsWith(TEXT("/")) && Normalized.Len() > 1)
	{
		Normalized.LeftChopInline(1);
	}
	return Normalized;
}

FPakPlatformFile* GetPakPlatformFile()
{
	return static_cast<FPakPlatformFile*>(
		FPlatformFileManager::Get().FindPlatformFile(FPakPlatformFile::GetTypeName()));
}

FPakPlatformFile* EnsurePakPlatformFile(FString& OutError)
{
	if (FPakPlatformFile* ExistingPakPlatformFile = GetPakPlatformFile())
	{
		return ExistingPakPlatformFile;
	}

	FModuleManager::LoadModuleChecked<IModuleInterface>(TEXT("PakFile"));
	IPlatformFile* NewPlatformFile = FPlatformFileManager::Get().GetPlatformFile(FPakPlatformFile::GetTypeName());
	if (!NewPlatformFile)
	{
		OutError = TEXT("PakFile platform file module is unavailable.");
		return nullptr;
	}

	IPlatformFile& CurrentPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!NewPlatformFile->Initialize(&CurrentPlatformFile, TEXT("")))
	{
		OutError = TEXT("PakFile platform file failed to initialize.");
		return nullptr;
	}

	if (!FPlatformFileManager::Get().InsertPlatformFile(NewPlatformFile))
	{
		OutError = TEXT("PakFile platform file failed to enter the active platform file chain.");
		return nullptr;
	}

	FPakPlatformFile* PakPlatformFile = GetPakPlatformFile();
	if (!PakPlatformFile)
	{
		OutError = TEXT("PakFile platform file was inserted but cannot be found.");
		return nullptr;
	}

	return PakPlatformFile;
}

bool IsEngineMountedPak(const FString& NormalizedPakFilePath)
{
	FPakPlatformFile* PakPlatformFile = GetPakPlatformFile();
	if (!PakPlatformFile)
	{
		return false;
	}

	TArray<FString> MountedPakFilenames;
	PakPlatformFile->GetMountedPakFilenames(MountedPakFilenames);
	for (const FString& MountedPakFilename : MountedPakFilenames)
	{
		if (NormalizeFilename(MountedPakFilename).Equals(NormalizedPakFilePath, ESearchCase::IgnoreCase))
		{
			return true;
		}
	}

	return false;
}

bool FindTrackedPak(const FString& NormalizedPakFilePath, FSomeToolMountedPakInfo* OutInfo)
{
	FScopeLock Lock(&GSomeToolMountedPakInfoLock);
	if (const FSomeToolMountedPakInfo* Info = GSomeToolMountedPakInfo.Find(NormalizedPakFilePath))
	{
		if (OutInfo)
		{
			*OutInfo = *Info;
		}
		return true;
	}
	return false;
}

void TrackMountedPak(const FSomeToolMountedPakInfo& Info)
{
	FScopeLock Lock(&GSomeToolMountedPakInfoLock);
	GSomeToolMountedPakInfo.Add(Info.PakFilePath, Info);
}

void UntrackMountedPak(const FString& NormalizedPakFilePath)
{
	FScopeLock Lock(&GSomeToolMountedPakInfoLock);
	GSomeToolMountedPakInfo.Remove(NormalizedPakFilePath);
}

FString ResolveManifestSiblingFilePath(const FString& ManifestFilePath, const FString& FileName)
{
	if (FPaths::IsRelative(FileName))
	{
		return NormalizeFilename(FPaths::Combine(FPaths::GetPath(ManifestFilePath), FileName));
	}

	return NormalizeFilename(FileName);
}

void OpenProjectShaderLibraryForMountedPak(TArray<FString>* OutMessages)
{
	if (!FShaderCodeLibrary::IsEnabled())
	{
		if (OutMessages)
		{
			OutMessages->Add(TEXT("ShaderCodeLibrary is not enabled for this runtime."));
		}
		return;
	}

	const bool bOpened = FShaderCodeLibrary::OpenLibrary(FApp::GetProjectName(), FPaths::ProjectContentDir());
	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(
			TEXT("Project shader library refresh: %s"),
			bOpened ? TEXT("opened new shader archive") : TEXT("already open or not found")));
	}
}

void AddDefaultPakRootDirectories(TArray<FString>& OutDirectories)
{
	OutDirectories.Add(NormalizeDirectory(FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Paks"))));
	OutDirectories.Add(NormalizeDirectory(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Paks"))));
}

bool FindManifestByPakId(
	const FName PakId,
	const FString& PakRootDirectory,
	FString& OutManifestFilePath,
	FString& OutError,
	TArray<FString>* OutMessages = nullptr)
{
	OutManifestFilePath.Reset();
	OutError.Reset();

	if (PakId.IsNone())
	{
		OutError = TEXT("PakId is empty.");
		return false;
	}

	const FString ManifestFileName = PakId.ToString() + TEXT(".manifest.json");
	TArray<FString> SearchDirectories;
	if (!PakRootDirectory.IsEmpty())
	{
		SearchDirectories.Add(NormalizeDirectory(PakRootDirectory));
	}
	else
	{
		AddDefaultPakRootDirectories(SearchDirectories);
	}

	TArray<FString> TriedPaths;
	for (const FString& SearchDirectory : SearchDirectories)
	{
		const FString Candidate = NormalizeFilename(FPaths::Combine(SearchDirectory, ManifestFileName));
		TriedPaths.Add(Candidate);
		if (OutMessages)
		{
			OutMessages->Add(FString::Printf(TEXT("Try manifest: %s"), *Candidate));
		}
		if (FPaths::FileExists(Candidate))
		{
			OutManifestFilePath = Candidate;
			if (OutMessages)
			{
				OutMessages->Add(FString::Printf(TEXT("Manifest found: %s"), *OutManifestFilePath));
			}
			return true;
		}
	}

	OutError = FString::Printf(
		TEXT("Pak manifest was not found for PakId %s. Tried:\n%s"),
		*PakId.ToString(),
		*FString::Join(TriedPaths, TEXT("\n")));
	return false;
}
}

bool USomeToolPakBlueprintLibrary::ReadPakManifest(
	const FString& ManifestFilePath,
	FSomeToolPakManifestInfo& OutManifest,
	FString& OutError,
	TArray<FString>* OutMessages)
{
	OutManifest = FSomeToolPakManifestInfo();
	OutError.Reset();
	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("Read manifest: %s"), *ManifestFilePath));
	}

	if (ManifestFilePath.IsEmpty())
	{
		OutError = TEXT("ManifestFilePath is empty.");
		return false;
	}

	const FString NormalizedManifestFilePath = NormalizeFilename(ManifestFilePath);
	if (!FPaths::FileExists(NormalizedManifestFilePath))
	{
		OutError = FString::Printf(TEXT("Manifest file does not exist: %s"), *NormalizedManifestFilePath);
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	FString JsonText;
	if (!FFileHelper::LoadFileToString(JsonText, *NormalizedManifestFilePath))
	{
		OutError = FString::Printf(TEXT("Failed to read manifest file: %s"), *NormalizedManifestFilePath);
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	TSharedPtr<FJsonObject> ManifestObject;
	const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JsonText);
	if (!FJsonSerializer::Deserialize(Reader, ManifestObject) || !ManifestObject.IsValid())
	{
		OutError = FString::Printf(TEXT("Failed to parse manifest json: %s"), *NormalizedManifestFilePath);
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	FString PakIdString;
	ManifestObject->TryGetStringField(TEXT("PakId"), PakIdString);
	if (PakIdString.IsEmpty())
	{
		OutError = TEXT("Manifest missing PakId.");
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	OutManifest.ManifestFilePath = NormalizedManifestFilePath;
	OutManifest.ManifestDirectory = NormalizeDirectory(FPaths::GetPath(NormalizedManifestFilePath));
	OutManifest.PakId = FName(*PakIdString);
	OutManifest.Version = ManifestObject->GetIntegerField(TEXT("Version"));
	ManifestObject->TryGetStringField(TEXT("TargetPlatform"), OutManifest.TargetPlatform);
	ManifestObject->TryGetStringField(TEXT("PakFile"), OutManifest.PakFileName);
	ManifestObject->TryGetStringField(TEXT("ContentRoot"), OutManifest.ContentRoot);
	ManifestObject->TryGetStringField(TEXT("EntryAsset"), OutManifest.EntryAsset);
	ManifestObject->TryGetStringField(TEXT("EntryMap"), OutManifest.EntryMap);
	ManifestObject->TryGetStringField(TEXT("ResourceRegistry"), OutManifest.ResourceRegistry);

	if (OutManifest.PakFileName.IsEmpty())
	{
		OutManifest.PakFileName = PakIdString + TEXT(".pak");
	}
	OutManifest.PakFilePath = ResolveManifestSiblingFilePath(NormalizedManifestFilePath, OutManifest.PakFileName);
	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("Manifest PakId: %s"), *OutManifest.PakId.ToString()));
		OutMessages->Add(FString::Printf(TEXT("Manifest PakFile: %s"), *OutManifest.PakFilePath));
		OutMessages->Add(FString::Printf(TEXT("Manifest ContentRoot: %s"), *OutManifest.ContentRoot));
		OutMessages->Add(FString::Printf(TEXT("Manifest EntryMap: %s"), *OutManifest.EntryMap));
	}

	const TArray<TSharedPtr<FJsonValue>>* DependentPakIdValues = nullptr;
	if (ManifestObject->TryGetArrayField(TEXT("DependentPakIds"), DependentPakIdValues))
	{
		for (const TSharedPtr<FJsonValue>& Value : *DependentPakIdValues)
		{
			FString DependentPakId;
			if (Value.IsValid() && Value->TryGetString(DependentPakId) && !DependentPakId.IsEmpty())
			{
				OutManifest.DependentPakIds.Add(FName(*DependentPakId));
			}
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* AssetValues = nullptr;
	if (ManifestObject->TryGetArrayField(TEXT("Assets"), AssetValues))
	{
		for (const TSharedPtr<FJsonValue>& Value : *AssetValues)
		{
			FString AssetPath;
			if (Value.IsValid() && Value->TryGetString(AssetPath) && !AssetPath.IsEmpty())
			{
				OutManifest.Assets.Add(AssetPath);
			}
		}
	}

	return true;
}

bool USomeToolPakBlueprintLibrary::MountPakByManifest(
	const FString& ManifestFilePath,
	const int32 PakOrder,
	TArray<FString>& OutAssetPaths,
	FSomeToolPakManifestInfo& OutManifest,
	FString& OutError,
	TArray<FString>* OutMessages)
{
	OutAssetPaths.Reset();
	OutError.Reset();

	if (!ReadPakManifest(ManifestFilePath, OutManifest, OutError, OutMessages))
	{
		return false;
	}

	FSomeToolPakMountOptions Options;
	Options.PakFilePath = OutManifest.PakFilePath;
	Options.PakOrder = PakOrder;
	Options.bScanAssetRegistry = true;
	Options.bForceAssetRegistryRescan = true;
	Options.AssetRegistryScanPaths.Add(TEXT("/Game"));

	if (!MountPak(Options, OutError, OutMessages))
	{
		return false;
	}
	OpenProjectShaderLibraryForMountedPak(OutMessages);

	FString AssetRegistryError;
	if (!GetPakAssetPaths(TEXT("/Game"), true, OutAssetPaths, AssetRegistryError))
	{
		OutAssetPaths = OutManifest.Assets;
		OutError = AssetRegistryError;
		if (OutMessages)
		{
			OutMessages->Add(FString::Printf(TEXT("AssetRegistry scan fallback to manifest assets. Error: %s"), *AssetRegistryError));
			OutMessages->Add(FString::Printf(TEXT("Manifest assets: %d"), OutAssetPaths.Num()));
		}
		return true;
	}

	if (OutAssetPaths.Num() == 0)
	{
		OutAssetPaths = OutManifest.Assets;
		if (OutMessages)
		{
			OutMessages->Add(FString::Printf(TEXT("AssetRegistry returned 0 assets. Fallback to manifest assets: %d"), OutAssetPaths.Num()));
		}
	}
	else if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("AssetRegistry /Game assets: %d"), OutAssetPaths.Num()));
	}

	return true;
}

bool USomeToolPakBlueprintLibrary::MountPakById(
	const FName PakId,
	const int32 PakOrder,
	TArray<FString>& OutAssetPaths,
	FSomeToolPakManifestInfo& OutManifest,
	FString& OutError,
	const FString& PakRootDirectory,
	TArray<FString>* OutMessages)
{
	OutAssetPaths.Reset();
	OutManifest = FSomeToolPakManifestInfo();
	OutError.Reset();
	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("Mount by PakId: %s"), *PakId.ToString()));
	}

	FString ManifestFilePath;
	if (!FindManifestByPakId(PakId, PakRootDirectory, ManifestFilePath, OutError, OutMessages))
	{
		return false;
	}

	if (!MountPakByManifest(ManifestFilePath, PakOrder, OutAssetPaths, OutManifest, OutError, OutMessages))
	{
		return false;
	}

	if (OutManifest.PakId != PakId)
	{
		OutError = FString::Printf(
			TEXT("PakId mismatch. Requested %s but manifest contains %s."),
			*PakId.ToString(),
			*OutManifest.PakId.ToString());
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	if (OutMessages)
	{
		OutMessages->Add(TEXT("Mount by PakId succeeded."));
	}
	return true;
}

bool USomeToolPakBlueprintLibrary::MountGamePak(
	const FName PakId,
	USomeToolPakPrimaryAsset*& OutPakEntry,
	TArray<FString>& OutAssetPaths,
	FString& OutError,
	TArray<FString>& OutMessages)
{
	OutPakEntry = nullptr;
	OutAssetPaths.Reset();
	OutError.Reset();
	OutMessages.Reset();

	FSomeToolPakManifestInfo Manifest;
	const bool bMounted = MountPakById(PakId, 100, OutAssetPaths, Manifest, OutError, FString(), &OutMessages);
	if (!bMounted)
	{
		UE_LOG(LogSomeToolPak, Warning, TEXT("Mount Game Pak failed. PakId=%s Error=%s"), *PakId.ToString(), *OutError);
		for (const FString& Message : OutMessages)
		{
			UE_LOG(LogSomeToolPak, Verbose, TEXT("%s"), *Message);
		}
		return false;
	}

	OutPakEntry = LoadObject<USomeToolPakPrimaryAsset>(nullptr, *Manifest.EntryAsset);
	if (!OutPakEntry)
	{
		OutError = FString::Printf(TEXT("Pak mounted but failed to load entry asset: %s"), *Manifest.EntryAsset);
		OutMessages.Add(OutError);
		UE_LOG(LogSomeToolPak, Warning, TEXT("Mount Game Pak loaded pak but failed to load entry asset. PakId=%s EntryAsset=%s"), *PakId.ToString(), *Manifest.EntryAsset);
		return false;
	}

	OutMessages.Add(FString::Printf(TEXT("Pak entry loaded: %s"), *OutPakEntry->GetPathName()));
	UE_LOG(LogSomeToolPak, Log, TEXT("Mount Game Pak succeeded. PakId=%s EntryAsset=%s Assets=%d"), *PakId.ToString(), *OutPakEntry->GetPathName(), OutAssetPaths.Num());
	return true;
}

USomeToolPakPrimaryAsset* USomeToolPakBlueprintLibrary::MountGamePakEntry(const FName PakId)
{
	USomeToolPakPrimaryAsset* PakEntry = nullptr;
	TArray<FString> AssetPaths;
	TArray<FString> Messages;
	FString Error;
	MountGamePak(PakId, PakEntry, AssetPaths, Error, Messages);
	return PakEntry;
}

bool USomeToolPakBlueprintLibrary::UnmountGamePak(const FName PakId, FString& OutError)
{
	OutError.Reset();

	FString ManifestFilePath;
	if (!FindManifestByPakId(PakId, FString(), ManifestFilePath, OutError))
	{
		return false;
	}

	FSomeToolPakManifestInfo Manifest;
	if (!ReadPakManifest(ManifestFilePath, Manifest, OutError))
	{
		return false;
	}

	if (Manifest.PakId != PakId)
	{
		OutError = FString::Printf(
			TEXT("PakId mismatch. Requested %s but manifest contains %s."),
			*PakId.ToString(),
			*Manifest.PakId.ToString());
		return false;
	}

	return UnmountPak(Manifest.PakFilePath, OutError);
}

bool USomeToolPakBlueprintLibrary::IsGamePakMounted(const FName PakId)
{
	FString Error;
	FString ManifestFilePath;
	if (!FindManifestByPakId(PakId, FString(), ManifestFilePath, Error))
	{
		return false;
	}

	FSomeToolPakManifestInfo Manifest;
	if (!ReadPakManifest(ManifestFilePath, Manifest, Error))
	{
		return false;
	}

	return Manifest.PakId == PakId && IsPakMounted(Manifest.PakFilePath);
}

bool USomeToolPakBlueprintLibrary::MountPak(
	const FSomeToolPakMountOptions& Options,
	FString& OutError,
	TArray<FString>* OutMessages)
{
	OutError.Reset();
	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("Mount pak file: %s"), *Options.PakFilePath));
	}

	if (Options.PakFilePath.IsEmpty())
	{
		OutError = TEXT("PakFilePath is empty.");
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	const FString NormalizedPakFilePath = NormalizeFilename(Options.PakFilePath);
	if (!FPaths::FileExists(NormalizedPakFilePath))
	{
		OutError = FString::Printf(TEXT("Pak file does not exist: %s"), *NormalizedPakFilePath);
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}
	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("Pak file exists: %s"), *NormalizedPakFilePath));
	}

	if (IsEngineMountedPak(NormalizedPakFilePath))
	{
		if (OutMessages)
		{
			OutMessages->Add(TEXT("Pak is already mounted."));
		}
		return true;
	}

	FPakPlatformFile* PakPlatformFile = EnsurePakPlatformFile(OutError);
	if (!PakPlatformFile)
	{
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	const int32 PakOrder = Options.PakOrder == -1 ? 0 : Options.PakOrder;

	const FString NormalizedPakMountPoint = Options.PakMountPoint.IsEmpty()
		? FString()
		: NormalizeDirectory(Options.PakMountPoint);

	IPakFile* MountedPakFile = nullptr;
	if (NormalizedPakMountPoint.IsEmpty() && FCoreDelegates::MountPak.IsBound())
	{
		MountedPakFile = FCoreDelegates::MountPak.Execute(NormalizedPakFilePath, PakOrder);
	}
	else if (PakPlatformFile->Mount(
		*NormalizedPakFilePath,
		static_cast<uint32>(PakOrder),
		NormalizedPakMountPoint.IsEmpty() ? nullptr : *NormalizedPakMountPoint))
	{
		MountedPakFile = nullptr;
	}

	if (!MountedPakFile && !IsEngineMountedPak(NormalizedPakFilePath))
	{
		OutError = FString::Printf(TEXT("Failed to mount pak: %s"), *NormalizedPakFilePath);
		if (OutMessages)
		{
			OutMessages->Add(OutError);
		}
		return false;
	}

	FSomeToolMountedPakInfo MountedInfo;
	MountedInfo.PakFilePath = NormalizedPakFilePath;
	MountedInfo.PakMountPoint = MountedPakFile ? MountedPakFile->PakGetMountPoint() : NormalizedPakMountPoint;
	MountedInfo.PakOrder = PakOrder;
	TrackMountedPak(MountedInfo);

	if (Options.bRegisterPackageMountPoint)
	{
		if (!RegisterPakPackageMountPoint(Options.LongPackageRoot, Options.ContentRootPath, OutError))
		{
			UnmountPak(NormalizedPakFilePath, OutError);
			if (OutMessages)
			{
				OutMessages->Add(OutError);
			}
			return false;
		}
	}

	if (Options.bScanAssetRegistry)
	{
		TArray<FString> ScanPaths = Options.AssetRegistryScanPaths;
		if (ScanPaths.Num() == 0 && !Options.LongPackageRoot.IsEmpty())
		{
			ScanPaths.Add(Options.LongPackageRoot);
		}

		for (const FString& ScanPath : ScanPaths)
		{
			if (!ScanPakContentPath(ScanPath, Options.bForceAssetRegistryRescan, OutError))
			{
				if (OutMessages)
				{
					OutMessages->Add(FString::Printf(TEXT("Scan failed: %s Error: %s"), *ScanPath, *OutError));
				}
				return false;
			}
			if (OutMessages)
			{
				OutMessages->Add(FString::Printf(TEXT("Scan path succeeded: %s"), *ScanPath));
			}
		}
	}

	if (OutMessages)
	{
		OutMessages->Add(FString::Printf(TEXT("Mounted pak: %s"), *NormalizedPakFilePath));
	}
	UE_LOG(LogSomeToolPak, Log, TEXT("Mounted pak: %s"), *NormalizedPakFilePath);
	return true;
}

bool USomeToolPakBlueprintLibrary::MountPakFile(
	const FString& PakFilePath,
	const int32 PakOrder,
	const FString& PakMountPoint,
	FString& OutError)
{
	FSomeToolPakMountOptions Options;
	Options.PakFilePath = PakFilePath;
	Options.PakOrder = PakOrder;
	Options.PakMountPoint = PakMountPoint;
	Options.bScanAssetRegistry = false;
	return MountPak(Options, OutError);
}

bool USomeToolPakBlueprintLibrary::UnmountPak(const FString& PakFilePath, FString& OutError)
{
	OutError.Reset();

	if (PakFilePath.IsEmpty())
	{
		OutError = TEXT("PakFilePath is empty.");
		return false;
	}

	const FString NormalizedPakFilePath = NormalizeFilename(PakFilePath);
	FPakPlatformFile* PakPlatformFile = GetPakPlatformFile();
	if (!PakPlatformFile)
	{
		OutError = TEXT("PakFile platform file is not active.");
		return false;
	}

	if (!IsEngineMountedPak(NormalizedPakFilePath))
	{
		UntrackMountedPak(NormalizedPakFilePath);
		return true;
	}

	const bool bUnmounted = FCoreDelegates::OnUnmountPak.IsBound()
		? FCoreDelegates::OnUnmountPak.Execute(NormalizedPakFilePath)
		: PakPlatformFile->Unmount(*NormalizedPakFilePath);

	if (!bUnmounted)
	{
		OutError = FString::Printf(TEXT("Failed to unmount pak: %s"), *NormalizedPakFilePath);
		return false;
	}

	UntrackMountedPak(NormalizedPakFilePath);
	UE_LOG(LogSomeToolPak, Log, TEXT("Unmounted pak: %s"), *NormalizedPakFilePath);
	return true;
}

bool USomeToolPakBlueprintLibrary::IsPakMounted(const FString& PakFilePath)
{
	if (PakFilePath.IsEmpty())
	{
		return false;
	}

	return IsEngineMountedPak(NormalizeFilename(PakFilePath));
}

void USomeToolPakBlueprintLibrary::GetMountedPakFiles(TArray<FString>& OutPakFilePaths)
{
	OutPakFilePaths.Reset();

	FPakPlatformFile* PakPlatformFile = GetPakPlatformFile();
	if (!PakPlatformFile)
	{
		return;
	}

	TArray<FString> MountedPakFilenames;
	PakPlatformFile->GetMountedPakFilenames(MountedPakFilenames);
	for (const FString& MountedPakFilename : MountedPakFilenames)
	{
		OutPakFilePaths.Add(NormalizeFilename(MountedPakFilename));
	}
}

void USomeToolPakBlueprintLibrary::GetMountedPakInfo(TArray<FSomeToolMountedPakInfo>& OutMountedPakInfo)
{
	OutMountedPakInfo.Reset();

	{
		FScopeLock Lock(&GSomeToolMountedPakInfoLock);
		for (const TPair<FString, FSomeToolMountedPakInfo>& Pair : GSomeToolMountedPakInfo)
		{
			if (IsEngineMountedPak(Pair.Key))
			{
				OutMountedPakInfo.Add(Pair.Value);
			}
		}
	}
}

bool USomeToolPakBlueprintLibrary::RegisterPakPackageMountPoint(
	const FString& LongPackageRoot,
	const FString& ContentRootPath,
	FString& OutError)
{
	OutError.Reset();

	if (LongPackageRoot.IsEmpty())
	{
		OutError = TEXT("LongPackageRoot is empty.");
		return false;
	}
	if (ContentRootPath.IsEmpty())
	{
		OutError = TEXT("ContentRootPath is empty.");
		return false;
	}

	const FString NormalizedLongPackageRoot = NormalizeLongPackageRoot(LongPackageRoot);
	const FString NormalizedContentRootPath = NormalizeDirectory(ContentRootPath);
	FPackageName::RegisterMountPoint(NormalizedLongPackageRoot, NormalizedContentRootPath);
	return true;
}

bool USomeToolPakBlueprintLibrary::UnregisterPakPackageMountPoint(
	const FString& LongPackageRoot,
	const FString& ContentRootPath,
	FString& OutError)
{
	OutError.Reset();

	if (LongPackageRoot.IsEmpty())
	{
		OutError = TEXT("LongPackageRoot is empty.");
		return false;
	}
	if (ContentRootPath.IsEmpty())
	{
		OutError = TEXT("ContentRootPath is empty.");
		return false;
	}

	const FString NormalizedLongPackageRoot = NormalizeLongPackageRoot(LongPackageRoot);
	const FString NormalizedContentRootPath = NormalizeDirectory(ContentRootPath);
	FPackageName::UnRegisterMountPoint(NormalizedLongPackageRoot, NormalizedContentRootPath);
	return true;
}

bool USomeToolPakBlueprintLibrary::DoesPackageMountPointExist(const FString& LongPackageRoot)
{
	if (LongPackageRoot.IsEmpty())
	{
		return false;
	}

	return FPackageName::MountPointExists(NormalizeLongPackageRoot(LongPackageRoot));
}

bool USomeToolPakBlueprintLibrary::ScanPakContentPath(
	const FString& LongPackagePath,
	const bool bForceRescan,
	FString& OutError)
{
	OutError.Reset();

	if (LongPackagePath.IsEmpty())
	{
		OutError = TEXT("LongPackagePath is empty.");
		return false;
	}

	const FString NormalizedLongPackagePath = NormalizeLongPackagePath(LongPackagePath);
	const FAssetRegistryModule* AssetRegistryModule =
		FModuleManager::LoadModulePtr<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	if (!AssetRegistryModule || !AssetRegistryModule->IsValid())
	{
		OutError = TEXT("AssetRegistry module is unavailable.");
		return false;
	}

	TArray<FString> PathsToScan;
	PathsToScan.Add(NormalizedLongPackagePath);
	AssetRegistryModule->Get().ScanPathsSynchronous(PathsToScan, bForceRescan);
	return true;
}

bool USomeToolPakBlueprintLibrary::GetPakAssetPaths(
	const FString& LongPackagePath,
	const bool bRecursive,
	TArray<FString>& OutAssetPaths,
	FString& OutError)
{
	OutAssetPaths.Reset();
	OutError.Reset();

	if (LongPackagePath.IsEmpty())
	{
		OutError = TEXT("LongPackagePath is empty.");
		return false;
	}

	const FAssetRegistryModule* AssetRegistryModule =
		FModuleManager::LoadModulePtr<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	if (!AssetRegistryModule || !AssetRegistryModule->IsValid())
	{
		OutError = TEXT("AssetRegistry module is unavailable.");
		return false;
	}

	TArray<FAssetData> AssetDataList;
	const FString NormalizedLongPackagePath = NormalizeLongPackagePath(LongPackagePath);
	AssetRegistryModule->Get().GetAssetsByPath(
		FName(*NormalizedLongPackagePath),
		AssetDataList,
		bRecursive,
		true);

	TSet<FString> UniqueAssetPaths;
	for (const FAssetData& AssetData : AssetDataList)
	{
		UniqueAssetPaths.Add(AssetData.GetSoftObjectPath().ToString());
	}

	for (const FString& AssetPath : UniqueAssetPaths)
	{
		OutAssetPaths.Add(AssetPath);
	}
	OutAssetPaths.Sort();
	return true;
}

bool USomeToolPakBlueprintLibrary::GetPakPackageNames(
	const FString& LongPackagePath,
	const bool bRecursive,
	TArray<FString>& OutPackageNames,
	FString& OutError)
{
	OutPackageNames.Reset();
	OutError.Reset();

	if (LongPackagePath.IsEmpty())
	{
		OutError = TEXT("LongPackagePath is empty.");
		return false;
	}

	const FAssetRegistryModule* AssetRegistryModule =
		FModuleManager::LoadModulePtr<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	if (!AssetRegistryModule || !AssetRegistryModule->IsValid())
	{
		OutError = TEXT("AssetRegistry module is unavailable.");
		return false;
	}

	TArray<FAssetData> AssetDataList;
	const FString NormalizedLongPackagePath = NormalizeLongPackagePath(LongPackagePath);
	AssetRegistryModule->Get().GetAssetsByPath(
		FName(*NormalizedLongPackagePath),
		AssetDataList,
		bRecursive,
		true);

	TSet<FString> UniquePackageNames;
	for (const FAssetData& AssetData : AssetDataList)
	{
		UniquePackageNames.Add(AssetData.PackageName.ToString());
	}

	for (const FString& PackageName : UniquePackageNames)
	{
		OutPackageNames.Add(PackageName);
	}
	OutPackageNames.Sort();
	return true;
}

bool USomeToolPakBlueprintLibrary::GetPakFilePaths(
	const FString& PakFilePath,
	TArray<FString>& OutFilePaths,
	FString& OutError)
{
	OutFilePaths.Reset();
	OutError.Reset();

	if (PakFilePath.IsEmpty())
	{
		OutError = TEXT("PakFilePath is empty.");
		return false;
	}

	const FString NormalizedPakFilePath = NormalizeFilename(PakFilePath);
	if (!FPaths::FileExists(NormalizedPakFilePath))
	{
		OutError = FString::Printf(TEXT("Pak file does not exist: %s"), *NormalizedPakFilePath);
		return false;
	}

	IPlatformFile& CurrentPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FPakPlatformFile* PakPlatformFile = GetPakPlatformFile();
	IPlatformFile* LowerLevelPlatformFile = PakPlatformFile ? PakPlatformFile->GetLowerLevel() : &CurrentPlatformFile;
	if (!LowerLevelPlatformFile)
	{
		LowerLevelPlatformFile = &CurrentPlatformFile;
	}

	TRefCountPtr<FPakFile> PakFile = new FPakFile(LowerLevelPlatformFile, *NormalizedPakFilePath, false);
	if (!PakFile || !PakFile->IsValid())
	{
		OutError = FString::Printf(TEXT("Failed to read pak index: %s"), *NormalizedPakFilePath);
		return false;
	}

	TSet<FString> UniqueFilePaths;
	for (FPakFile::FFilenameIterator It(*PakFile); It; ++It)
	{
		UniqueFilePaths.Add(It.Filename());
	}

	for (const FString& FilePath : UniqueFilePaths)
	{
		OutFilePaths.Add(FilePath);
	}
	OutFilePaths.Sort();
	return true;
}

namespace
{
FString MakeResourceId(const FName Namespace, const FName Name)
{
	if (Namespace.IsNone())
	{
		return Name.ToString();
	}
	if (Name.IsNone())
	{
		return Namespace.ToString();
	}
	return FString::Printf(TEXT("%s.%s"), *Namespace.ToString(), *Name.ToString());
}

void AddRegisteredObjectPath(
	const FName Namespace,
	const FName Name,
	const TSoftObjectPtr<UObject>& Asset,
	TArray<FSomeToolPakRegisteredResourcePath>& OutResources)
{
	if (Asset.IsNull())
	{
		return;
	}

	FSomeToolPakRegisteredResourcePath Resource;
	Resource.Name = Name;
	Resource.Namespace = Namespace;
	Resource.ResourceId = MakeResourceId(Namespace, Name);
	Resource.Path = Asset.ToString();
	Resource.bIsClass = false;
	OutResources.Add(Resource);
}

void AddRegisteredClassPath(
	const FName Namespace,
	const FName Name,
	const TSoftClassPtr<UObject>& Class,
	TArray<FSomeToolPakRegisteredResourcePath>& OutResources)
{
	if (Class.IsNull())
	{
		return;
	}

	FSomeToolPakRegisteredResourcePath Resource;
	Resource.Name = Name;
	Resource.Namespace = Namespace;
	Resource.ResourceId = MakeResourceId(Namespace, Name);
	Resource.Path = Class.ToString();
	Resource.bIsClass = true;
	OutResources.Add(Resource);
}

void AddRegistryResources(
	const USomeToolPakResourceRegistry& ResourceRegistry,
	TArray<FSomeToolPakRegisteredResourcePath>& OutResources)
{
	for (const TPair<FName, TSoftObjectPtr<UObject>>& Entry : ResourceRegistry.SoftObjects)
	{
		AddRegisteredObjectPath(ResourceRegistry.Namespace, Entry.Key, Entry.Value, OutResources);
	}
	for (const TPair<FName, TSoftClassPtr<UObject>>& Entry : ResourceRegistry.SoftClasses)
	{
		AddRegisteredClassPath(ResourceRegistry.Namespace, Entry.Key, Entry.Value, OutResources);
	}
}

void ValidateObjectEntries(
	const TMap<FName, TSoftObjectPtr<UObject>>& Entries,
	const FString& SectionName,
	TSet<FName>& UsedNames,
	TArray<FString>& OutMessages)
{
	int32 Index = 0;
	for (const TPair<FName, TSoftObjectPtr<UObject>>& Entry : Entries)
	{
		if (Entry.Key.IsNone())
		{
			OutMessages.Add(FString::Printf(TEXT("%s[%d] has an empty Name."), *SectionName, Index));
		}
		else if (UsedNames.Contains(Entry.Key))
		{
			OutMessages.Add(FString::Printf(TEXT("%s[%d] has duplicate Name: %s."), *SectionName, Index, *Entry.Key.ToString()));
		}
		else
		{
			UsedNames.Add(Entry.Key);
		}

		if (Entry.Value.IsNull())
		{
			OutMessages.Add(FString::Printf(TEXT("%s[%d] has an empty Asset."), *SectionName, Index));
		}

		++Index;
	}
}

void ValidateClassEntries(
	const TMap<FName, TSoftClassPtr<UObject>>& Entries,
	const FString& SectionName,
	TSet<FName>& UsedNames,
	TArray<FString>& OutMessages)
{
	int32 Index = 0;
	for (const TPair<FName, TSoftClassPtr<UObject>>& Entry : Entries)
	{
		if (Entry.Key.IsNone())
		{
			OutMessages.Add(FString::Printf(TEXT("%s[%d] has an empty Name."), *SectionName, Index));
		}
		else if (UsedNames.Contains(Entry.Key))
		{
			OutMessages.Add(FString::Printf(TEXT("%s[%d] has duplicate Name: %s."), *SectionName, Index, *Entry.Key.ToString()));
		}
		else
		{
			UsedNames.Add(Entry.Key);
		}

		if (Entry.Value.IsNull())
		{
			OutMessages.Add(FString::Printf(TEXT("%s[%d] has an empty Class."), *SectionName, Index));
		}

		++Index;
	}
}
}

bool USomeToolPakBlueprintLibrary::GetRegisteredPakResources(
	const USomeToolPakResourceRegistry* ResourceRegistry,
	TArray<FSomeToolPakRegisteredResourcePath>& OutResources,
	FString& OutError)
{
	OutResources.Reset();
	OutError.Reset();

	if (!ResourceRegistry)
	{
		OutError = TEXT("ResourceRegistry is null.");
		return false;
	}

	AddRegistryResources(*ResourceRegistry, OutResources);
	OutResources.Sort([](
		const FSomeToolPakRegisteredResourcePath& Left,
		const FSomeToolPakRegisteredResourcePath& Right)
	{
		return Left.Path < Right.Path;
	});
	return true;
}

bool USomeToolPakBlueprintLibrary::GetPakEntryRegisteredResources(
	const USomeToolPakPrimaryAsset* PakEntry,
	const bool bIncludeEntryMap,
	TArray<FSomeToolPakRegisteredResourcePath>& OutResources,
	FString& OutError)
{
	OutResources.Reset();
	OutError.Reset();

	if (!PakEntry)
	{
		OutError = TEXT("PakEntry is null.");
		return false;
	}

	if (bIncludeEntryMap && !PakEntry->EntryMap.IsNull())
	{
		FSomeToolPakRegisteredResourcePath EntryMapResource;
		EntryMapResource.Name = TEXT("EntryMap");
		EntryMapResource.ResourceId = TEXT("EntryMap");
		EntryMapResource.Path = PakEntry->EntryMap.ToString();
		EntryMapResource.bIsClass = false;
		OutResources.Add(EntryMapResource);
	}

	USomeToolPakResourceRegistry* ResourceRegistry = PakEntry->ResourceRegistry.LoadSynchronous();
	if (ResourceRegistry)
	{
		AddRegistryResources(*ResourceRegistry, OutResources);
	}

	OutResources.Sort([](
		const FSomeToolPakRegisteredResourcePath& Left,
		const FSomeToolPakRegisteredResourcePath& Right)
	{
		return Left.Path < Right.Path;
	});
	return true;
}

bool USomeToolPakBlueprintLibrary::FindRegisteredSoftObject(
	const USomeToolPakResourceRegistry* ResourceRegistry,
	const FName Name,
	TSoftObjectPtr<UObject>& OutAsset,
	FString& OutError)
{
	OutAsset.Reset();
	OutError.Reset();

	if (!ResourceRegistry)
	{
		OutError = TEXT("ResourceRegistry is null.");
		return false;
	}
	if (Name.IsNone())
	{
		OutError = TEXT("Name is empty.");
		return false;
	}

	if (const TSoftObjectPtr<UObject>* Asset = ResourceRegistry->SoftObjects.Find(Name))
	{
		if (Asset->IsNull())
		{
			OutError = FString::Printf(TEXT("Registered soft object is empty: %s."), *Name.ToString());
			return false;
		}

		OutAsset = *Asset;
		return true;
	}

	OutError = FString::Printf(TEXT("Registered soft object was not found: %s."), *Name.ToString());
	return false;
}

bool USomeToolPakBlueprintLibrary::FindRegisteredSoftClass(
	const USomeToolPakResourceRegistry* ResourceRegistry,
	const FName Name,
	TSoftClassPtr<UObject>& OutClass,
	FString& OutError)
{
	OutClass.Reset();
	OutError.Reset();

	if (!ResourceRegistry)
	{
		OutError = TEXT("ResourceRegistry is null.");
		return false;
	}
	if (Name.IsNone())
	{
		OutError = TEXT("Name is empty.");
		return false;
	}

	if (const TSoftClassPtr<UObject>* Class = ResourceRegistry->SoftClasses.Find(Name))
	{
		if (Class->IsNull())
		{
			OutError = FString::Printf(TEXT("Registered soft class is empty: %s."), *Name.ToString());
			return false;
		}

		OutClass = *Class;
		return true;
	}

	OutError = FString::Printf(TEXT("Registered soft class was not found: %s."), *Name.ToString());
	return false;
}

bool USomeToolPakBlueprintLibrary::FindPakEntrySoftObject(
	const USomeToolPakPrimaryAsset* PakEntry,
	const FName Name,
	TSoftObjectPtr<UObject>& OutAsset,
	FString& OutError)
{
	OutAsset.Reset();
	OutError.Reset();

	if (!PakEntry)
	{
		OutError = TEXT("PakEntry is null.");
		return false;
	}

	USomeToolPakResourceRegistry* ResourceRegistry = PakEntry->ResourceRegistry.LoadSynchronous();
	if (!ResourceRegistry)
	{
		OutError = FString::Printf(TEXT("ResourceRegistry failed to load: %s."), *PakEntry->ResourceRegistry.ToString());
		return false;
	}

	return FindRegisteredSoftObject(ResourceRegistry, Name, OutAsset, OutError);
}

bool USomeToolPakBlueprintLibrary::FindPakEntrySoftClass(
	const USomeToolPakPrimaryAsset* PakEntry,
	const FName Name,
	TSoftClassPtr<UObject>& OutClass,
	FString& OutError)
{
	OutClass.Reset();
	OutError.Reset();

	if (!PakEntry)
	{
		OutError = TEXT("PakEntry is null.");
		return false;
	}

	USomeToolPakResourceRegistry* ResourceRegistry = PakEntry->ResourceRegistry.LoadSynchronous();
	if (!ResourceRegistry)
	{
		OutError = FString::Printf(TEXT("ResourceRegistry failed to load: %s."), *PakEntry->ResourceRegistry.ToString());
		return false;
	}

	return FindRegisteredSoftClass(ResourceRegistry, Name, OutClass, OutError);
}

bool USomeToolPakBlueprintLibrary::ValidatePakResourceRegistry(
	const USomeToolPakResourceRegistry* ResourceRegistry,
	TArray<FString>& OutMessages)
{
	OutMessages.Reset();

	if (!ResourceRegistry)
	{
		OutMessages.Add(TEXT("ResourceRegistry is null."));
		return false;
	}

	TSet<FName> UsedNames;
	if (ResourceRegistry->Namespace.IsNone())
	{
		OutMessages.Add(TEXT("Namespace is empty."));
	}
	ValidateObjectEntries(ResourceRegistry->SoftObjects, TEXT("SoftObjects"), UsedNames, OutMessages);
	ValidateClassEntries(ResourceRegistry->SoftClasses, TEXT("SoftClasses"), UsedNames, OutMessages);

	return OutMessages.Num() == 0;
}

bool USomeToolPakBlueprintLibrary::ValidatePakEntry(
	const USomeToolPakPrimaryAsset* PakEntry,
	TArray<FString>& OutMessages)
{
	OutMessages.Reset();

	if (!PakEntry)
	{
		OutMessages.Add(TEXT("PakEntry is null."));
		return false;
	}

	if (PakEntry->EntryMap.IsNull())
	{
		OutMessages.Add(TEXT("EntryMap is empty."));
	}

	if (PakEntry->ResourceRegistry.IsNull())
	{
		OutMessages.Add(TEXT("ResourceRegistry is empty."));
	}
	else
	{
		USomeToolPakResourceRegistry* ResourceRegistry = PakEntry->ResourceRegistry.LoadSynchronous();
		if (!ResourceRegistry)
		{
			OutMessages.Add(FString::Printf(TEXT("ResourceRegistry failed to load: %s."), *PakEntry->ResourceRegistry.ToString()));
		}
		else
		{
			TArray<FString> RegistryMessages;
			ValidatePakResourceRegistry(ResourceRegistry, RegistryMessages);
			for (const FString& Message : RegistryMessages)
			{
				OutMessages.Add(FString::Printf(TEXT("ResourceRegistry: %s"), *Message));
			}
		}
	}

	return OutMessages.Num() == 0;
}
