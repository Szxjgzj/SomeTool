#include "Pak/SomeToolPakEditorBlueprintLibrary.h"

#include "Pak/SomeToolPakManifestBuilder.h"

bool USomeToolPakEditorBlueprintLibrary::BuildPakManifestById(
	const FSomeToolPakManifestBuildOptions& Options,
	FSomeToolPakManifestBuildResult& OutResult)
{
	return FSomeToolPakManifestBuilder::BuildById(Options, OutResult);
}

bool USomeToolPakEditorBlueprintLibrary::BuildPakById(
	const FSomeToolPakManifestBuildOptions& Options,
	FSomeToolPakManifestBuildResult& OutResult)
{
	return FSomeToolPakManifestBuilder::BuildPakById(Options, OutResult);
}

USomeToolPakPrimaryAsset* USomeToolPakEditorBlueprintLibrary::FindPakEntryById(
	const FName PakId,
	FString& OutError)
{
	return FSomeToolPakManifestBuilder::FindPakEntryById(PakId, OutError);
}
