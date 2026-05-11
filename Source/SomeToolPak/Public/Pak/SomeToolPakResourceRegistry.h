#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/SoftObjectPath.h"
#include "SomeToolPakResourceRegistry.generated.h"

class FObjectPreSaveContext;

UCLASS(BlueprintType, Blueprintable, meta=(DisplayName="SomeTool Pak Resource Registry"))
class SOMETOOLPAK_API USomeToolPakResourceRegistry : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SomeTool|Pak")
	FName Namespace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SomeTool|Pak", meta=(ReadOnlyKeys))
	TMap<FName, TSoftObjectPtr<UObject>> SoftObjects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SomeTool|Pak", meta=(ReadOnlyKeys))
	TMap<FName, TSoftClassPtr<UObject>> SoftClasses;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	virtual void PostRename(UObject* OldOuter, const FName OldName) override;

private:
	bool SynchronizeGeneratedFields();
#endif
};
