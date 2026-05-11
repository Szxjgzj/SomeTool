#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/SoftObjectPath.h"
#include "SomeToolPakPrimaryAsset.generated.h"

class USomeToolPakResourceRegistry;

UCLASS(BlueprintType, Blueprintable, meta=(DisplayName="SomeTool Pak Primary Asset"))
class SOMETOOLPAK_API USomeToolPakPrimaryAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	static const FPrimaryAssetType PrimaryAssetType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SomeTool|Pak|Entry", meta=(AllowedClasses="/Script/Engine.World"))
	FSoftObjectPath EntryMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SomeTool|Pak|Entry")
	TSoftObjectPtr<USomeToolPakResourceRegistry> ResourceRegistry;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SomeTool|Pak|Entry")
	TArray<FName> DependentPakIds;
};
