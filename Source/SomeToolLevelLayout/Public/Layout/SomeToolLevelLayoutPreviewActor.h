#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Layout/SomeToolLevelLayoutTypes.h"
#include "SomeToolLevelLayoutPreviewActor.generated.h"

class UInstancedStaticMeshComponent;
class USceneComponent;
class UStaticMeshComponent;
class UStaticMesh;
class ASomeToolLevelLayoutDoorToolActor;
class ASomeToolLevelLayoutRoomToolActor;
struct FPropertyChangedEvent;

UCLASS(
	BlueprintType,
	CollapseCategories,
	HideCategories=(Actor, Input, Replication, Collision, Cooking, HLOD, Physics, Navigation, LOD, Rendering, WorldPartition, DataLayers),
	AutoExpandCategories=("Default"),
	PrioritizeCategories=("Default"))
class SOMETOOLLEVELLAYOUT_API ASomeToolLevelLayoutPreviewActor : public AActor
{
	GENERATED_BODY()

public:
	ASomeToolLevelLayoutPreviewActor();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION(CallInEditor, BlueprintCallable, Category="Default", meta=(DisplayName="重建布局"))
	void RebuildLayout();

	UFUNCTION(CallInEditor, BlueprintCallable, Category="Default", meta=(DisplayName="清空房间"))
	void ClearRooms();

	UFUNCTION(BlueprintPure, Category="Runtime", meta=(DisplayName="获取地面实例数据"))
	TArray<FSomeToolFloorInstanceInfo> GetInstanceInfos_Floor() const;

	UFUNCTION(BlueprintPure, Category="Runtime", meta=(DisplayName="获取基础墙体实例数据"))
	TArray<FSomeToolWallInstanceInfo> GetInstanceInfos_BaseWall() const;

	UFUNCTION(BlueprintPure, Category="Runtime", meta=(DisplayName="获取最终墙体实例数据"))
	TArray<FSomeToolWallInstanceInfo> GetInstanceInfos_Wall() const;

	UFUNCTION(BlueprintPure, Category="Runtime", meta=(DisplayName="获取开口实例数据"))
	TArray<FSomeToolOpeningInstanceInfo> GetInstanceInfos_Opening() const;

	UFUNCTION(BlueprintPure, Category="Runtime", meta=(DisplayName="获取拐角实例数据"))
	TArray<FSomeToolCornerInstanceInfo> GetInstanceInfos_Corner() const;

	const TArray<FSomeToolFloorInstanceInfo>& GetFloorInstanceInfos() const { return GeneratedFloorInstanceInfos; }
	const TArray<FSomeToolWallInstanceInfo>& GetBaseWallInstanceInfos() const { return GeneratedBaseWallInstanceInfos; }
	const TArray<FSomeToolWallInstanceInfo>& GetWallInstanceInfos() const { return GeneratedWallInstanceInfos; }
	const TArray<FSomeToolOpeningInstanceInfo>& GetOpeningInstanceInfos() const { return GeneratedOpeningInstanceInfos; }
	const TArray<FSomeToolCornerInstanceInfo>& GetCornerInstanceInfos() const { return GeneratedCornerInstanceInfos; }

