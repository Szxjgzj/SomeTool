#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SomeToolPakEditorBlueprintLibrary.generated.h"

class USomeToolPakPrimaryAsset;

USTRUCT(BlueprintType)
struct SOMETOOLPAKEDITOR_API FSomeToolPakManifestBuildOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	FName PakId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	int32 Version = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	FString TargetPlatform = TEXT("Windows");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	FString OutputDirectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	FString ContentRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	bool bIncludeEntryMap = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	bool bIncludeRegistryObjects = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak|Editor")
	bool bIncludeRegistryClasses = true;
};

USTRUCT(BlueprintType)
struct SOMETOOLPAKEDITOR_API FSomeToolPakManifestBuildResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	bool bSucceeded = false;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FName PakId;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString EntryAssetPath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString ResourceRegistryPath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString ContentRoot;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString TargetPlatform;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString OutputDirectory;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString PakFileName;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString ManifestFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString ResourceListFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString PakListFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	FString PakFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	TArray<FString> AssetPaths;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak|Editor")
	TArray<FString> Messages;
};

UCLASS()
class SOMETOOLPAKEDITOR_API USomeToolPakEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak|Editor", meta=(DisplayName="Build Pak Manifest By Id", Keywords="SomeTool pak manifest build validate resources"))
	static bool BuildPakManifestById(const FSomeToolPakManifestBuildOptions& Options, FSomeToolPakManifestBuildResult& OutResult);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak|Editor", meta=(DisplayName="Build Pak By Id", Keywords="SomeTool pak manifest cook unrealpak build"))
	static bool BuildPakById(const FSomeToolPakManifestBuildOptions& Options, FSomeToolPakManifestBuildResult& OutResult);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak|Editor", meta=(DisplayName="Find Pak Entry By Id", Keywords="SomeTool pak entry find id"))
	static USomeToolPakPrimaryAsset* FindPakEntryById(FName PakId, FString& OutError);
};
