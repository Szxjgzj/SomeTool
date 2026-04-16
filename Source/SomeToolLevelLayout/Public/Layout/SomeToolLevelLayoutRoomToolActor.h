#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomeToolLevelLayoutRoomToolActor.generated.h"

class ASomeToolLevelLayoutPreviewActor;
class UBoxComponent;
class USceneComponent;
class UTextRenderComponent;
struct FPropertyChangedEvent;

UCLASS(
	BlueprintType,
	CollapseCategories,
	HideCategories=(Actor, Input, Replication, Collision, Cooking, HLOD, Physics, Navigation, LOD, Rendering, WorldPartition, DataLayers),
	AutoExpandCategories=("Default"),
	PrioritizeCategories=("Default"))
class SOMETOOLLEVELLAYOUT_API ASomeToolLevelLayoutRoomToolActor : public AActor
{
	GENERATED_BODY()

public:
	ASomeToolLevelLayoutRoomToolActor();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(CallInEditor, BlueprintCallable, Category="Default", meta=(DisplayName="通知布局Actor更新"))
	void NotifyLayoutOwnerChanged();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="根组件"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="房间范围组件"))
	TObjectPtr<UBoxComponent> RoomBoundsComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="房间ID预览组件"))
	TObjectPtr<UTextRenderComponent> RoomIdPreviewComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="所属布局Actor"))
	TObjectPtr<ASomeToolLevelLayoutPreviewActor> LayoutOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="自动重建所属布局"))
	bool bAutoRebuildLayoutOwner = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="使用显式房间ID"))
	bool bUseExplicitRoomId = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(EditCondition="bUseExplicitRoomId", EditConditionHides, DisplayName="显式房间ID"))
	int32 ExplicitRoomId = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="预览颜色"))
	FLinearColor PreviewColor = FLinearColor(0.15f, 0.55f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="优先级", ToolTip="多个房间工具重叠时，优先级更高的会覆盖更低的。"))
	int32 Priority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="吸附到布局网格"))
	bool bSnapToLayoutGrid = true;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="当前房间ID"))
	int32 ResolvedPreviewRoomId = INDEX_NONE;

	void SetResolvedPreviewRoomId(int32 InRoomId);

	UFUNCTION(BlueprintPure, Category="Default")
	ASomeToolLevelLayoutPreviewActor* GetLayoutOwnerActor() const { return LayoutOwner; }

	UFUNCTION(BlueprintPure, Category="Default")
	UBoxComponent* GetRoomBoundsComponent() const { return RoomBoundsComponent; }

private:
	void UpdateRoomIdPreview();

	bool bIsApplyingToolSync = false;
	bool bIsInteractiveEditorTransform = false;

#if WITH_EDITOR
protected:
	virtual void EditorApplyTranslation(const FVector& DeltaTranslation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyRotation(const FRotator& DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void PostEditMove(bool bFinished) override;
#endif
};
