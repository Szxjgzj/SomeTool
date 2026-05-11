#include "Pak/SomeToolPakManifestBuilder.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Dom/JsonObject.h"
#include "HAL/PlatformProcess.h"
#include "Misc/App.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Pak/SomeToolPakEditorBlueprintLibrary.h"
#include "Pak/SomeToolPakPrimaryAsset.h"
#include "Pak/SomeToolPakResourceRegistry.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"

namespace
{
FString GetLongPackageNameFromAssetPath(const FString& AssetPath);

FString NormalizeLongPackagePath(FString Path)
{
	Path.TrimStartAndEndInline();
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Path.StartsWith(TEXT("/")))
	{
		Path.InsertAt(0, TEXT("/"));
	}
	while (Path.EndsWith(TEXT("/")) && Path.Len() > 1)
	{
		Path.LeftChopInline(1);
	}
	return Path;
}

FString MakeSoftObjectPathString(const FSoftObjectPath& Path)
{
	return Path.IsNull() ? FString() : Path.ToString();
}

void AddUniqueAssetPath(
	const FString& AssetPath,
	TArray<FString>& AssetPaths,
	TSet<FString>& UniqueAssetPaths)
{
	if (!AssetPath.IsEmpty() && !UniqueAssetPaths.Contains(AssetPath))
	{
		UniqueAssetPaths.Add(AssetPath);
		AssetPaths.Add(AssetPath);
	}
}

bool DoesAssetExist(const FString& AssetPath)
{
	if (AssetPath.IsEmpty())
	{
		return false;
	}

	const FAssetRegistryModule* AssetRegistryModule =
		FModuleManager::LoadModulePtr<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	if (!AssetRegistryModule || !AssetRegistryModule->IsValid())
	{
		return false;
	}

	return AssetRegistryModule->Get().GetAssetByObjectPath(FSoftObjectPath(AssetPath)).IsValid();
}

bool DoesPackageExistInProjectOrEngine(const FString& LongPackageName)
{
	if (LongPackageName.IsEmpty())
	{
		return false;
	}

	FString PackageFilename;
	return FPackageName::DoesPackageExist(LongPackageName, &PackageFilename);
}

bool IsPakBuildPackageAllowed(const FString& LongPackageName)
{
	if (LongPackageName.StartsWith(TEXT("/Game/")))
	{
		return true;
	}

	if (LongPackageName.StartsWith(TEXT("/Engine/")))
	{
		if (LongPackageName.StartsWith(TEXT("/Engine/Editor")) ||
			LongPackageName.StartsWith(TEXT("/Engine/VREditor")))
		{
			return false;
		}

		return true;
	}

	return false;
}

bool IsGamePackageOutsideContentRoot(const FString& LongPackageName, const FString& ContentRoot)
{
	if (!LongPackageName.StartsWith(TEXT("/Game/")))
	{
		return false;
	}

	if (ContentRoot.Equals(TEXT("/Game")))
	{
		return false;
	}

	return !LongPackageName.StartsWith(ContentRoot + TEXT("/")) && !LongPackageName.Equals(ContentRoot);
}

bool AddPackageAssetPathByPackageName(
	const FAssetRegistryModule& AssetRegistryModule,
	const FName PackageName,
	TArray<FString>& AssetPaths,
	TSet<FString>& UniqueAssetPaths)
{
	const FString PackageNameString = PackageName.ToString();
	if (!IsPakBuildPackageAllowed(PackageNameString))
	{
		return false;
	}

	TArray<FAssetData> PackageAssets;
	AssetRegistryModule.Get().GetAssetsByPackageName(PackageName, PackageAssets, true);
	if (PackageAssets.Num() == 0)
	{
		if (!DoesPackageExistInProjectOrEngine(PackageNameString))
		{
			return false;
		}

		AddUniqueAssetPath(PackageNameString, AssetPaths, UniqueAssetPaths);
		return true;
	}

	for (const FAssetData& PackageAsset : PackageAssets)
	{
		AddUniqueAssetPath(PackageAsset.GetSoftObjectPath().ToString(), AssetPaths, UniqueAssetPaths);
	}
	return true;
}

