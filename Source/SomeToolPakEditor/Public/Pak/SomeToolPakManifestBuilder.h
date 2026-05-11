#pragma once

#include "CoreMinimal.h"

class USomeToolPakPrimaryAsset;

struct FSomeToolPakManifestBuildOptions;
struct FSomeToolPakManifestBuildResult;

class SOMETOOLPAKEDITOR_API FSomeToolPakManifestBuilder
{
public:
	static bool BuildById(const FSomeToolPakManifestBuildOptions& Options, FSomeToolPakManifestBuildResult& OutResult);
	static bool BuildPakById(const FSomeToolPakManifestBuildOptions& Options, FSomeToolPakManifestBuildResult& OutResult);
	static USomeToolPakPrimaryAsset* FindPakEntryById(FName PakId, FString& OutError);

private:
	static FString GetDefaultOutputDirectory();
	static FString GetDefaultContentRoot(FName PakId);
	static FString MakePakEntryAssetName(FName PakId);
	static bool RunCook(const FSomeToolPakManifestBuildOptions& Options, FSomeToolPakManifestBuildResult& OutResult);
	static bool BuildPakFromCookedFiles(const FSomeToolPakManifestBuildOptions& Options, FSomeToolPakManifestBuildResult& OutResult);
};
