#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SomeToolPakBlueprintLibrary.generated.h"

class USomeToolPakPrimaryAsset;
class USomeToolPakResourceRegistry;

USTRUCT(BlueprintType)
struct SOMETOOLPAK_API FSomeToolPakMountOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	FString PakFilePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	int32 PakOrder = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	FString PakMountPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	bool bRegisterPackageMountPoint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	FString LongPackageRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	FString ContentRootPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	bool bScanAssetRegistry = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	TArray<FString> AssetRegistryScanPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SomeTool|Pak")
	bool bForceAssetRegistryRescan = true;
};

USTRUCT(BlueprintType)
struct SOMETOOLPAK_API FSomeToolMountedPakInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString PakFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString PakMountPoint;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	int32 PakOrder = 0;
};

USTRUCT(BlueprintType)
struct SOMETOOLPAK_API FSomeToolPakRegisteredResourcePath
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FName Name;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FName Namespace;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString ResourceId;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString Path;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	bool bIsClass = false;
};

USTRUCT(BlueprintType)
struct SOMETOOLPAK_API FSomeToolPakManifestInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString ManifestFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString ManifestDirectory;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FName PakId;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	int32 Version = 0;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString TargetPlatform;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString PakFileName;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString PakFilePath;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString ContentRoot;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString EntryAsset;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString EntryMap;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	FString ResourceRegistry;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	TArray<FName> DependentPakIds;

	UPROPERTY(BlueprintReadOnly, Category="SomeTool|Pak")
	TArray<FString> Assets;
};

UCLASS()
class SOMETOOLPAK_API USomeToolPakBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Mount Game Pak Legacy", DeprecatedFunction, DeprecationMessage="Use Mount Game Pak. The new node returns the Pak Entry directly.", Keywords="SomeTool pak id manifest mount game dlc runtime simple legacy"))
	static bool MountGamePak(FName PakId, USomeToolPakPrimaryAsset*& OutPakEntry, TArray<FString>& OutAssetPaths, FString& OutError, TArray<FString>& OutMessages);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Mount Game Pak", Keywords="SomeTool pak id manifest mount game dlc runtime simple entry data"))
	static USomeToolPakPrimaryAsset* MountGamePakEntry(FName PakId);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Unmount Game Pak", Keywords="SomeTool pak id unmount game dlc runtime simple"))
	static bool UnmountGamePak(FName PakId, FString& OutError);

	UFUNCTION(BlueprintPure, Category="SomeTool|Pak", meta=(DisplayName="Is Game Pak Mounted", Keywords="SomeTool pak id mounted game dlc runtime simple"))
	static bool IsGamePakMounted(FName PakId);

private:
	static bool ReadPakManifest(const FString& ManifestFilePath, FSomeToolPakManifestInfo& OutManifest, FString& OutError, TArray<FString>* OutMessages = nullptr);
	static bool MountPakByManifest(const FString& ManifestFilePath, int32 PakOrder, TArray<FString>& OutAssetPaths, FSomeToolPakManifestInfo& OutManifest, FString& OutError, TArray<FString>* OutMessages = nullptr);
	static bool MountPakById(FName PakId, int32 PakOrder, TArray<FString>& OutAssetPaths, FSomeToolPakManifestInfo& OutManifest, FString& OutError, const FString& PakRootDirectory = TEXT(""), TArray<FString>* OutMessages = nullptr);
	static bool MountPak(const FSomeToolPakMountOptions& Options, FString& OutError, TArray<FString>* OutMessages = nullptr);
	static bool MountPakFile(const FString& PakFilePath, int32 PakOrder, const FString& PakMountPoint, FString& OutError);
	static bool UnmountPak(const FString& PakFilePath, FString& OutError);
	static bool IsPakMounted(const FString& PakFilePath);
	static void GetMountedPakFiles(TArray<FString>& OutPakFilePaths);
	static void GetMountedPakInfo(TArray<FSomeToolMountedPakInfo>& OutMountedPakInfo);
	static bool RegisterPakPackageMountPoint(const FString& LongPackageRoot, const FString& ContentRootPath, FString& OutError);
	static bool UnregisterPakPackageMountPoint(const FString& LongPackageRoot, const FString& ContentRootPath, FString& OutError);
	static bool DoesPackageMountPointExist(const FString& LongPackageRoot);
	static bool ScanPakContentPath(const FString& LongPackagePath, bool bForceRescan, FString& OutError);
	static bool GetPakAssetPaths(const FString& LongPackagePath, bool bRecursive, TArray<FString>& OutAssetPaths, FString& OutError);
	static bool GetPakPackageNames(const FString& LongPackagePath, bool bRecursive, TArray<FString>& OutPackageNames, FString& OutError);
	static bool GetPakFilePaths(const FString& PakFilePath, TArray<FString>& OutFilePaths, FString& OutError);

public:
	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Get Registered Pak Resources", Keywords="SomeTool pak registry resource soft reference list"))
	static bool GetRegisteredPakResources(const USomeToolPakResourceRegistry* ResourceRegistry, TArray<FSomeToolPakRegisteredResourcePath>& OutResources, FString& OutError);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Get Pak Entry Registered Resources", Keywords="SomeTool pak entry registry resource soft reference list"))
	static bool GetPakEntryRegisteredResources(const USomeToolPakPrimaryAsset* PakEntry, bool bIncludeEntryMap, TArray<FSomeToolPakRegisteredResourcePath>& OutResources, FString& OutError);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Find Registered Soft Object", Keywords="SomeTool pak registry find soft object resource"))
	static bool FindRegisteredSoftObject(const USomeToolPakResourceRegistry* ResourceRegistry, FName Name, TSoftObjectPtr<UObject>& OutAsset, FString& OutError);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Find Registered Soft Class", Keywords="SomeTool pak registry find soft class resource"))
	static bool FindRegisteredSoftClass(const USomeToolPakResourceRegistry* ResourceRegistry, FName Name, TSoftClassPtr<UObject>& OutClass, FString& OutError);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Find Pak Entry Soft Object", Keywords="SomeTool pak entry registry find soft object resource"))
	static bool FindPakEntrySoftObject(const USomeToolPakPrimaryAsset* PakEntry, FName Name, TSoftObjectPtr<UObject>& OutAsset, FString& OutError);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Find Pak Entry Soft Class", Keywords="SomeTool pak entry registry find soft class resource"))
	static bool FindPakEntrySoftClass(const USomeToolPakPrimaryAsset* PakEntry, FName Name, TSoftClassPtr<UObject>& OutClass, FString& OutError);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Validate Pak Resource Registry", Keywords="SomeTool pak registry validate soft reference"))
	static bool ValidatePakResourceRegistry(const USomeToolPakResourceRegistry* ResourceRegistry, TArray<FString>& OutMessages);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Pak", meta=(DisplayName="Validate Pak Entry", Keywords="SomeTool pak entry validate registry soft reference"))
	static bool ValidatePakEntry(const USomeToolPakPrimaryAsset* PakEntry, TArray<FString>& OutMessages);
};