void AddRecursivePackageDependencies(
	const TArray<FString>& RootAssetPaths,
	TArray<FString>& AssetPaths,
	TSet<FString>& UniqueAssetPaths,
	TArray<FString>& Messages)
{
	FAssetRegistryModule* AssetRegistryModule =
		FModuleManager::LoadModulePtr<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	if (!AssetRegistryModule || !AssetRegistryModule->IsValid())
	{
		Messages.Add(TEXT("AssetRegistry module is unavailable. Recursive dependency collection skipped."));
		return;
	}

	AssetRegistryModule->Get().SearchAllAssets(true);

	TArray<FName> PendingPackages;
	TSet<FName> VisitedPackages;
	int32 SkippedDependencyCount = 0;
	int32 SkippedMissingDependencyCount = 0;
	for (const FString& RootAssetPath : RootAssetPaths)
	{
		const FString LongPackageName = GetLongPackageNameFromAssetPath(RootAssetPath);
		if (!LongPackageName.IsEmpty() && IsPakBuildPackageAllowed(LongPackageName))
		{
			PendingPackages.Add(FName(*LongPackageName));
		}
	}

	int32 AddedDependencyCount = 0;
	for (int32 Index = 0; Index < PendingPackages.Num(); ++Index)
	{
		const FName PackageName = PendingPackages[Index];
		if (VisitedPackages.Contains(PackageName))
		{
			continue;
		}
		VisitedPackages.Add(PackageName);

		TArray<FName> Dependencies;
		AssetRegistryModule->Get().GetDependencies(
			PackageName,
			Dependencies,
			UE::AssetRegistry::EDependencyCategory::Package);

		for (const FName DependencyPackageName : Dependencies)
		{
			if (DependencyPackageName.IsNone() || VisitedPackages.Contains(DependencyPackageName))
			{
				continue;
			}

			const FString DependencyPackageNameString = DependencyPackageName.ToString();
			if (!IsPakBuildPackageAllowed(DependencyPackageNameString))
			{
				++SkippedDependencyCount;
				continue;
			}

			PendingPackages.Add(DependencyPackageName);
			const int32 BeforeCount = AssetPaths.Num();
			if (AddPackageAssetPathByPackageName(*AssetRegistryModule, DependencyPackageName, AssetPaths, UniqueAssetPaths))
			{
				AddedDependencyCount += AssetPaths.Num() - BeforeCount;
			}
			else
			{
				++SkippedMissingDependencyCount;
			}
		}
	}

	if (AddedDependencyCount > 0)
	{
		Messages.Add(FString::Printf(TEXT("Recursive hard dependencies added: %d."), AddedDependencyCount));
	}
	if (SkippedDependencyCount > 0)
	{
		Messages.Add(FString::Printf(TEXT("Skipped non-runtime dependencies: %d."), SkippedDependencyCount));
	}
	if (SkippedMissingDependencyCount > 0)
	{
		Messages.Add(FString::Printf(TEXT("Skipped missing dependency package paths: %d. These are usually stale redirector paths."), SkippedMissingDependencyCount));
	}
}

FString QuoteCommandArgument(const FString& Value)
{
	return FString::Printf(TEXT("\"%s\""), *Value);
}

FString NormalizeCommandPath(FString Path)
{
	FPaths::NormalizeFilename(Path);
	return Path;
}

FString GetCookTargetPlatform(const FString& TargetPlatform)
{
	if (TargetPlatform.Equals(TEXT("Win64"), ESearchCase::IgnoreCase) ||
		TargetPlatform.Equals(TEXT("Windows"), ESearchCase::IgnoreCase))
	{
		return TEXT("Windows");
	}

	return TargetPlatform.IsEmpty() ? TEXT("Windows") : TargetPlatform;
}

FString GetProjectNameForPak()
{
	const FString ProjectFilePath = FPaths::GetProjectFilePath();
	if (!ProjectFilePath.IsEmpty())
	{
		return FPaths::GetBaseFilename(ProjectFilePath);
	}

	return FApp::GetProjectName();
}

FString ExtractObjectPathString(FString AssetPath)
{
	AssetPath.TrimStartAndEndInline();

	int32 FirstQuoteIndex = INDEX_NONE;
	int32 LastQuoteIndex = INDEX_NONE;
	if (AssetPath.FindChar(TEXT('\''), FirstQuoteIndex) &&
		AssetPath.FindLastChar(TEXT('\''), LastQuoteIndex) &&
		LastQuoteIndex > FirstQuoteIndex)
	{
		AssetPath = AssetPath.Mid(FirstQuoteIndex + 1, LastQuoteIndex - FirstQuoteIndex - 1);
	}

	return AssetPath;
}

FString GetLongPackageNameFromAssetPath(const FString& AssetPath)
{
	const FString ObjectPath = ExtractObjectPathString(AssetPath);
	const FSoftObjectPath SoftObjectPath(ObjectPath);
	FString LongPackageName = SoftObjectPath.GetLongPackageName();
	if (!LongPackageName.IsEmpty())
	{
		return LongPackageName;
	}

	FString PackageName = ObjectPath;
	const int32 DotIndex = PackageName.Find(TEXT("."));
	if (DotIndex != INDEX_NONE)
	{
		PackageName.LeftInline(DotIndex);
	}
	return PackageName;
}

