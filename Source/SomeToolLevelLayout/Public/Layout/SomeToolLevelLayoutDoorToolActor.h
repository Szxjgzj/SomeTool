#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Layout/SomeToolLevelLayoutTypes.h"
#include "SomeToolLevelLayoutDoorToolActor.generated.h"

class ASomeToolLevelLayoutPreviewActor;
class UBoxComponent;
class USceneComponent;
struct FPropertyChangedEvent;

UCLASS(
	BlueprintType,
	CollapseCategories,
	HideCategories=(Actor, Input, Replication, Collision, Cooking, HLOD, Physics, Navigation, LOD, Rendering, WorldPartition, DataLayers),
	AutoExpandCategories=("Default"),
	PrioritizeCategories=("Default"))
class SOMETOOLLEVELLAYOUT_API ASomeToolLevelLayoutDoorToolActor : public AActor
{
	GENERATED_BODY()

public:
	ASomeToolLevelLayoutDoorToolActor();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(CallInEditor, BlueprintCallable, Category="Default", meta=(DisplayName="通知布局Actor更新"))
	void NotifyLayoutOwnerChanged();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="根组件"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="门窗开口范围组件"))
	TObjectPtr<UBoxComponent> DoorBoundsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="所属布局Actor"))
	TObjectPtr<ASomeToolLevelLayoutPreviewActor> LayoutOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="开口模式"))
	ESomeToolOpeningMode OpeningMode = ESomeToolOpeningMode::Bounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="自动重建所属布局"))
	bool bAutoRebuildLayoutOwner = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="预览颜色"))
	FLinearColor PreviewColor = FLinearColor(1.0f, 0.55f, 0.1f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="吸附到布局墙线"))
	bool bSnapToLayoutGrid = true;

	UFUNCTION(BlueprintPure, Category="Default")
	ASomeToolLevelLayoutPreviewActor* GetLayoutOwnerActor() const { return LayoutOwner; }

	UFUNCTION(BlueprintPure, Category="Default")
	UBoxComponent* GetDoorBoundsComponent() const { return DoorBoundsComponent; }

private:
	bool bIsApplyingToolSync = false;
	bool bIsInteractiveEditorTransform = false;

#if WITH_EDITOR
protected:
	virtual void EditorApplyTranslation(const FVector& DeltaTranslation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyRotation(const FRotator& DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void PostEditMove(bool bFinished) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
