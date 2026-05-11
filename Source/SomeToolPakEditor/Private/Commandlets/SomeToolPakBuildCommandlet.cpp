#include "Commandlets/SomeToolPakBuildCommandlet.h"

#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Misc/Parse.h"
#include "Pak/SomeToolPakEditorBlueprintLibrary.h"

namespace
{
void LogPakCommandletProgress(const int32 Percent, const TCHAR* Message)
{
	UE_LOG(LogTemp, Display, TEXT("SOMETOOL_PAK_PROGRESS %d %s"), Percent, Message);
}

void DeleteCommandletBuildFilesByPattern(const FString& Directory, const FString& Pattern)
{
	TArray<FString> Filenames;
	IFileManager::Get().FindFiles(Filenames, *FPaths::Combine(Directory, Pattern), true, false);
	for (const FString& Filename : Filenames)
	{
		IFileManager::Get().Delete(*FPaths::Combine(Directory, Filename), false, true);
	}
}

void CleanCommandletSuccessfulBuildOutputs(const FString& OutputDirectory, const FString& PakIdString)
{
	const FString NormalizedOutputDirectory = FPaths::ConvertRelativePathToFull(OutputDirectory);
	const FString TempDirectory = FPaths::Combine(NormalizedOutputDirectory, TEXT(".BuildTemp"), PakIdString);
	IFileManager::Get().DeleteDirectory(*TempDirectory, false, true);
	IFileManager::Get().DeleteDirectory(*FPaths::Combine(NormalizedOutputDirectory, TEXT(".BuildTemp")), false, false);

	DeleteCommandletBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".build*.log"));
	DeleteCommandletBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".manual-build*.log"));
	DeleteCommandletBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".resources.txt"));
	DeleteCommandletBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".paklist.txt"));
}
}

USomeToolPakBuildCommandlet::USomeToolPakBuildCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 USomeToolPakBuildCommandlet::Main(const FString& Params)
{
	FString PakIdString;
	if (!FParse::Value(*Params, TEXT("PakId="), PakIdString) || PakIdString.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Missing required parameter: -PakId=<Id>"));
		return 1;
	}

	FString OutputDirectory;
	FParse::Value(*Params, TEXT("OutputDirectory="), OutputDirectory);
	if (OutputDirectory.IsEmpty())
	{
		OutputDirectory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Paks")));
	}
	const FString FinalOutputDirectory = OutputDirectory;
	const FString TempOutputDirectory = FPaths::Combine(FinalOutputDirectory, TEXT(".BuildTemp"), PakIdString);

	FSomeToolPakManifestBuildOptions Options;
	Options.PakId = FName(*PakIdString);
	Options.Version = 1;
	Options.TargetPlatform = TEXT("Windows");
	Options.OutputDirectory = TempOutputDirectory;
	Options.ContentRoot = TEXT("/Game");
	Options.bIncludeEntryMap = true;
	Options.bIncludeRegistryObjects = true;
	Options.bIncludeRegistryClasses = true;

	FSomeToolPakManifestBuildResult Result;
	USomeToolPakEditorBlueprintLibrary::BuildPakById(Options, Result);

	if (Result.bSucceeded)
	{
		LogPakCommandletProgress(95, TEXT("Copy final outputs"));
		IFileManager::Get().MakeDirectory(*FinalOutputDirectory, true);

		const FString FinalManifestFilePath = FPaths::Combine(FinalOutputDirectory, PakIdString + TEXT(".manifest.json"));
		const FString FinalPakFilePath = FPaths::Combine(FinalOutputDirectory, PakIdString + TEXT(".pak"));
		const bool bCopiedManifest = IFileManager::Get().Copy(*FinalManifestFilePath, *Result.ManifestFilePath, true, true) == COPY_OK;
		const bool bCopiedPak = IFileManager::Get().Copy(*FinalPakFilePath, *Result.PakFilePath, true, true) == COPY_OK;

		if (!bCopiedManifest || !bCopiedPak)
		{
			Result.bSucceeded = false;
			Result.Messages.Add(FString::Printf(
				TEXT("Failed to copy final outputs. ManifestCopied=%s PakCopied=%s"),
				bCopiedManifest ? TEXT("true") : TEXT("false"),
				bCopiedPak ? TEXT("true") : TEXT("false")));
		}
		else
		{
			Result.ManifestFilePath = FinalManifestFilePath;
			Result.PakFilePath = FinalPakFilePath;
			Result.OutputDirectory = FinalOutputDirectory;
			Result.Messages.Add(FString::Printf(TEXT("Final manifest: %s"), *FinalManifestFilePath));
			Result.Messages.Add(FString::Printf(TEXT("Final pak: %s"), *FinalPakFilePath));
			LogPakCommandletProgress(100, TEXT("Pak build finished"));
			if (FParse::Param(*Params, TEXT("CleanBuildTemp")))
			{
				CleanCommandletSuccessfulBuildOutputs(FinalOutputDirectory, PakIdString);
			}
		}
	}

	UE_LOG(LogTemp, Display, TEXT("SomeTool Pak Build: %s"), Result.bSucceeded ? TEXT("Succeeded") : TEXT("Failed"));
	UE_LOG(LogTemp, Display, TEXT("PakId: %s"), *Result.PakId.ToString());
	UE_LOG(LogTemp, Display, TEXT("Manifest: %s"), *Result.ManifestFilePath);
	UE_LOG(LogTemp, Display, TEXT("ResourceList: %s"), *Result.ResourceListFilePath);
	UE_LOG(LogTemp, Display, TEXT("PakList: %s"), *Result.PakListFilePath);
	UE_LOG(LogTemp, Display, TEXT("PakFile: %s"), *Result.PakFilePath);

	for (const FString& Message : Result.Messages)
	{
		UE_LOG(LogTemp, Display, TEXT("- %s"), *Message);
	}

	return Result.bSucceeded ? 0 : 1;
}