bool GetCookedPackageBasePath(
	const FString& LongPackageName,
	const FString& CookedPlatformRoot,
	const FString& ProjectName,
	FString& OutSourceBasePath,
	FString& OutPakBasePath,
	FString& OutError)
{
	OutSourceBasePath.Reset();
	OutPakBasePath.Reset();
	OutError.Reset();

	if (LongPackageName.StartsWith(TEXT("/Game/")))
	{
		const FString RelativeContentPath = LongPackageName.RightChop(6);
		OutSourceBasePath = FPaths::Combine(CookedPlatformRoot, ProjectName, TEXT("Content"), RelativeContentPath);
		OutPakBasePath = FString::Printf(TEXT("../../../%s/Content/%s"), *ProjectName, *RelativeContentPath);
	}
	else if (LongPackageName.StartsWith(TEXT("/Engine/")))
	{
		const FString RelativeContentPath = LongPackageName.RightChop(8);
		OutSourceBasePath = FPaths::Combine(CookedPlatformRoot, TEXT("Engine"), TEXT("Content"), RelativeContentPath);
		OutPakBasePath = FString::Printf(TEXT("../../../Engine/Content/%s"), *RelativeContentPath);
	}
	else
	{
		OutError = FString::Printf(TEXT("Unsupported cooked package root: %s"), *LongPackageName);
		return false;
	}

	OutSourceBasePath = NormalizeCommandPath(OutSourceBasePath);
	OutPakBasePath.ReplaceInline(TEXT("\\"), TEXT("/"));
	return true;
}

void FindCookedFilesForPackage(const FString& SourceBasePath, TArray<FString>& OutFiles)
{
	static const TCHAR* Extensions[] =
	{
		TEXT(".uasset"),
		TEXT(".umap"),
		TEXT(".uexp"),
		TEXT(".ubulk"),
		TEXT(".m.ubulk"),
		TEXT(".o.ubulk"),
		TEXT(".uptnl")
	};

	OutFiles.Reset();
	for (const TCHAR* Extension : Extensions)
	{
		const FString Candidate = SourceBasePath + Extension;
		if (FPaths::FileExists(Candidate))
		{
			OutFiles.Add(Candidate);
		}
	}

	OutFiles.Sort();
}

bool HasCookedPackageFile(const TArray<FString>& CookedFiles)
{
	for (const FString& CookedFile : CookedFiles)
	{
		const FString Extension = FPaths::GetExtension(CookedFile, true);
		if (Extension.Equals(TEXT(".uasset"), ESearchCase::IgnoreCase) ||
			Extension.Equals(TEXT(".umap"), ESearchCase::IgnoreCase))
		{
			return true;
		}
	}

	return false;
}

void AddPakListEntry(
	const FString& SourceFilePath,
	const FString& PakMountPath,
	TSet<FString>& UniquePakEntries,
	TArray<FString>& PakListLines)
{
	FString NormalizedSourceFilePath = NormalizeCommandPath(SourceFilePath);
	FString NormalizedPakMountPath = PakMountPath;
	NormalizedPakMountPath.ReplaceInline(TEXT("\\"), TEXT("/"));

	const FString UniqueKey = NormalizedSourceFilePath + TEXT("|") + NormalizedPakMountPath;
	if (UniquePakEntries.Contains(UniqueKey))
	{
		return;
	}

	UniquePakEntries.Add(UniqueKey);
	PakListLines.Add(FString::Printf(TEXT("\"%s\" \"%s\""), *NormalizedSourceFilePath, *NormalizedPakMountPath));
}

void AddCookedProjectShaderArchives(
	const FString& CookedPlatformRoot,
	const FString& ProjectName,
	TSet<FString>& UniquePakEntries,
	TArray<FString>& PakListLines,
	TArray<FString>& Messages)
{
	const FString CookedProjectContentDirectory = NormalizeCommandPath(
		FPaths::Combine(CookedPlatformRoot, ProjectName, TEXT("Content")));
	if (!FPaths::DirectoryExists(CookedProjectContentDirectory))
	{
		return;
	}

	TArray<FString> ShaderArchiveFilenames;
	IFileManager::Get().FindFiles(
		ShaderArchiveFilenames,
		*FPaths::Combine(CookedProjectContentDirectory, FString::Printf(TEXT("ShaderArchive-%s_Chunk*.ushaderbytecode"), *ProjectName)),
		true,
		false);

	int32 AddedShaderArchiveCount = 0;
	int32 AddedShaderArchiveAliasCount = 0;
	const FString Chunk0Prefix = FString::Printf(TEXT("ShaderArchive-%s_Chunk0-"), *ProjectName);
	for (const FString& ShaderArchiveFilename : ShaderArchiveFilenames)
	{
		const FString ShaderArchiveSourceFilePath = NormalizeCommandPath(
			FPaths::Combine(CookedProjectContentDirectory, ShaderArchiveFilename));
		const FString ShaderArchivePakMountPath = FString::Printf(
			TEXT("../../../%s/Content/%s"),
			*ProjectName,
			*ShaderArchiveFilename);
		AddPakListEntry(ShaderArchiveSourceFilePath, ShaderArchivePakMountPath, UniquePakEntries, PakListLines);
		++AddedShaderArchiveCount;

		if (ShaderArchiveFilename.StartsWith(Chunk0Prefix))
		{
			const FString AliasFilename = FString::Printf(
				TEXT("ShaderArchive-%s-%s"),
				*ProjectName,
				*ShaderArchiveFilename.RightChop(Chunk0Prefix.Len()));
			const FString AliasPakMountPath = FString::Printf(
				TEXT("../../../%s/Content/%s"),
				*ProjectName,
				*AliasFilename);
			AddPakListEntry(ShaderArchiveSourceFilePath, AliasPakMountPath, UniquePakEntries, PakListLines);
			++AddedShaderArchiveAliasCount;
		}
	}

	if (AddedShaderArchiveCount > 0)
	{
		Messages.Add(FString::Printf(
			TEXT("Project shader archives added: %d. PakId shader aliases added: %d."),
			AddedShaderArchiveCount,
			AddedShaderArchiveAliasCount));
	}
	else
	{
		Messages.Add(TEXT("No project shader archives were found in cooked content. Materials may use default material in a cooked runtime."));
	}
}