	bool SnapRoomToolActorToGrid(ASomeToolLevelLayoutRoomToolActor& RoomToolActor) const;
	bool SnapDoorToolActorToGrid(ASomeToolLevelLayoutDoorToolActor& DoorToolActor) const;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="根组件"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="总网格预览组件"))
	TObjectPtr<UStaticMeshComponent> GridPreviewComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="房间地面预览组件"))
	TObjectPtr<UInstancedStaticMeshComponent> FloorPreviewComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="墙体预览组件"))
	TObjectPtr<UInstancedStaticMeshComponent> WallPreviewComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Default", meta=(DisplayName="拐角预览组件"))
	TObjectPtr<UInstancedStaticMeshComponent> CornerPreviewComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ClampMin="1", DisplayName="网格宽度"))
	int32 GridWidth = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ClampMin="1", DisplayName="网格高度"))
	int32 GridHeight = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ClampMin="1.0", DisplayName="单元尺寸"))
	float CellSize = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="网格以Actor为中心"))
	bool bCenterGridOnActor = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="自动重建"))
	bool bAutoRebuild = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="运行时保留预览模型", ToolTip="开启后，运行时会继续显示当前LayoutActor的预览网格；关闭后，运行时只保留数据，不显示这些预览模型。"))
	bool bKeepPreviewVisibleInGame = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="使用房间工具Actor"))
	bool bUseRoomToolActors = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="使用门窗工具Actor"))
	bool bUseDoorToolActors = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="手动房间矩形", EditCondition="!bUseRoomToolActors", EditConditionHides, ToolTip="关闭“使用房间工具Actor”后，可直接在这里手动填写房间矩形数据。"))
	TArray<FSomeToolRoomRect> RoomRects;

	UPROPERTY(Transient, BlueprintReadOnly, Category="Debug", AdvancedDisplay, meta=(DisplayName="缓存布局结果"))
	FSomeToolLayoutBuildResult CachedLayout;

	UPROPERTY(Transient, BlueprintReadOnly, Category="Debug", AdvancedDisplay, meta=(DisplayName="收集到的房间工具Actor"))
	TArray<TObjectPtr<ASomeToolLevelLayoutRoomToolActor>> CollectedRoomToolActors;

	UPROPERTY(Transient, BlueprintReadOnly, Category="Debug", AdvancedDisplay, meta=(DisplayName="收集到的门窗工具Actor"))
	TArray<TObjectPtr<ASomeToolLevelLayoutDoorToolActor>> CollectedDoorToolActors;

	UPROPERTY(Transient, BlueprintReadOnly, Category="Debug", AdvancedDisplay, meta=(DisplayName="解析后的房间矩形"))
	TArray<FSomeToolRoomRect> ResolvedRoomRects;

	UPROPERTY(Transient, BlueprintReadOnly, Category="Debug", AdvancedDisplay, meta=(DisplayName="解析后的门窗开口"))
	TArray<FSomeToolWallOpening> ResolvedWallOpenings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="总地面网格模型"))
	TObjectPtr<UStaticMesh> GridMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="房间地面模型"))
	TObjectPtr<UStaticMesh> FloorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="墙体模型"))
	TObjectPtr<UStaticMesh> WallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(DisplayName="拐角模型"))
	TObjectPtr<UStaticMesh> CornerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ClampMin="1.0", DisplayName="总网格厚度"))
	float GridThickness = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="总网格Z偏移"))
	float GridOffsetZ = -5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ClampMin="1.0", DisplayName="地面厚度"))
	float FloorThickness = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ClampMin="1.0", DisplayName="墙体厚度"))
	float WallThickness = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="房间高度吸附"))
	bool bSnapRoomToolHeightToStep = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(ClampMin="1.0", EditCondition="bSnapRoomToolHeightToStep", EditConditionHides, DisplayName="房间高度吸附步长"))
	float RoomToolHeightSnapStep = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="房间底部高度吸附"))
	bool bSnapRoomToolBaseHeightToStep = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(ClampMin="1.0", EditCondition="bSnapRoomToolBaseHeightToStep", EditConditionHides, DisplayName="房间底部吸附步长"))
	float RoomToolBaseHeightSnapStep = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="拖拽时延后重建"))
	bool bDeferRoomToolRebuildWhileDragging = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="大量地面时合并预览"))
	bool bUseMergedFloorPreviewWhenDense = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(ClampMin="1", DisplayName="合并预览阈值"))
	int32 DenseFloorPreviewCellThreshold = 4096;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(DisplayName="启用异步布局构建"))
	bool bUseAsyncLayoutBuild = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", AdvancedDisplay, meta=(ClampMin="1", DisplayName="异步构建阈值"))
	int32 AsyncBuildCellThreshold = 16384;

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void CollectRoomToolActors();
	void CollectDoorToolActors();
	void ResetRoomToolActorPreviewIds() const;
	void ResolveRoomRects();
	void ResolveWallOpenings();
	void RebuildInstanceInfos();
	void RefreshPreviewComponents();
	bool ShouldRenderPreviewComponentsInCurrentWorld() const;
	bool ShouldUseAsyncLayoutBuild() const;
	void QueueAsyncLayoutBuild();
	void StartQueuedAsyncLayoutBuild();
	void HandleAsyncLayoutBuildCompleted(
		int32 BuildGeneration,
		int32 BuiltGridWidth,
		int32 BuiltGridHeight,
		TArray<FSomeToolRoomRect>&& BuiltRoomRects,
		FSomeToolLayoutBuildResult&& BuildResult);
	void UpdateBuildCacheState(const TArray<FSomeToolRoomRect>& AppliedRoomRects);
	FVector GetGridMinLocal() const;
	FTransform BuildGridTransform() const;
	bool BuildRoomRectFromToolActor(
		const ASomeToolLevelLayoutRoomToolActor& RoomToolActor,
		int32 AssignedRoomId,
		FSomeToolRoomRect& OutRoomRect) const;
	bool BuildWallOpeningFromToolActor(
		const ASomeToolLevelLayoutDoorToolActor& DoorToolActor,
		FSomeToolWallOpening& OutWallOpening) const;
	FSomeToolFloorInstanceInfo BuildFloorInstanceInfo(const FSomeToolLayoutFloorRegion& FloorRegion) const;
	FSomeToolWallInstanceInfo BuildWallInstanceInfo(const FSomeToolLayoutWallSegment& WallSegment) const;
	FSomeToolOpeningInstanceInfo BuildOpeningInstanceInfo(const FSomeToolWallOpening& WallOpening) const;
	void BuildCornerInstanceInfos(const TArray<FSomeToolLayoutWallSegment>& WallSegments);
	FLinearColor GetRoomPreviewColor(int32 RoomId) const;
	FTransform BuildFloorPreviewTransform(const FSomeToolGridCell& Cell) const;
	FTransform BuildFloorRegionPreviewTransform(const FSomeToolLayoutFloorRegion& FloorRegion) const;
	FTransform BuildWallPreviewTransform(const FSomeToolLayoutWallSegment& WallSegment) const;
	FTransform BuildCornerPreviewTransform(const FIntPoint& GridPoint, float BaseHeight, float VerticalSize) const;
	FTransform BuildWorldTransform(const FTransform& LocalTransform) const;
	FTransform BuildLocalTransformFromWorldFields(const FVector& Location, const FRotator& Rotation, const FVector& Scale) const;
	static FTransform BuildPreviewTransform(const FVector& Location, const FRotator& Rotation, const FVector& Scale);
	static void FillTransformFields(const FTransform& Transform, FVector& OutLocation, FRotator& OutRotation, FVector& OutScale);
	static float GetSafeMeshDimension(const UStaticMesh* Mesh, EAxis::Type Axis);

	UPROPERTY(Transient)
	TArray<FSomeToolFloorInstanceInfo> GeneratedFloorInstanceInfos;

	UPROPERTY(Transient)
	TArray<FSomeToolWallInstanceInfo> GeneratedBaseWallInstanceInfos;

	UPROPERTY(Transient)
	TArray<FSomeToolWallInstanceInfo> GeneratedWallInstanceInfos;

	UPROPERTY(Transient)
	TArray<FSomeToolOpeningInstanceInfo> GeneratedOpeningInstanceInfos;

	UPROPERTY(Transient)
	TArray<FSomeToolCornerInstanceInfo> GeneratedCornerInstanceInfos;

	UPROPERTY(Transient)
	bool bHasCachedBuildState = false;

	UPROPERTY(Transient)
	int32 CachedBuildGridWidth = 0;

	UPROPERTY(Transient)
	int32 CachedBuildGridHeight = 0;

	UPROPERTY(Transient)
	float CachedBuildCellSize = 0.0f;

	UPROPERTY(Transient)
	bool bCachedCenterGridOnActor = true;

	UPROPERTY(Transient)
	float CachedBuildGridThickness = 0.0f;

	UPROPERTY(Transient)
	float CachedBuildGridOffsetZ = 0.0f;

	UPROPERTY(Transient)
	float CachedBuildFloorThickness = 0.0f;

	UPROPERTY(Transient)
	float CachedBuildWallThickness = 0.0f;

	UPROPERTY(Transient)
	bool bCachedUseMergedFloorPreviewWhenDense = true;

	UPROPERTY(Transient)
	bool bCachedKeepPreviewVisibleInGame = false;

	UPROPERTY(Transient)
	int32 CachedDenseFloorPreviewCellThreshold = 0;

	UPROPERTY(Transient)
	TObjectPtr<UStaticMesh> CachedGridMesh;

	UPROPERTY(Transient)
	TObjectPtr<UStaticMesh> CachedFloorMesh;

	UPROPERTY(Transient)
	TObjectPtr<UStaticMesh> CachedWallMesh;

	UPROPERTY(Transient)
	TObjectPtr<UStaticMesh> CachedCornerMesh;

	UPROPERTY(Transient)
	TArray<FSomeToolRoomRect> CachedBuildRoomRects;

	UPROPERTY(Transient)
	TArray<FSomeToolWallOpening> CachedBuildWallOpenings;

	UPROPERTY(Transient)
	TMap<int32, FLinearColor> RoomPreviewColors;

	UPROPERTY(Transient)
	TArray<FLinearColor> WallPreviewColors;

	UPROPERTY(Transient)
	TArray<FLinearColor> CornerPreviewColors;

	int32 LatestRequestedAsyncBuildGeneration = 0;
	int32 ActiveAsyncBuildGeneration = 0;
	int32 ActiveBuildGridWidth = 0;
	int32 ActiveBuildGridHeight = 0;
	bool bAsyncBuildInProgress = false;
	bool bHasQueuedAsyncBuildRequest = false;
	int32 QueuedBuildGridWidth = 0;
	int32 QueuedBuildGridHeight = 0;
	TArray<FSomeToolRoomRect> ActiveBuildRoomRects;
	TArray<FSomeToolRoomRect> QueuedBuildRoomRects;
};