void SaveProcessLog(
	const FString& LogFilePath,
	const FString& Header,
	const FString& StdOut,
	const FString& StdErr)
{
	FString LogText = Header;
	LogText += LINE_TERMINATOR;
	LogText += TEXT("----- stdout -----");
	LogText += LINE_TERMINATOR;
	LogText += StdOut;
	LogText += LINE_TERMINATOR;
	LogText += TEXT("----- stderr -----");
	LogText += LINE_TERMINATOR;
	LogText += StdErr;
	FFileHelper::SaveStringToFile(LogText, *LogFilePath);
}

void InitializeLiveProcessLog(const FString& LogFilePath, const FString& Header)
{
	if (LogFilePath.IsEmpty())
	{
		return;
	}

	IFileManager::Get().MakeDirectory(*FPaths::GetPath(LogFilePath), true);

	FString LogText = Header;
	LogText += LINE_TERMINATOR;
	LogText += TEXT("----- live stdout/stderr -----");
	LogText += LINE_TERMINATOR;
	FFileHelper::SaveStringToFile(
		LogText,
		*LogFilePath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

void AppendLiveProcessLog(const FString& LogFilePath, const FString& Text)
{
	if (LogFilePath.IsEmpty() || Text.IsEmpty())
	{
		return;
	}

	FFileHelper::SaveStringToFile(
		Text,
		*LogFilePath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM,
		&IFileManager::Get(),
		FILEWRITE_Append);
}

void LogPakProgress(const int32 Percent, const TCHAR* Message)
{
	UE_LOG(LogTemp, Display, TEXT("SOMETOOL_PAK_PROGRESS %d %s"), Percent, Message);
}

bool RunProcessWithLiveLog(
	const FString& ExecutablePath,
	const FString& Params,
	const FString& WorkingDirectory,
	const FString& LogPrefix,
	const FString& LiveLogFilePath,
	int32& OutReturnCode,
	FString& OutStdOut,
	FString& OutStdErr)
{
	OutReturnCode = 0;
	OutStdOut.Reset();
	OutStdErr.Reset();

	void* ReadPipe = nullptr;
	void* WritePipe = nullptr;
	if (!FPlatformProcess::CreatePipe(ReadPipe, WritePipe))
	{
		return false;
	}

	InitializeLiveProcessLog(LiveLogFilePath, FString::Printf(TEXT("%s %s"), *ExecutablePath, *Params));

	FProcHandle ProcHandle = FPlatformProcess::CreateProc(
		*ExecutablePath,
		*Params,
		true,
		true,
		true,
		nullptr,
		0,
		*WorkingDirectory,
		WritePipe,
		WritePipe);

	if (!ProcHandle.IsValid())
	{
		FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
		return false;
	}

	double LastForwardTime = 0.0;
	while (!FPlatformProcess::GetProcReturnCode(ProcHandle, &OutReturnCode))
	{
		const FString Chunk = FPlatformProcess::ReadPipe(ReadPipe);
		if (!Chunk.IsEmpty())
		{
			OutStdOut += Chunk;
			AppendLiveProcessLog(LiveLogFilePath, Chunk);
			const double Now = FPlatformTime::Seconds();
			if (Now - LastForwardTime > 1.0)
			{
				FString Tail = Chunk;
				Tail.TrimStartAndEndInline();
				if (!Tail.IsEmpty())
				{
					if (Tail.Len() > 1200)
					{
						Tail = Tail.Right(1200);
					}
					UE_LOG(LogTemp, Display, TEXT("%s %s"), *LogPrefix, *Tail);
				}
				LastForwardTime = Now;
			}
		}

		FPlatformProcess::Sleep(0.2f);
	}

	const FString FinalChunk = FPlatformProcess::ReadPipe(ReadPipe);
	if (!FinalChunk.IsEmpty())
	{
		OutStdOut += FinalChunk;
		AppendLiveProcessLog(LiveLogFilePath, FinalChunk);
		FString Tail = FinalChunk;
		Tail.TrimStartAndEndInline();
		if (!Tail.IsEmpty())
		{
			if (Tail.Len() > 1200)
			{
				Tail = Tail.Right(1200);
			}
			UE_LOG(LogTemp, Display, TEXT("%s %s"), *LogPrefix, *Tail);
		}
	}

	FPlatformProcess::CloseProc(ProcHandle);
	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
	return true;
}
}

bool FSomeToolPakManifestBuilder::BuildById(
	const FSomeToolPakManifestBuildOptions& Options,
	FSomeToolPakManifestBuildResult& OutResult)
{
	OutResult = FSomeToolPakManifestBuildResult();
	OutResult.PakId = Options.PakId;

	if (Options.PakId.IsNone())
	{
		OutResult.Messages.Add(TEXT("PakId is empty."));
		return false;
	}

	FString Error;
	USomeToolPakPrimaryAsset* PakEntry = FindPakEntryById(Options.PakId, Error);
	if (!PakEntry)
	{
		OutResult.Messages.Add(Error);
		return false;
	}

	const FString PakIdString = Options.PakId.ToString();
	const FString OutputRootDirectory = Options.OutputDirectory.IsEmpty()
		? GetDefaultOutputDirectory()
		: Options.OutputDirectory;
	const FString TargetPlatform = Options.TargetPlatform.IsEmpty()
		? TEXT("Windows")
		: Options.TargetPlatform;
	const FString OutputDirectory = OutputRootDirectory;
	const FString ContentRoot = Options.ContentRoot.IsEmpty()
		? GetDefaultContentRoot(Options.PakId)
		: NormalizeLongPackagePath(Options.ContentRoot);
	bool bHasValidationWarnings = false;

	OutResult.EntryAssetPath = PakEntry->GetPathName();
	OutResult.ContentRoot = ContentRoot;
	OutResult.TargetPlatform = TargetPlatform;
	OutResult.OutputDirectory = OutputDirectory;
	OutResult.PakFileName = PakIdString + TEXT(".pak");
	OutResult.ManifestFilePath = FPaths::Combine(OutputDirectory, PakIdString + TEXT(".manifest.json"));
	OutResult.ResourceListFilePath = FPaths::Combine(OutputDirectory, PakIdString + TEXT(".resources.txt"));

	TArray<FString> AssetPaths;
	TSet<FString> UniqueAssetPaths;
	AddUniqueAssetPath(OutResult.EntryAssetPath, AssetPaths, UniqueAssetPaths);

	if (Options.bIncludeEntryMap)
	{
		AddUniqueAssetPath(MakeSoftObjectPathString(PakEntry->EntryMap), AssetPaths, UniqueAssetPaths);
		if (PakEntry->EntryMap.IsNull())
		{
			bHasValidationWarnings = true;
			OutResult.Messages.Add(TEXT("EntryMap is empty."));
		}
	}

	if (PakEntry->ResourceRegistry.IsNull())
	{
		bHasValidationWarnings = true;
		OutResult.Messages.Add(TEXT("ResourceRegistry is empty."));
	}
	else
	{
		USomeToolPakResourceRegistry* ResourceRegistry = PakEntry->ResourceRegistry.LoadSynchronous();
		if (!ResourceRegistry)
		{
			bHasValidationWarnings = true;
			OutResult.Messages.Add(FString::Printf(TEXT("ResourceRegistry failed to load: %s."), *PakEntry->ResourceRegistry.ToString()));
		}
		else
		{
			OutResult.ResourceRegistryPath = ResourceRegistry->GetPathName();
			AddUniqueAssetPath(OutResult.ResourceRegistryPath, AssetPaths, UniqueAssetPaths);

			if (Options.bIncludeRegistryObjects)
			{
				for (const TPair<FName, TSoftObjectPtr<UObject>>& Entry : ResourceRegistry->SoftObjects)
				{
					AddUniqueAssetPath(Entry.Value.ToString(), AssetPaths, UniqueAssetPaths);
					if (Entry.Value.IsNull())
					{
						bHasValidationWarnings = true;
						OutResult.Messages.Add(FString::Printf(TEXT("SoftObjects entry is empty: %s."), *Entry.Key.ToString()));
					}
				}
			}

			if (Options.bIncludeRegistryClasses)
			{
				for (const TPair<FName, TSoftClassPtr<UObject>>& Entry : ResourceRegistry->SoftClasses)
				{
					AddUniqueAssetPath(Entry.Value.ToString(), AssetPaths, UniqueAssetPaths);
					if (Entry.Value.IsNull())
					{
						bHasValidationWarnings = true;
						OutResult.Messages.Add(FString::Printf(TEXT("SoftClasses entry is empty: %s."), *Entry.Key.ToString()));
					}
				}
			}
		}
	}

	AddRecursivePackageDependencies(AssetPaths, AssetPaths, UniqueAssetPaths, OutResult.Messages);

	AssetPaths.Sort();
	OutResult.AssetPaths = AssetPaths;

	for (const FString& AssetPath : OutResult.AssetPaths)
	{
		const FString LongPackageName = GetLongPackageNameFromAssetPath(AssetPath);
		if (IsGamePackageOutsideContentRoot(LongPackageName, ContentRoot) &&
			!AssetPath.Equals(OutResult.EntryAssetPath) &&
			!AssetPath.Equals(OutResult.ResourceRegistryPath))
		{
			bHasValidationWarnings = true;
			OutResult.Messages.Add(FString::Printf(TEXT("Asset is outside ContentRoot %s: %s"), *ContentRoot, *AssetPath));
		}

		if (!DoesAssetExist(AssetPath))
		{
			bHasValidationWarnings = true;
			OutResult.Messages.Add(FString::Printf(TEXT("Asset does not exist in AssetRegistry: %s"), *AssetPath));
		}
	}

	IFileManager::Get().MakeDirectory(*OutputDirectory, true);

	FString ResourceList;
	for (const FString& AssetPath : OutResult.AssetPaths)
	{
		ResourceList += AssetPath + LINE_TERMINATOR;
	}

	if (!FFileHelper::SaveStringToFile(ResourceList, *OutResult.ResourceListFilePath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Failed to save resource list: %s"), *OutResult.ResourceListFilePath));
		return false;
	}

	TSharedRef<FJsonObject> ManifestObject = MakeShared<FJsonObject>();
	ManifestObject->SetStringField(TEXT("PakId"), PakIdString);
	ManifestObject->SetNumberField(TEXT("Version"), Options.Version);
	ManifestObject->SetStringField(TEXT("TargetPlatform"), TargetPlatform);
	ManifestObject->SetStringField(TEXT("PakFile"), OutResult.PakFileName);
	ManifestObject->SetStringField(TEXT("ContentRoot"), OutResult.ContentRoot);
	ManifestObject->SetStringField(TEXT("EntryAsset"), OutResult.EntryAssetPath);
	ManifestObject->SetStringField(TEXT("EntryMap"), MakeSoftObjectPathString(PakEntry->EntryMap));
	ManifestObject->SetStringField(TEXT("ResourceRegistry"), OutResult.ResourceRegistryPath);
	ManifestObject->SetStringField(TEXT("ResourceListFile"), FPaths::GetCleanFilename(OutResult.ResourceListFilePath));

	TArray<TSharedPtr<FJsonValue>> DependentPakIds;
	for (const FName DependentPakId : PakEntry->DependentPakIds)
	{
		DependentPakIds.Add(MakeShared<FJsonValueString>(DependentPakId.ToString()));
	}
	ManifestObject->SetArrayField(TEXT("DependentPakIds"), DependentPakIds);

	TArray<TSharedPtr<FJsonValue>> Assets;
	for (const FString& AssetPath : OutResult.AssetPaths)
	{
		Assets.Add(MakeShared<FJsonValueString>(AssetPath));
	}
	ManifestObject->SetArrayField(TEXT("Assets"), Assets);

	FString ManifestJson;
	const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&ManifestJson);
	if (!FJsonSerializer::Serialize(ManifestObject, Writer))
	{
		OutResult.Messages.Add(TEXT("Failed to serialize manifest json."));
		return false;
	}

	if (!FFileHelper::SaveStringToFile(ManifestJson, *OutResult.ManifestFilePath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Failed to save manifest: %s"), *OutResult.ManifestFilePath));
		return false;
	}

	OutResult.bSucceeded = !bHasValidationWarnings;
	if (OutResult.bSucceeded)
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Manifest generated for PakId %s."), *PakIdString));
	}
	return OutResult.bSucceeded;
}

bool FSomeToolPakManifestBuilder::BuildPakById(
	const FSomeToolPakManifestBuildOptions& Options,
	FSomeToolPakManifestBuildResult& OutResult)
{
	LogPakProgress(10, TEXT("Build manifest"));
	const bool bManifestSucceeded = BuildById(Options, OutResult);
	if (OutResult.EntryAssetPath.IsEmpty() || OutResult.ResourceListFilePath.IsEmpty() || OutResult.ManifestFilePath.IsEmpty())
	{
		OutResult.Messages.Add(TEXT("Pak build stopped because manifest generation did not produce required files."));
		OutResult.bSucceeded = false;
		return false;
	}

	if (!bManifestSucceeded)
	{
		OutResult.Messages.Add(TEXT("Manifest contains warnings. Cook and pak build will continue for this first-pass pipeline."));
	}

	LogPakProgress(25, TEXT("Manifest generated"));
	if (!RunCook(Options, OutResult))
	{
		OutResult.bSucceeded = false;
		return false;
	}

	LogPakProgress(65, TEXT("Cook finished"));
	if (!BuildPakFromCookedFiles(Options, OutResult))
	{
		OutResult.bSucceeded = false;
		return false;
	}

	OutResult.bSucceeded = true;
	OutResult.Messages.Add(FString::Printf(TEXT("Pak generated: %s"), *OutResult.PakFilePath));
	return true;
}

USomeToolPakPrimaryAsset* FSomeToolPakManifestBuilder::FindPakEntryById(
	const FName PakId,
	FString& OutError)
{
	OutError.Reset();
	if (PakId.IsNone())
	{
		OutError = TEXT("PakId is empty.");
		return nullptr;
	}

	const FString ExpectedAssetName = MakePakEntryAssetName(PakId);
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	AssetRegistryModule.Get().SearchAllAssets(true);

	TArray<FAssetData> Assets;
	AssetRegistryModule.Get().GetAssetsByClass(
		USomeToolPakPrimaryAsset::StaticClass()->GetClassPathName(),
		Assets,
		true);

	for (const FAssetData& Asset : Assets)
	{
		if (Asset.AssetName.ToString() == ExpectedAssetName)
		{
			return Cast<USomeToolPakPrimaryAsset>(Asset.GetAsset());
		}
	}

	OutError = FString::Printf(TEXT("PakEntry was not found. Expected asset name: %s."), *ExpectedAssetName);
	return nullptr;
}

FString FSomeToolPakManifestBuilder::GetDefaultOutputDirectory()
{
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Paks")));
}

FString FSomeToolPakManifestBuilder::GetDefaultContentRoot(const FName PakId)
{
	return TEXT("/Game");
}

FString FSomeToolPakManifestBuilder::MakePakEntryAssetName(const FName PakId)
{
	return FString::Printf(TEXT("DA_PakEntry_%s"), *PakId.ToString());
}

bool FSomeToolPakManifestBuilder::RunCook(
	const FSomeToolPakManifestBuildOptions& Options,
	FSomeToolPakManifestBuildResult& OutResult)
{
	const FString EngineDir = FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
	const FString EditorCmdPath = NormalizeCommandPath(FPaths::Combine(EngineDir, TEXT("Binaries"), TEXT("Win64"), TEXT("UnrealEditor-Cmd.exe")));
	if (!FPaths::FileExists(EditorCmdPath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("UnrealEditor-Cmd.exe was not found: %s"), *EditorCmdPath));
		return false;
	}

	const FString ProjectFilePath = NormalizeCommandPath(FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()));
	if (!FPaths::FileExists(ProjectFilePath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Project file was not found: %s"), *ProjectFilePath));
		return false;
	}

	IFileManager::Get().MakeDirectory(*OutResult.OutputDirectory, true);

	const FString CookTargetPlatform = GetCookTargetPlatform(OutResult.TargetPlatform);
	const FString Params = FString::Printf(
		TEXT("%s -run=Cook -TargetPlatform=%s -CookAll -unattended -nop4 -UTF8Output"),
		*QuoteCommandArgument(ProjectFilePath),
		*CookTargetPlatform);

	int32 ReturnCode = 0;
	FString StdOut;
	FString StdErr;
	const FString CookLogPath = FPaths::Combine(OutResult.OutputDirectory, OutResult.PakId.ToString() + TEXT(".cook.log"));
	LogPakProgress(40, TEXT("Cook started"));
	const bool bStarted = RunProcessWithLiveLog(
		EditorCmdPath,
		Params,
		FPaths::ProjectDir(),
		TEXT("Cook:"),
		CookLogPath,
		ReturnCode,
		StdOut,
		StdErr);

	SaveProcessLog(CookLogPath, FString::Printf(TEXT("%s %s"), *EditorCmdPath, *Params), StdOut, StdErr);
	OutResult.Messages.Add(FString::Printf(TEXT("Cook log: %s"), *CookLogPath));

	if (!bStarted || ReturnCode != 0)
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Cook failed. Started=%s ReturnCode=%d"), bStarted ? TEXT("true") : TEXT("false"), ReturnCode));
		return false;
	}

	OutResult.Messages.Add(FString::Printf(TEXT("Cook succeeded for target platform %s."), *CookTargetPlatform));
	return true;
}

bool FSomeToolPakManifestBuilder::BuildPakFromCookedFiles(
	const FSomeToolPakManifestBuildOptions& Options,
	FSomeToolPakManifestBuildResult& OutResult)
{
	const FString EngineDir = FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
	const FString UnrealPakPath = NormalizeCommandPath(FPaths::Combine(EngineDir, TEXT("Binaries"), TEXT("Win64"), TEXT("UnrealPak.exe")));
	if (!FPaths::FileExists(UnrealPakPath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("UnrealPak.exe was not found: %s"), *UnrealPakPath));
		return false;
	}

	const FString ProjectName = GetProjectNameForPak();
	const FString CookTargetPlatform = GetCookTargetPlatform(OutResult.TargetPlatform);
	const FString CookedPlatformRoot = NormalizeCommandPath(FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Cooked"), CookTargetPlatform)));
	if (!FPaths::DirectoryExists(CookedPlatformRoot))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Cooked platform directory was not found: %s"), *CookedPlatformRoot));
		return false;
	}

	OutResult.PakListFilePath = NormalizeCommandPath(FPaths::Combine(OutResult.OutputDirectory, OutResult.PakId.ToString() + TEXT(".paklist.txt")));
	OutResult.PakFilePath = NormalizeCommandPath(FPaths::Combine(OutResult.OutputDirectory, OutResult.PakFileName));

	TSet<FString> UniquePackages;
	TSet<FString> UniquePakEntries;
	TArray<FString> PakListLines;
	bool bHasBlockingMissingFile = false;

	for (const FString& AssetPath : OutResult.AssetPaths)
	{
		const FString LongPackageName = GetLongPackageNameFromAssetPath(AssetPath);
		if (LongPackageName.IsEmpty())
		{
			OutResult.Messages.Add(FString::Printf(TEXT("Could not get package name from asset path: %s"), *AssetPath));
			bHasBlockingMissingFile = true;
			continue;
		}

		if (UniquePackages.Contains(LongPackageName))
		{
			continue;
		}
		UniquePackages.Add(LongPackageName);

		FString SourceBasePath;
		FString PakBasePath;
		FString Error;
		if (!GetCookedPackageBasePath(LongPackageName, CookedPlatformRoot, ProjectName, SourceBasePath, PakBasePath, Error))
		{
			OutResult.Messages.Add(Error);
			bHasBlockingMissingFile = true;
			continue;
		}

		TArray<FString> CookedFiles;
		FindCookedFilesForPackage(SourceBasePath, CookedFiles);
		if (!HasCookedPackageFile(CookedFiles))
		{
			const FString Message = FString::Printf(TEXT("Cooked package file was not found for %s. Expected base path: %s"), *LongPackageName, *SourceBasePath);
			OutResult.Messages.Add(Message);
			if (LongPackageName.StartsWith(TEXT("/Game/")) && DoesPackageExistInProjectOrEngine(LongPackageName))
			{
				bHasBlockingMissingFile = true;
			}
			else
			{
				OutResult.Messages.Add(FString::Printf(TEXT("Skipped missing package path while building pak list: %s"), *LongPackageName));
			}
			continue;
		}

		for (const FString& CookedFile : CookedFiles)
		{
			const FString Extension = FPaths::GetExtension(CookedFile, true);
			FString PakMountPath = PakBasePath + Extension;
			AddPakListEntry(CookedFile, PakMountPath, UniquePakEntries, PakListLines);
		}
	}

	AddCookedProjectShaderArchives(CookedPlatformRoot, ProjectName, UniquePakEntries, PakListLines, OutResult.Messages);

	PakListLines.Sort();
	FString PakListText;
	for (const FString& PakListLine : PakListLines)
	{
		PakListText += PakListLine + LINE_TERMINATOR;
	}

	if (!FFileHelper::SaveStringToFile(PakListText, *OutResult.PakListFilePath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("Failed to save UnrealPak response file: %s"), *OutResult.PakListFilePath));
		return false;
	}
	LogPakProgress(78, TEXT("Pak list generated"));
	OutResult.Messages.Add(FString::Printf(TEXT("UnrealPak response file: %s"), *OutResult.PakListFilePath));

	if (PakListLines.Num() == 0)
	{
		OutResult.Messages.Add(TEXT("UnrealPak response file is empty."));
		return false;
	}

	if (bHasBlockingMissingFile)
	{
		OutResult.Messages.Add(TEXT("Pak build stopped because one or more /Game cooked package files were missing."));
		return false;
	}

	const FString Params = FString::Printf(
		TEXT("%s -Create=%s"),
		*QuoteCommandArgument(OutResult.PakFilePath),
		*QuoteCommandArgument(OutResult.PakListFilePath));

	int32 ReturnCode = 0;
	FString StdOut;
	FString StdErr;
	const FString UnrealPakLogPath = FPaths::Combine(OutResult.OutputDirectory, OutResult.PakId.ToString() + TEXT(".unrealpak.log"));
	LogPakProgress(88, TEXT("UnrealPak started"));
	const bool bStarted = RunProcessWithLiveLog(
		UnrealPakPath,
		Params,
		FPaths::ProjectDir(),
		TEXT("UnrealPak:"),
		UnrealPakLogPath,
		ReturnCode,
		StdOut,
		StdErr);

	SaveProcessLog(UnrealPakLogPath, FString::Printf(TEXT("%s %s"), *UnrealPakPath, *Params), StdOut, StdErr);
	OutResult.Messages.Add(FString::Printf(TEXT("UnrealPak log: %s"), *UnrealPakLogPath));

	if (!bStarted || ReturnCode != 0 || !FPaths::FileExists(OutResult.PakFilePath))
	{
		OutResult.Messages.Add(FString::Printf(TEXT("UnrealPak failed. Started=%s ReturnCode=%d"), bStarted ? TEXT("true") : TEXT("false"), ReturnCode));
		return false;
	}

	OutResult.Messages.Add(FString::Printf(TEXT("UnrealPak succeeded with %d cooked files."), PakListLines.Num()));
	return true;
}
