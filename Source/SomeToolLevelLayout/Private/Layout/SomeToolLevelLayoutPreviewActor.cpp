#include "Layout/SomeToolLevelLayoutPreviewActor.h"

#include "Algo/Sort.h"
#include "Async/Async.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Layout/SomeToolLevelLayoutDoorToolActor.h"
#include "Layout/SomeToolLevelLayoutRoomToolActor.h"
#include "Layout/SomeToolLevelLayoutSolver.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
bool AreNearlyEqual(const float Left, const float Right)
{
	return FMath::IsNearlyEqual(Left, Right, KINDA_SMALL_NUMBER);
}

bool AreRoomRectsEqual(const FSomeToolRoomRect& Left, const FSomeToolRoomRect& Right)
{
	return Left.RoomId == Right.RoomId
		&& Left.Origin == Right.Origin
		&& Left.Width == Right.Width
		&& Left.Height == Right.Height
		&& Left.PreviewColor.Equals(Right.PreviewColor)
		&& AreNearlyEqual(Left.HeightOffset, Right.HeightOffset)
		&& AreNearlyEqual(Left.VerticalSize, Right.VerticalSize)
		&& Left.Priority == Right.Priority;
}

bool AreRoomRectArraysEqual(const TArray<FSomeToolRoomRect>& Left, const TArray<FSomeToolRoomRect>& Right)
{
	if (Left.Num() != Right.Num())
	{
		return false;
	}

	for (int32 Index = 0; Index < Left.Num(); ++Index)
	{
		if (!AreRoomRectsEqual(Left[Index], Right[Index]))
		{
			return false;
		}
	}

	return true;
}

bool AreWallOpeningsEqual(const FSomeToolWallOpening& Left, const FSomeToolWallOpening& Right)
{
	return Left.Orientation == Right.Orientation
		&& Left.Mode == Right.Mode
		&& Left.GridPoint == Right.GridPoint
		&& Left.Length == Right.Length
		&& AreNearlyEqual(Left.HeightOffset, Right.HeightOffset)
		&& AreNearlyEqual(Left.VerticalSize, Right.VerticalSize);
}

bool AreWallOpeningArraysEqual(const TArray<FSomeToolWallOpening>& Left, const TArray<FSomeToolWallOpening>& Right)
{
	if (Left.Num() != Right.Num())
	{
		return false;
	}

	for (int32 Index = 0; Index < Left.Num(); ++Index)
	{
		if (!AreWallOpeningsEqual(Left[Index], Right[Index]))
		{
			return false;
		}
	}

	return true;
}

int32 GetClampedCellCount(const float FullSize, const float CellSize, const int32 MaxCells)
{
	const int32 DesiredCells = FMath::Max(1, FMath::RoundToInt(FullSize / CellSize));
	return FMath::Clamp(DesiredCells, 1, FMath::Max(MaxCells, 1));
}

int32 GetClampedOriginCell(
	const float LocalCenter,
	const float GridMin,
	const float CellSize,
	const int32 CellCount,
	const int32 GridLimit)
{
	const int32 RawOrigin = FMath::RoundToInt(((LocalCenter - GridMin) / CellSize) - (CellCount * 0.5f));
	return FMath::Clamp(RawOrigin, 0, FMath::Max(0, GridLimit - CellCount));
}

float SnapValueToStep(const float Value, const float Step, const float MinValue = 0.0f)
{
	const float SafeStep = FMath::Max(Step, 1.0f);
	return FMath::Max(FMath::RoundToFloat(Value / SafeStep) * SafeStep, MinValue);
}

float SnapAngleToRightAngle(const float AngleDegrees)
{
	return 90.0f * FMath::RoundToFloat(AngleDegrees / 90.0f);
}

ESomeToolLayoutWallOrientation GetWallOrientationFromLocalYaw(const float LocalYaw)
{
	const float SnappedYaw = FRotator::NormalizeAxis(SnapAngleToRightAngle(LocalYaw));
	return (FMath::Abs(SnappedYaw) > 45.0f && FMath::Abs(SnappedYaw) <= 135.0f)
		? ESomeToolLayoutWallOrientation::Vertical
		: ESomeToolLayoutWallOrientation::Horizontal;
}

int32 GetWallAxisStart(const FSomeToolLayoutWallSegment& WallSegment)
{
	return WallSegment.Orientation == ESomeToolLayoutWallOrientation::Vertical
		? WallSegment.GridPoint.Y
		: WallSegment.GridPoint.X;
}

int32 GetOpeningAxisStart(const FSomeToolWallOpening& WallOpening)
{
	return WallOpening.Orientation == ESomeToolLayoutWallOrientation::Vertical
		? WallOpening.GridPoint.Y
		: WallOpening.GridPoint.X;
}

float GetOpeningAxisCenter(const FSomeToolWallOpening& WallOpening)
{
	return static_cast<float>(GetOpeningAxisStart(WallOpening)) + static_cast<float>(WallOpening.Length) * 0.5f;
}

bool IsSameWallLine(const FSomeToolLayoutWallSegment& WallSegment, const FSomeToolWallOpening& WallOpening)
{
	if (WallSegment.Orientation != WallOpening.Orientation)
	{
		return false;
	}

	return WallSegment.Orientation == ESomeToolLayoutWallOrientation::Vertical
		? WallSegment.GridPoint.X == WallOpening.GridPoint.X
		: WallSegment.GridPoint.Y == WallOpening.GridPoint.Y;
}

bool ShouldApplyOpeningMode(const FSomeToolWallOpening& WallOpening, const bool bWholeSegmentOnly)
{
	return bWholeSegmentOnly
		? WallOpening.Mode == ESomeToolOpeningMode::Segment
		: WallOpening.Mode == ESomeToolOpeningMode::Bounds;
}

bool ShouldRemoveWholeWallSegment(
	const FSomeToolLayoutWallSegment& WallSegment,
	const FSomeToolWallOpening& WallOpening)
{
	if (!IsSameWallLine(WallSegment, WallOpening))
	{
		return false;
	}

	const float OpeningCenter = GetOpeningAxisCenter(WallOpening);
	const int32 SegmentStart = GetWallAxisStart(WallSegment);
	const int32 SegmentEnd = SegmentStart + WallSegment.Length;
	return OpeningCenter > static_cast<float>(SegmentStart) && OpeningCenter < static_cast<float>(SegmentEnd);
}

void AddWallSegmentPiece(
	TArray<FSomeToolLayoutWallSegment>& OutSegments,
	const FSomeToolLayoutWallSegment& TemplateSegment,
	const int32 SegmentStart,
	const int32 SegmentLength,
	const float SegmentBase,
	const float SegmentVerticalSize)
{
	if (SegmentLength <= 0 || SegmentVerticalSize <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	FSomeToolLayoutWallSegment& Piece = OutSegments.AddDefaulted_GetRef();
	Piece = TemplateSegment;
	Piece.Length = SegmentLength;
	Piece.HeightOffset = SegmentBase;
	Piece.VerticalSize = SegmentVerticalSize;

	if (TemplateSegment.Orientation == ESomeToolLayoutWallOrientation::Vertical)
	{
		Piece.GridPoint = FIntPoint(TemplateSegment.GridPoint.X, SegmentStart);
	}
	else
	{
		Piece.GridPoint = FIntPoint(SegmentStart, TemplateSegment.GridPoint.Y);
	}
}

void BuildVisibleWallSegments(
	const TArray<FSomeToolLayoutWallSegment>& SourceWallSegments,
	const float FloorThickness,
	TArray<FSomeToolLayoutWallSegment>& OutWallSegments)
{
	OutWallSegments.Reset();
	OutWallSegments.Reserve(SourceWallSegments.Num());

	for (const FSomeToolLayoutWallSegment& SourceWallSegment : SourceWallSegments)
	{
		FSomeToolLayoutWallSegment& VisibleWallSegment = OutWallSegments.AddDefaulted_GetRef();
		VisibleWallSegment = SourceWallSegment;
		VisibleWallSegment.HeightOffset = SourceWallSegment.HeightOffset + FloorThickness;
		VisibleWallSegment.VerticalSize = FMath::Max(SourceWallSegment.VerticalSize - FloorThickness, 1.0f);
	}
}

void ApplyWallOpeningsToSegments(
	const TArray<FSomeToolLayoutWallSegment>& SourceWallSegments,
	const TArray<FSomeToolWallOpening>& WallOpenings,
	const bool bWholeSegmentOnly,
	TArray<FSomeToolLayoutWallSegment>& OutWallSegments)
{
	OutWallSegments.Reset();
	OutWallSegments.Reserve(SourceWallSegments.Num());

	for (const FSomeToolLayoutWallSegment& SourceWallSegment : SourceWallSegments)
	{
		TArray<FSomeToolLayoutWallSegment> WorkingSegments;
		WorkingSegments.Add(SourceWallSegment);

		for (const FSomeToolWallOpening& WallOpening : WallOpenings)
		{
			if (!ShouldApplyOpeningMode(WallOpening, bWholeSegmentOnly) || !IsSameWallLine(SourceWallSegment, WallOpening))
			{
				continue;
			}

			TArray<FSomeToolLayoutWallSegment> NextSegments;
			for (const FSomeToolLayoutWallSegment& WorkingSegment : WorkingSegments)
			{
				if (!IsSameWallLine(WorkingSegment, WallOpening))
				{
					NextSegments.Add(WorkingSegment);
					continue;
				}

				if (bWholeSegmentOnly)
				{
					if (!ShouldRemoveWholeWallSegment(WorkingSegment, WallOpening))
					{
						NextSegments.Add(WorkingSegment);
					}
					continue;
				}

				const int32 SegmentStart = GetWallAxisStart(WorkingSegment);
				const int32 SegmentEnd = SegmentStart + WorkingSegment.Length;
				const int32 OpeningStart = GetOpeningAxisStart(WallOpening);
				const int32 OpeningEnd = OpeningStart + WallOpening.Length;
				const int32 OverlapStart = FMath::Max(SegmentStart, OpeningStart);
				const int32 OverlapEnd = FMath::Min(SegmentEnd, OpeningEnd);

				const float SegmentBase = WorkingSegment.HeightOffset;
				const float SegmentTop = WorkingSegment.HeightOffset + WorkingSegment.VerticalSize;
				const float OpeningBase = WallOpening.HeightOffset;
				const float OpeningTop = WallOpening.HeightOffset + WallOpening.VerticalSize;
				const float OverlapBase = FMath::Max(SegmentBase, OpeningBase);
				const float OverlapTop = FMath::Min(SegmentTop, OpeningTop);

				if (OverlapStart >= OverlapEnd || OverlapBase >= OverlapTop)
				{
					NextSegments.Add(WorkingSegment);
					continue;
				}

				AddWallSegmentPiece(
					NextSegments,
					WorkingSegment,
					SegmentStart,
					OverlapStart - SegmentStart,
					SegmentBase,
					WorkingSegment.VerticalSize);
				AddWallSegmentPiece(
					NextSegments,
					WorkingSegment,
					OverlapEnd,
					SegmentEnd - OverlapEnd,
					SegmentBase,
					WorkingSegment.VerticalSize);

				const int32 OverlapLength = OverlapEnd - OverlapStart;
				AddWallSegmentPiece(
					NextSegments,
					WorkingSegment,
					OverlapStart,
					OverlapLength,
					SegmentBase,
					OverlapBase - SegmentBase);
				AddWallSegmentPiece(
					NextSegments,
					WorkingSegment,
					OverlapStart,
					OverlapLength,
					OverlapTop,
					SegmentTop - OverlapTop);
			}

			WorkingSegments = MoveTemp(NextSegments);
			if (WorkingSegments.Num() <= 0)
			{
				break;
			}
		}

		for (const FSomeToolLayoutWallSegment& WorkingSegment : WorkingSegments)
		{
			if (WorkingSegment.Length > 0 && WorkingSegment.VerticalSize > KINDA_SMALL_NUMBER)
			{
				OutWallSegments.Add(WorkingSegment);
			}
		}
	}
}
}

ASomeToolLevelLayoutPreviewActor::ASomeToolLevelLayoutPreviewActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultPlaneMeshFinder(TEXT("/Engine/BasicShapes/Plane.Plane"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultCubeMeshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultGridMaterialFinder(
		TEXT("/Script/Engine.MaterialInstanceConstant'/Engine/OpenWorldTemplate/LandscapeMaterial/MI_ProcGrid.MI_ProcGrid'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultFallbackGridMaterialFinder(
		TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	GridPreviewComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridPreview"));
	GridPreviewComponent->SetupAttachment(SceneRoot);
	GridPreviewComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GridPreviewComponent->SetGenerateOverlapEvents(false);
	GridPreviewComponent->SetCastShadow(false);
	GridPreviewComponent->SetHiddenInGame(true);
	GridPreviewComponent->SetCanEverAffectNavigation(false);

	FloorPreviewComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorPreview"));
	FloorPreviewComponent->SetupAttachment(SceneRoot);
	FloorPreviewComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FloorPreviewComponent->SetGenerateOverlapEvents(false);
	FloorPreviewComponent->SetCastShadow(false);
	FloorPreviewComponent->SetHiddenInGame(true);
	FloorPreviewComponent->SetCanEverAffectNavigation(false);
	FloorPreviewComponent->NumCustomDataFloats = 4;

	WallPreviewComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallPreview"));
	WallPreviewComponent->SetupAttachment(SceneRoot);
	WallPreviewComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WallPreviewComponent->SetGenerateOverlapEvents(false);
	WallPreviewComponent->SetCastShadow(false);
	WallPreviewComponent->SetHiddenInGame(true);
	WallPreviewComponent->SetCanEverAffectNavigation(false);
	WallPreviewComponent->NumCustomDataFloats = 4;

	CornerPreviewComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CornerPreview"));
	CornerPreviewComponent->SetupAttachment(SceneRoot);
	CornerPreviewComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CornerPreviewComponent->SetGenerateOverlapEvents(false);
	CornerPreviewComponent->SetCastShadow(false);
	CornerPreviewComponent->SetHiddenInGame(true);
	CornerPreviewComponent->SetCanEverAffectNavigation(false);
	CornerPreviewComponent->NumCustomDataFloats = 4;

	GridMesh = DefaultPlaneMeshFinder.Succeeded() ? DefaultPlaneMeshFinder.Object : nullptr;
	FloorMesh = DefaultCubeMeshFinder.Succeeded() ? DefaultCubeMeshFinder.Object : nullptr;
	WallMesh = DefaultCubeMeshFinder.Succeeded() ? DefaultCubeMeshFinder.Object : nullptr;
	CornerMesh = DefaultCubeMeshFinder.Succeeded() ? DefaultCubeMeshFinder.Object : nullptr;

	if (DefaultGridMaterialFinder.Succeeded())
	{
		GridPreviewComponent->SetMaterial(0, DefaultGridMaterialFinder.Object);
	}
	else if (DefaultFallbackGridMaterialFinder.Succeeded())
	{
		GridPreviewComponent->SetMaterial(0, DefaultFallbackGridMaterialFinder.Object);
	}
}

void ASomeToolLevelLayoutPreviewActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bAutoRebuild)
	{
		RebuildLayout();
	}
	else
	{
		RefreshPreviewComponents();
	}
}

void ASomeToolLevelLayoutPreviewActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (const UWorld* World = GetWorld(); World && World->IsGameWorld())
	{
		bHasCachedBuildState = false;
		bHasQueuedAsyncBuildRequest = false;
		bAsyncBuildInProgress = false;
		LatestRequestedAsyncBuildGeneration = 0;
		ActiveAsyncBuildGeneration = 0;
		ActiveBuildGridWidth = 0;
		ActiveBuildGridHeight = 0;
		QueuedBuildGridWidth = 0;
		QueuedBuildGridHeight = 0;
		ActiveBuildRoomRects.Reset();
		QueuedBuildRoomRects.Reset();
		RebuildLayout();
	}
}

void ASomeToolLevelLayoutPreviewActor::RebuildLayout()
{
	GridWidth = FMath::Max(GridWidth, 1);
	GridHeight = FMath::Max(GridHeight, 1);
	CellSize = FMath::Max(CellSize, 1.0f);
	GridThickness = FMath::Max(GridThickness, 1.0f);
	FloorThickness = FMath::Max(FloorThickness, 1.0f);
	WallThickness = FMath::Max(WallThickness, 1.0f);
	DenseFloorPreviewCellThreshold = FMath::Max(DenseFloorPreviewCellThreshold, 1);

	ResolveRoomRects();
	ResolveWallOpenings();

	const bool bLayoutShapeChanged = !bHasCachedBuildState
		|| CachedBuildGridWidth != GridWidth
		|| CachedBuildGridHeight != GridHeight
		|| !AreRoomRectArraysEqual(CachedBuildRoomRects, ResolvedRoomRects);
	const bool bWallOpeningsChanged = !bHasCachedBuildState
		|| !AreWallOpeningArraysEqual(CachedBuildWallOpenings, ResolvedWallOpenings);

	if (bLayoutShapeChanged && ShouldUseAsyncLayoutBuild())
	{
		QueueAsyncLayoutBuild();

		const bool bPreviewChangedWhileBuilding = !AreNearlyEqual(CachedBuildGridThickness, GridThickness)
			|| !AreNearlyEqual(CachedBuildGridOffsetZ, GridOffsetZ)
			|| bCachedUseMergedFloorPreviewWhenDense != bUseMergedFloorPreviewWhenDense
			|| bCachedKeepPreviewVisibleInGame != bKeepPreviewVisibleInGame
			|| bWallOpeningsChanged
			|| CachedDenseFloorPreviewCellThreshold != DenseFloorPreviewCellThreshold
			|| CachedGridMesh != GridMesh
			|| CachedFloorMesh != FloorMesh
			|| CachedWallMesh != WallMesh
			|| CachedCornerMesh != CornerMesh;

		if (bPreviewChangedWhileBuilding)
		{
			if (bWallOpeningsChanged)
			{
				RebuildInstanceInfos();
			}
			RefreshPreviewComponents();
			UpdateBuildCacheState(CachedBuildRoomRects);
		}

		return;
	}

	const bool bInstanceDataChanged = bLayoutShapeChanged
		|| bWallOpeningsChanged
		|| !AreNearlyEqual(CachedBuildCellSize, CellSize)
		|| bCachedCenterGridOnActor != bCenterGridOnActor
		|| !AreNearlyEqual(CachedBuildFloorThickness, FloorThickness)
		|| !AreNearlyEqual(CachedBuildWallThickness, WallThickness);

	const bool bPreviewChanged = bInstanceDataChanged
		|| !AreNearlyEqual(CachedBuildGridThickness, GridThickness)
		|| !AreNearlyEqual(CachedBuildGridOffsetZ, GridOffsetZ)
		|| bCachedUseMergedFloorPreviewWhenDense != bUseMergedFloorPreviewWhenDense
		|| bCachedKeepPreviewVisibleInGame != bKeepPreviewVisibleInGame
		|| CachedDenseFloorPreviewCellThreshold != DenseFloorPreviewCellThreshold
		|| CachedGridMesh != GridMesh
		|| CachedFloorMesh != FloorMesh
		|| CachedWallMesh != WallMesh
		|| CachedCornerMesh != CornerMesh;

	const bool bShouldRenderPreviewComponents = ShouldRenderPreviewComponentsInCurrentWorld();
	const bool bUseMergedFloorPreview = bUseMergedFloorPreviewWhenDense
		&& GeneratedFloorInstanceInfos.Num() >= DenseFloorPreviewCellThreshold;
	const int32 ExpectedFloorPreviewInstanceCount = (bShouldRenderPreviewComponents && FloorMesh != nullptr)
		? (bUseMergedFloorPreview ? CachedLayout.FloorRegions.Num() : GeneratedFloorInstanceInfos.Num())
		: 0;
	const int32 ExpectedWallPreviewInstanceCount = (bShouldRenderPreviewComponents && WallMesh != nullptr)
		? GeneratedWallInstanceInfos.Num()
		: 0;
	const int32 ExpectedCornerPreviewInstanceCount = (bShouldRenderPreviewComponents && CornerMesh != nullptr)
		? GeneratedCornerInstanceInfos.Num()
		: 0;
	const bool bPreviewComponentsNeedRefresh = (bShouldRenderPreviewComponents
			? (GridMesh != nullptr && !GridPreviewComponent->GetVisibleFlag())
			: GridPreviewComponent->GetVisibleFlag())
		|| FloorPreviewComponent->GetInstanceCount() != ExpectedFloorPreviewInstanceCount
		|| WallPreviewComponent->GetInstanceCount() != ExpectedWallPreviewInstanceCount
		|| CornerPreviewComponent->GetInstanceCount() != ExpectedCornerPreviewInstanceCount;

	if (!bLayoutShapeChanged && !bInstanceDataChanged && !bPreviewChanged && !bPreviewComponentsNeedRefresh)
	{
		return;
	}

	if (bLayoutShapeChanged)
	{
		CachedLayout = FSomeToolLevelLayoutSolver::BuildLayout(GridWidth, GridHeight, ResolvedRoomRects);
	}

	if (bInstanceDataChanged)
	{
		RebuildInstanceInfos();
	}

	if (bPreviewChanged || bPreviewComponentsNeedRefresh)
	{
		RefreshPreviewComponents();
	}

	UpdateBuildCacheState(ResolvedRoomRects);
}

void ASomeToolLevelLayoutPreviewActor::ClearRooms()
{
	ResetRoomToolActorPreviewIds();
	RoomRects.Reset();
	ResolvedRoomRects.Reset();
	ResolvedWallOpenings.Reset();
	CollectedRoomToolActors.Reset();
	CollectedDoorToolActors.Reset();
	CachedLayout = FSomeToolLevelLayoutSolver::BuildLayout(GridWidth, GridHeight, ResolvedRoomRects);
	RebuildInstanceInfos();
	RefreshPreviewComponents();

	bHasQueuedAsyncBuildRequest = false;
	LatestRequestedAsyncBuildGeneration = 0;
	ActiveAsyncBuildGeneration = 0;
	ActiveBuildGridWidth = 0;
	ActiveBuildGridHeight = 0;
	ActiveBuildRoomRects.Reset();
	QueuedBuildGridWidth = 0;
	QueuedBuildGridHeight = 0;
	QueuedBuildRoomRects.Reset();
	UpdateBuildCacheState(ResolvedRoomRects);
}

TArray<FSomeToolFloorInstanceInfo> ASomeToolLevelLayoutPreviewActor::GetInstanceInfos_Floor() const
{
	return GeneratedFloorInstanceInfos;
}

TArray<FSomeToolWallInstanceInfo> ASomeToolLevelLayoutPreviewActor::GetInstanceInfos_BaseWall() const
{
	return GeneratedBaseWallInstanceInfos;
}

TArray<FSomeToolWallInstanceInfo> ASomeToolLevelLayoutPreviewActor::GetInstanceInfos_Wall() const
{
	return GeneratedWallInstanceInfos;
}

TArray<FSomeToolOpeningInstanceInfo> ASomeToolLevelLayoutPreviewActor::GetInstanceInfos_Opening() const
{
	return GeneratedOpeningInstanceInfos;
}

TArray<FSomeToolCornerInstanceInfo> ASomeToolLevelLayoutPreviewActor::GetInstanceInfos_Corner() const
{
	return GeneratedCornerInstanceInfos;
}

bool ASomeToolLevelLayoutPreviewActor::SnapRoomToolActorToGrid(ASomeToolLevelLayoutRoomToolActor& RoomToolActor) const
{
	UBoxComponent* RoomBoundsComponent = RoomToolActor.GetRoomBoundsComponent();
	if (!RoomBoundsComponent)
	{
		return false;
	}

	const float SafeCellSize = FMath::Max(CellSize, 1.0f);
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector CurrentLocalCenter = GetActorTransform().InverseTransformPosition(RoomBoundsComponent->GetComponentLocation());
	const FVector CurrentWorldExtent = RoomBoundsComponent->GetScaledBoxExtent();
	const FVector CurrentUnscaledExtent = RoomBoundsComponent->GetUnscaledBoxExtent();
	const FVector CurrentBoundsCenterWorld = RoomBoundsComponent->GetComponentLocation();
	const FVector CurrentActorToBoundsOffsetWorld = CurrentBoundsCenterWorld - RoomToolActor.GetActorLocation();

	const int32 WidthInCells = GetClampedCellCount(CurrentWorldExtent.X * 2.0f, SafeCellSize, GridWidth);
	const int32 HeightInCells = GetClampedCellCount(CurrentWorldExtent.Y * 2.0f, SafeCellSize, GridHeight);
	const int32 OriginX = GetClampedOriginCell(CurrentLocalCenter.X, GridMinLocal.X, SafeCellSize, WidthInCells, GridWidth);
	const int32 OriginY = GetClampedOriginCell(CurrentLocalCenter.Y, GridMinLocal.Y, SafeCellSize, HeightInCells, GridHeight);
	float SnappedBaseHeight = CurrentLocalCenter.Z - CurrentWorldExtent.Z;
	if (bSnapRoomToolBaseHeightToStep)
	{
		SnappedBaseHeight = SnapValueToStep(SnappedBaseHeight, RoomToolBaseHeightSnapStep);
	}

	float DesiredHeight = CurrentWorldExtent.Z * 2.0f;
	if (bSnapRoomToolHeightToStep)
	{
		DesiredHeight = SnapValueToStep(DesiredHeight, RoomToolHeightSnapStep, FloorThickness + 1.0f);
	}
	const float DesiredExtentZ = DesiredHeight * 0.5f;

	const FVector SnappedBoundsCenterLocal(
		GridMinLocal.X + (OriginX + WidthInCells * 0.5f) * SafeCellSize,
		GridMinLocal.Y + (OriginY + HeightInCells * 0.5f) * SafeCellSize,
		SnappedBaseHeight + DesiredExtentZ);

	const FVector DesiredBoundsCenterWorld = GetActorTransform().TransformPosition(SnappedBoundsCenterLocal);
	const FVector DesiredWorldLocation = DesiredBoundsCenterWorld - CurrentActorToBoundsOffsetWorld;
	const FRotator DesiredWorldRotation = GetActorRotation();
	const FVector DesiredWorldScale = FVector::OneVector;
	const FVector DesiredExtent(
		WidthInCells * SafeCellSize * 0.5f,
		HeightInCells * SafeCellSize * 0.5f,
		FMath::Max(DesiredExtentZ, 1.0f));

	const bool bActorLocationChanged = !RoomToolActor.GetActorLocation().Equals(DesiredWorldLocation, KINDA_SMALL_NUMBER);
	const bool bActorRotationChanged = !RoomToolActor.GetActorRotation().Equals(DesiredWorldRotation, KINDA_SMALL_NUMBER);
	const bool bActorScaleChanged = !RoomToolActor.GetActorScale3D().Equals(DesiredWorldScale, KINDA_SMALL_NUMBER);
	const bool bExtentChanged = bActorScaleChanged || !CurrentUnscaledExtent.Equals(DesiredExtent, KINDA_SMALL_NUMBER);

	if (bActorScaleChanged)
	{
		RoomToolActor.SetActorScale3D(DesiredWorldScale);
	}

	if (bActorLocationChanged || bActorRotationChanged)
	{
		RoomToolActor.SetActorLocationAndRotation(
			DesiredWorldLocation,
			DesiredWorldRotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics);
	}

	if (bExtentChanged)
	{
		RoomBoundsComponent->SetBoxExtent(DesiredExtent, false);
	}

	return bActorLocationChanged || bActorRotationChanged || bActorScaleChanged || bExtentChanged;
}

bool ASomeToolLevelLayoutPreviewActor::SnapDoorToolActorToGrid(ASomeToolLevelLayoutDoorToolActor& DoorToolActor) const
{
	UBoxComponent* DoorBoundsComponent = DoorToolActor.GetDoorBoundsComponent();
	if (!DoorBoundsComponent)
	{
		return false;
	}

	const float SafeCellSize = FMath::Max(CellSize, 1.0f);
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector CurrentLocalCenter = GetActorTransform().InverseTransformPosition(DoorBoundsComponent->GetComponentLocation());
	const FVector CurrentWorldExtent = DoorBoundsComponent->GetScaledBoxExtent();
	const FVector CurrentUnscaledExtent = DoorBoundsComponent->GetUnscaledBoxExtent();
	const FVector CurrentBoundsCenterWorld = DoorBoundsComponent->GetComponentLocation();
	const FVector CurrentActorToBoundsOffsetWorld = CurrentBoundsCenterWorld - DoorToolActor.GetActorLocation();
	const float CurrentBaseHeight = CurrentLocalCenter.Z - CurrentWorldExtent.Z;
	const float CurrentHeight = FMath::Max(CurrentWorldExtent.Z * 2.0f, 1.0f);
	const float DesiredExtentZ = CurrentHeight * 0.5f;
	const float LocalYaw = FRotator::NormalizeAxis((GetActorQuat().Inverse() * DoorToolActor.GetActorQuat()).Rotator().Yaw);
	const float SnappedLocalYaw = FRotator::NormalizeAxis(SnapAngleToRightAngle(LocalYaw));
	const ESomeToolLayoutWallOrientation Orientation = GetWallOrientationFromLocalYaw(SnappedLocalYaw);
	const int32 WidthLimit = Orientation == ESomeToolLayoutWallOrientation::Vertical ? GridHeight : GridWidth;
	const int32 WidthInCells = GetClampedCellCount(CurrentWorldExtent.X * 2.0f, SafeCellSize, WidthLimit);

	FVector SnappedBoundsCenterLocal = CurrentLocalCenter;
	if (Orientation == ESomeToolLayoutWallOrientation::Vertical)
	{
		const int32 LineX = FMath::Clamp(
			FMath::RoundToInt((CurrentLocalCenter.X - GridMinLocal.X) / SafeCellSize),
			0,
			GridWidth);
		const int32 OriginY = GetClampedOriginCell(CurrentLocalCenter.Y, GridMinLocal.Y, SafeCellSize, WidthInCells, GridHeight);
		SnappedBoundsCenterLocal.X = GridMinLocal.X + LineX * SafeCellSize;
		SnappedBoundsCenterLocal.Y = GridMinLocal.Y + (OriginY + WidthInCells * 0.5f) * SafeCellSize;
	}
	else
	{
		const int32 LineY = FMath::Clamp(
			FMath::RoundToInt((CurrentLocalCenter.Y - GridMinLocal.Y) / SafeCellSize),
			0,
			GridHeight);
		const int32 OriginX = GetClampedOriginCell(CurrentLocalCenter.X, GridMinLocal.X, SafeCellSize, WidthInCells, GridWidth);
		SnappedBoundsCenterLocal.X = GridMinLocal.X + (OriginX + WidthInCells * 0.5f) * SafeCellSize;
		SnappedBoundsCenterLocal.Y = GridMinLocal.Y + LineY * SafeCellSize;
	}
	SnappedBoundsCenterLocal.Z = CurrentBaseHeight + DesiredExtentZ;

	const FVector DesiredBoundsCenterWorld = GetActorTransform().TransformPosition(SnappedBoundsCenterLocal);
	const FVector DesiredWorldLocation = DesiredBoundsCenterWorld - CurrentActorToBoundsOffsetWorld;
	const FQuat DesiredWorldQuat = GetActorQuat() * FRotator(0.0f, SnappedLocalYaw, 0.0f).Quaternion();
	const FRotator DesiredWorldRotation = DesiredWorldQuat.Rotator();
	const FVector DesiredWorldScale = FVector::OneVector;
	const FVector DesiredExtent(
		WidthInCells * SafeCellSize * 0.5f,
		FMath::Max(WallThickness * 0.5f, 1.0f),
		FMath::Max(DesiredExtentZ, 1.0f));

	const bool bActorLocationChanged = !DoorToolActor.GetActorLocation().Equals(DesiredWorldLocation, KINDA_SMALL_NUMBER);
	const bool bActorRotationChanged = !DoorToolActor.GetActorRotation().Equals(DesiredWorldRotation, KINDA_SMALL_NUMBER);
	const bool bActorScaleChanged = !DoorToolActor.GetActorScale3D().Equals(DesiredWorldScale, KINDA_SMALL_NUMBER);
	const bool bExtentChanged = bActorScaleChanged || !CurrentUnscaledExtent.Equals(DesiredExtent, KINDA_SMALL_NUMBER);

	if (bActorScaleChanged)
	{
		DoorToolActor.SetActorScale3D(DesiredWorldScale);
	}

	if (bActorLocationChanged || bActorRotationChanged)
	{
		DoorToolActor.SetActorLocationAndRotation(
			DesiredWorldLocation,
			DesiredWorldRotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics);
	}

	if (bExtentChanged)
	{
		DoorBoundsComponent->SetBoxExtent(DesiredExtent, false);
	}

	return bActorLocationChanged || bActorRotationChanged || bActorScaleChanged || bExtentChanged;
}

#if WITH_EDITOR
void ASomeToolLevelLayoutPreviewActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (bAutoRebuild)
	{
		RebuildLayout();
	}
	else
	{
		RefreshPreviewComponents();
	}
}
#endif

void ASomeToolLevelLayoutPreviewActor::CollectRoomToolActors()
{
	CollectedRoomToolActors.Reset();

	if (!bUseRoomToolActors || !GetWorld())
	{
		return;
	}

	for (TActorIterator<ASomeToolLevelLayoutRoomToolActor> It(GetWorld()); It; ++It)
	{
		ASomeToolLevelLayoutRoomToolActor* RoomToolActor = *It;
		if (!IsValid(RoomToolActor) || RoomToolActor->GetLayoutOwnerActor() != this)
		{
			continue;
		}

		CollectedRoomToolActors.Add(RoomToolActor);
	}

	CollectedRoomToolActors.Sort([](
		const TObjectPtr<ASomeToolLevelLayoutRoomToolActor>& Left,
		const TObjectPtr<ASomeToolLevelLayoutRoomToolActor>& Right)
	{
		const ASomeToolLevelLayoutRoomToolActor* LeftPtr = Left.Get();
		const ASomeToolLevelLayoutRoomToolActor* RightPtr = Right.Get();
		if (!LeftPtr || !RightPtr)
		{
			return LeftPtr != nullptr;
		}

		return LeftPtr->GetName() < RightPtr->GetName();
	});
}

void ASomeToolLevelLayoutPreviewActor::CollectDoorToolActors()
{
	CollectedDoorToolActors.Reset();

	if (!bUseDoorToolActors || !GetWorld())
	{
		return;
	}

	for (TActorIterator<ASomeToolLevelLayoutDoorToolActor> It(GetWorld()); It; ++It)
	{
		ASomeToolLevelLayoutDoorToolActor* DoorToolActor = *It;
		if (!IsValid(DoorToolActor) || DoorToolActor->GetLayoutOwnerActor() != this)
		{
			continue;
		}

		CollectedDoorToolActors.Add(DoorToolActor);
	}

	CollectedDoorToolActors.Sort([](
		const TObjectPtr<ASomeToolLevelLayoutDoorToolActor>& Left,
		const TObjectPtr<ASomeToolLevelLayoutDoorToolActor>& Right)
	{
		const ASomeToolLevelLayoutDoorToolActor* LeftPtr = Left.Get();
		const ASomeToolLevelLayoutDoorToolActor* RightPtr = Right.Get();
		if (!LeftPtr || !RightPtr)
		{
			return LeftPtr != nullptr;
		}

		return LeftPtr->GetName() < RightPtr->GetName();
	});
}

void ASomeToolLevelLayoutPreviewActor::ResetRoomToolActorPreviewIds() const
{
	if (!GetWorld())
	{
		return;
	}

	for (TActorIterator<ASomeToolLevelLayoutRoomToolActor> It(GetWorld()); It; ++It)
	{
		ASomeToolLevelLayoutRoomToolActor* RoomToolActor = *It;
		if (!IsValid(RoomToolActor) || RoomToolActor->GetLayoutOwnerActor() != this)
		{
			continue;
		}

		RoomToolActor->SetResolvedPreviewRoomId(INDEX_NONE);
	}
}

void ASomeToolLevelLayoutPreviewActor::ResolveRoomRects()
{
	ResolvedRoomRects.Reset();
	ResetRoomToolActorPreviewIds();
	CollectRoomToolActors();

	if (CollectedRoomToolActors.Num() > 0)
	{
		int32 AutoAssignedRoomId = 1;
		ResolvedRoomRects.Reserve(CollectedRoomToolActors.Num());

		for (ASomeToolLevelLayoutRoomToolActor* RoomToolActor : CollectedRoomToolActors)
		{
			if (!IsValid(RoomToolActor))
			{
				continue;
			}

			const int32 AssignedRoomId = RoomToolActor->bUseExplicitRoomId
				? RoomToolActor->ExplicitRoomId
				: AutoAssignedRoomId++;

			FSomeToolRoomRect RoomRect;
			if (BuildRoomRectFromToolActor(*RoomToolActor, AssignedRoomId, RoomRect))
			{
				RoomToolActor->SetResolvedPreviewRoomId(AssignedRoomId);
				ResolvedRoomRects.Add(RoomRect);
			}
		}

		return;
	}

	ResolvedRoomRects = RoomRects;
}

void ASomeToolLevelLayoutPreviewActor::ResolveWallOpenings()
{
	ResolvedWallOpenings.Reset();
	CollectDoorToolActors();

	if (CollectedDoorToolActors.Num() <= 0)
	{
		return;
	}

	ResolvedWallOpenings.Reserve(CollectedDoorToolActors.Num());
	for (ASomeToolLevelLayoutDoorToolActor* DoorToolActor : CollectedDoorToolActors)
	{
		if (!IsValid(DoorToolActor))
		{
			continue;
		}

		FSomeToolWallOpening WallOpening;
		if (BuildWallOpeningFromToolActor(*DoorToolActor, WallOpening))
		{
			ResolvedWallOpenings.Add(WallOpening);
		}
	}
}

void ASomeToolLevelLayoutPreviewActor::RebuildInstanceInfos()
{
	GeneratedFloorInstanceInfos.Reset();
	GeneratedBaseWallInstanceInfos.Reset();
	GeneratedWallInstanceInfos.Reset();
	GeneratedOpeningInstanceInfos.Reset();
	GeneratedCornerInstanceInfos.Reset();
	RoomPreviewColors.Reset();
	WallPreviewColors.Reset();
	CornerPreviewColors.Reset();

	GeneratedFloorInstanceInfos.Reserve(CachedLayout.FloorRegions.Num());
	GeneratedOpeningInstanceInfos.Reserve(ResolvedWallOpenings.Num());

	TArray<FSomeToolLayoutWallSegment> VisibleWallSegments;
	BuildVisibleWallSegments(CachedLayout.WallSegments, FloorThickness, VisibleWallSegments);

	// Whole-segment removals are applied first; size-based openings are carved from the remaining wall pieces.
	TArray<FSomeToolLayoutWallSegment> BaseWallSegments;
	ApplyWallOpeningsToSegments(VisibleWallSegments, ResolvedWallOpenings, true, BaseWallSegments);
	GeneratedBaseWallInstanceInfos.Reserve(BaseWallSegments.Num());

	TArray<FSomeToolLayoutWallSegment> FinalWallSegments;
	ApplyWallOpeningsToSegments(BaseWallSegments, ResolvedWallOpenings, false, FinalWallSegments);
	GeneratedWallInstanceInfos.Reserve(FinalWallSegments.Num());

	for (const FSomeToolLayoutFloorRegion& FloorRegion : CachedLayout.FloorRegions)
	{
		RoomPreviewColors.FindOrAdd(FloorRegion.RoomId, FloorRegion.PreviewColor);
		GeneratedFloorInstanceInfos.Add(BuildFloorInstanceInfo(FloorRegion));
	}

	for (const FSomeToolWallOpening& WallOpening : ResolvedWallOpenings)
	{
		GeneratedOpeningInstanceInfos.Add(BuildOpeningInstanceInfo(WallOpening));
	}

	for (const FSomeToolLayoutWallSegment& WallSegment : BaseWallSegments)
	{
		GeneratedBaseWallInstanceInfos.Add(BuildWallInstanceInfo(WallSegment));
	}

	for (const FSomeToolLayoutWallSegment& WallSegment : FinalWallSegments)
	{
		GeneratedWallInstanceInfos.Add(BuildWallInstanceInfo(WallSegment));
		WallPreviewColors.Add(WallSegment.PreviewColor);
	}

	BuildCornerInstanceInfos(FinalWallSegments);
}

void ASomeToolLevelLayoutPreviewActor::RefreshPreviewComponents()
{
	const bool bShouldRenderPreviewComponents = ShouldRenderPreviewComponentsInCurrentWorld();

	GridPreviewComponent->SetStaticMesh(GridMesh);
	GridPreviewComponent->SetRelativeTransform(GridMesh ? BuildGridTransform() : FTransform::Identity);
	GridPreviewComponent->SetHiddenInGame(!bShouldRenderPreviewComponents);
	GridPreviewComponent->SetVisibility(bShouldRenderPreviewComponents && GridMesh != nullptr);

	FloorPreviewComponent->SetStaticMesh(FloorMesh);
	FloorPreviewComponent->SetHiddenInGame(!bShouldRenderPreviewComponents);
	FloorPreviewComponent->ClearInstances();

	WallPreviewComponent->SetStaticMesh(WallMesh);
	WallPreviewComponent->SetHiddenInGame(!bShouldRenderPreviewComponents);
	WallPreviewComponent->ClearInstances();

	CornerPreviewComponent->SetStaticMesh(CornerMesh);
	CornerPreviewComponent->SetHiddenInGame(!bShouldRenderPreviewComponents);
	CornerPreviewComponent->ClearInstances();

	if (!bShouldRenderPreviewComponents)
	{
		return;
	}

	if (FloorMesh)
	{
		const bool bUseMergedFloorPreview = bUseMergedFloorPreviewWhenDense
			&& GeneratedFloorInstanceInfos.Num() >= DenseFloorPreviewCellThreshold;

		if (bUseMergedFloorPreview)
		{
			for (const FSomeToolLayoutFloorRegion& FloorRegion : CachedLayout.FloorRegions)
			{
				const int32 InstanceIndex = FloorPreviewComponent->AddInstance(BuildFloorRegionPreviewTransform(FloorRegion));
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 0, FloorRegion.PreviewColor.R, false);
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 1, FloorRegion.PreviewColor.G, false);
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 2, FloorRegion.PreviewColor.B, false);
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 3, FloorRegion.PreviewColor.A, true);
			}
		}
		else
		{
			for (const FSomeToolFloorInstanceInfo& FloorInfo : GeneratedFloorInstanceInfos)
			{
				const FLinearColor PreviewColor = GetRoomPreviewColor(FloorInfo.RoomId);
				const int32 InstanceIndex = FloorPreviewComponent->AddInstance(
					BuildLocalTransformFromWorldFields(FloorInfo.Location, FloorInfo.Rotation, FloorInfo.Scale));
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 0, PreviewColor.R, false);
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 1, PreviewColor.G, false);
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 2, PreviewColor.B, false);
				FloorPreviewComponent->SetCustomDataValue(InstanceIndex, 3, PreviewColor.A, true);
			}
		}
	}

	if (WallMesh)
	{
		for (int32 WallIndex = 0; WallIndex < GeneratedWallInstanceInfos.Num(); ++WallIndex)
		{
			const FSomeToolWallInstanceInfo& WallInfo = GeneratedWallInstanceInfos[WallIndex];
			const FLinearColor PreviewColor = WallPreviewColors.IsValidIndex(WallIndex)
				? WallPreviewColors[WallIndex]
				: FLinearColor::White;
			const int32 InstanceIndex = WallPreviewComponent->AddInstance(
				BuildLocalTransformFromWorldFields(WallInfo.Location, WallInfo.Rotation, WallInfo.Scale));
			WallPreviewComponent->SetCustomDataValue(InstanceIndex, 0, PreviewColor.R, false);
			WallPreviewComponent->SetCustomDataValue(InstanceIndex, 1, PreviewColor.G, false);
			WallPreviewComponent->SetCustomDataValue(InstanceIndex, 2, PreviewColor.B, false);
			WallPreviewComponent->SetCustomDataValue(InstanceIndex, 3, PreviewColor.A, true);
		}
	}

	if (CornerMesh)
	{
		for (int32 CornerIndex = 0; CornerIndex < GeneratedCornerInstanceInfos.Num(); ++CornerIndex)
		{
			const FSomeToolCornerInstanceInfo& CornerInfo = GeneratedCornerInstanceInfos[CornerIndex];
			const FLinearColor PreviewColor = CornerPreviewColors.IsValidIndex(CornerIndex)
				? CornerPreviewColors[CornerIndex]
				: FLinearColor::White;
			const int32 InstanceIndex = CornerPreviewComponent->AddInstance(
				BuildLocalTransformFromWorldFields(CornerInfo.Location, CornerInfo.Rotation, CornerInfo.Scale));
			CornerPreviewComponent->SetCustomDataValue(InstanceIndex, 0, PreviewColor.R, false);
			CornerPreviewComponent->SetCustomDataValue(InstanceIndex, 1, PreviewColor.G, false);
			CornerPreviewComponent->SetCustomDataValue(InstanceIndex, 2, PreviewColor.B, false);
			CornerPreviewComponent->SetCustomDataValue(InstanceIndex, 3, PreviewColor.A, true);
		}
	}
}

bool ASomeToolLevelLayoutPreviewActor::ShouldRenderPreviewComponentsInCurrentWorld() const
{
	if (const UWorld* World = GetWorld(); World && World->IsGameWorld())
	{
		return bKeepPreviewVisibleInGame;
	}

	return true;
}

bool ASomeToolLevelLayoutPreviewActor::ShouldUseAsyncLayoutBuild() const
{
	if (const UWorld* World = GetWorld(); World && World->IsGameWorld())
	{
		return false;
	}

	return bUseAsyncLayoutBuild
		&& GridWidth * GridHeight >= FMath::Max(AsyncBuildCellThreshold, 1);
}

void ASomeToolLevelLayoutPreviewActor::QueueAsyncLayoutBuild()
{
	const bool bMatchesQueuedRequest = bHasQueuedAsyncBuildRequest
		&& QueuedBuildGridWidth == GridWidth
		&& QueuedBuildGridHeight == GridHeight
		&& AreRoomRectArraysEqual(QueuedBuildRoomRects, ResolvedRoomRects);
	if (bMatchesQueuedRequest)
	{
		return;
	}

	const bool bMatchesActiveRequest = bAsyncBuildInProgress
		&& ActiveBuildGridWidth == GridWidth
		&& ActiveBuildGridHeight == GridHeight
		&& AreRoomRectArraysEqual(ActiveBuildRoomRects, ResolvedRoomRects);
	if (bMatchesActiveRequest)
	{
		bHasQueuedAsyncBuildRequest = false;
		QueuedBuildGridWidth = 0;
		QueuedBuildGridHeight = 0;
		QueuedBuildRoomRects.Reset();
		LatestRequestedAsyncBuildGeneration = ActiveAsyncBuildGeneration;
		return;
	}

	QueuedBuildGridWidth = GridWidth;
	QueuedBuildGridHeight = GridHeight;
	QueuedBuildRoomRects = ResolvedRoomRects;
	bHasQueuedAsyncBuildRequest = true;
	++LatestRequestedAsyncBuildGeneration;

	if (!bAsyncBuildInProgress)
	{
		StartQueuedAsyncLayoutBuild();
	}
}

void ASomeToolLevelLayoutPreviewActor::StartQueuedAsyncLayoutBuild()
{
	if (!bHasQueuedAsyncBuildRequest || bAsyncBuildInProgress)
	{
		return;
	}

	const int32 BuildGeneration = LatestRequestedAsyncBuildGeneration;
	const int32 BuiltGridWidth = QueuedBuildGridWidth;
	const int32 BuiltGridHeight = QueuedBuildGridHeight;
	TArray<FSomeToolRoomRect> BuiltRoomRects = QueuedBuildRoomRects;

	bHasQueuedAsyncBuildRequest = false;
	bAsyncBuildInProgress = true;
	ActiveAsyncBuildGeneration = BuildGeneration;
	ActiveBuildGridWidth = BuiltGridWidth;
	ActiveBuildGridHeight = BuiltGridHeight;
	ActiveBuildRoomRects = BuiltRoomRects;

	TWeakObjectPtr<ASomeToolLevelLayoutPreviewActor> WeakThis(this);
	Async(EAsyncExecution::ThreadPool, [WeakThis, BuildGeneration, BuiltGridWidth, BuiltGridHeight, BuiltRoomRects = MoveTemp(BuiltRoomRects)]() mutable
	{
		FSomeToolLayoutBuildResult BuildResult = FSomeToolLevelLayoutSolver::BuildLayout(
			BuiltGridWidth,
			BuiltGridHeight,
			BuiltRoomRects);

		AsyncTask(ENamedThreads::GameThread, [WeakThis, BuildGeneration, BuiltGridWidth, BuiltGridHeight, BuiltRoomRects = MoveTemp(BuiltRoomRects), BuildResult = MoveTemp(BuildResult)]() mutable
		{
			if (ASomeToolLevelLayoutPreviewActor* StrongThis = WeakThis.Get())
			{
				StrongThis->HandleAsyncLayoutBuildCompleted(
					BuildGeneration,
					BuiltGridWidth,
					BuiltGridHeight,
					MoveTemp(BuiltRoomRects),
					MoveTemp(BuildResult));
			}
		});
	});
}

void ASomeToolLevelLayoutPreviewActor::HandleAsyncLayoutBuildCompleted(
	int32 BuildGeneration,
	int32 BuiltGridWidth,
	int32 BuiltGridHeight,
	TArray<FSomeToolRoomRect>&& BuiltRoomRects,
	FSomeToolLayoutBuildResult&& BuildResult)
{
	if (BuildGeneration != ActiveAsyncBuildGeneration)
	{
		return;
	}

	bAsyncBuildInProgress = false;
	ActiveAsyncBuildGeneration = 0;
	ActiveBuildGridWidth = 0;
	ActiveBuildGridHeight = 0;
	ActiveBuildRoomRects.Reset();

	if (BuildGeneration != LatestRequestedAsyncBuildGeneration)
	{
		if (bHasQueuedAsyncBuildRequest)
		{
			StartQueuedAsyncLayoutBuild();
		}
		return;
	}

	CachedLayout = MoveTemp(BuildResult);
	ResolvedRoomRects = BuiltRoomRects;
	RebuildInstanceInfos();
	RefreshPreviewComponents();
	UpdateBuildCacheState(BuiltRoomRects);

	if (bHasQueuedAsyncBuildRequest)
	{
		StartQueuedAsyncLayoutBuild();
	}
}

void ASomeToolLevelLayoutPreviewActor::UpdateBuildCacheState(const TArray<FSomeToolRoomRect>& AppliedRoomRects)
{
	bHasCachedBuildState = true;
	CachedBuildGridWidth = GridWidth;
	CachedBuildGridHeight = GridHeight;
	CachedBuildCellSize = CellSize;
	bCachedCenterGridOnActor = bCenterGridOnActor;
	CachedBuildGridThickness = GridThickness;
	CachedBuildGridOffsetZ = GridOffsetZ;
	CachedBuildFloorThickness = FloorThickness;
	CachedBuildWallThickness = WallThickness;
	bCachedUseMergedFloorPreviewWhenDense = bUseMergedFloorPreviewWhenDense;
	bCachedKeepPreviewVisibleInGame = bKeepPreviewVisibleInGame;
	CachedDenseFloorPreviewCellThreshold = DenseFloorPreviewCellThreshold;
	CachedGridMesh = GridMesh;
	CachedFloorMesh = FloorMesh;
	CachedWallMesh = WallMesh;
	CachedCornerMesh = CornerMesh;
	CachedBuildRoomRects = AppliedRoomRects;
	CachedBuildWallOpenings = ResolvedWallOpenings;
}

FVector ASomeToolLevelLayoutPreviewActor::GetGridMinLocal() const
{
	if (!bCenterGridOnActor)
	{
		return FVector::ZeroVector;
	}

	return FVector(
		GridWidth * CellSize * -0.5f,
		GridHeight * CellSize * -0.5f,
		0.0f);
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildGridTransform() const
{
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector LocalLocation(
		GridMinLocal.X + GridWidth * CellSize * 0.5f,
		GridMinLocal.Y + GridHeight * CellSize * 0.5f,
		GridOffsetZ + GridThickness * 0.5f);

	const FVector LocalScale(
		(GridWidth * CellSize) / GetSafeMeshDimension(GridMesh, EAxis::X),
		(GridHeight * CellSize) / GetSafeMeshDimension(GridMesh, EAxis::Y),
		GridThickness / GetSafeMeshDimension(GridMesh, EAxis::Z));

	return FTransform(FRotator::ZeroRotator, LocalLocation, LocalScale);
}

bool ASomeToolLevelLayoutPreviewActor::BuildRoomRectFromToolActor(
	const ASomeToolLevelLayoutRoomToolActor& RoomToolActor,
	int32 AssignedRoomId,
	FSomeToolRoomRect& OutRoomRect) const
{
	const UBoxComponent* RoomBoundsComponent = RoomToolActor.GetRoomBoundsComponent();
	if (!RoomBoundsComponent)
	{
		return false;
	}

	const float SafeCellSize = FMath::Max(CellSize, 1.0f);
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector LocalCenter = GetActorTransform().InverseTransformPosition(RoomBoundsComponent->GetComponentLocation());
	const FVector BoxExtent = RoomBoundsComponent->GetScaledBoxExtent();

	const int32 WidthInCells = GetClampedCellCount(BoxExtent.X * 2.0f, SafeCellSize, GridWidth);
	const int32 HeightInCells = GetClampedCellCount(BoxExtent.Y * 2.0f, SafeCellSize, GridHeight);
	const int32 OriginX = GetClampedOriginCell(LocalCenter.X, GridMinLocal.X, SafeCellSize, WidthInCells, GridWidth);
	const int32 OriginY = GetClampedOriginCell(LocalCenter.Y, GridMinLocal.Y, SafeCellSize, HeightInCells, GridHeight);

	OutRoomRect.RoomId = AssignedRoomId;
	OutRoomRect.Origin = FIntPoint(OriginX, OriginY);
	OutRoomRect.Width = WidthInCells;
	OutRoomRect.Height = HeightInCells;
	OutRoomRect.PreviewColor = RoomToolActor.PreviewColor;
	OutRoomRect.HeightOffset = LocalCenter.Z - BoxExtent.Z;
	OutRoomRect.VerticalSize = FMath::Max(BoxExtent.Z * 2.0f, FloorThickness + 1.0f);
	OutRoomRect.Priority = RoomToolActor.Priority;
	return true;
}

bool ASomeToolLevelLayoutPreviewActor::BuildWallOpeningFromToolActor(
	const ASomeToolLevelLayoutDoorToolActor& DoorToolActor,
	FSomeToolWallOpening& OutWallOpening) const
{
	const UBoxComponent* DoorBoundsComponent = DoorToolActor.GetDoorBoundsComponent();
	if (!DoorBoundsComponent)
	{
		return false;
	}

	const float SafeCellSize = FMath::Max(CellSize, 1.0f);
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector LocalCenter = GetActorTransform().InverseTransformPosition(DoorBoundsComponent->GetComponentLocation());
	const FVector BoxExtent = DoorBoundsComponent->GetScaledBoxExtent();
	const float LocalYaw = FRotator::NormalizeAxis((GetActorQuat().Inverse() * DoorToolActor.GetActorQuat()).Rotator().Yaw);
	const ESomeToolLayoutWallOrientation Orientation = GetWallOrientationFromLocalYaw(LocalYaw);
	const int32 WidthLimit = Orientation == ESomeToolLayoutWallOrientation::Vertical ? GridHeight : GridWidth;
	const int32 WidthInCells = GetClampedCellCount(BoxExtent.X * 2.0f, SafeCellSize, WidthLimit);

	OutWallOpening.Orientation = Orientation;
	OutWallOpening.Mode = DoorToolActor.OpeningMode;
	if (Orientation == ESomeToolLayoutWallOrientation::Vertical)
	{
		const int32 LineX = FMath::Clamp(
			FMath::RoundToInt((LocalCenter.X - GridMinLocal.X) / SafeCellSize),
			0,
			GridWidth);
		const int32 OriginY = GetClampedOriginCell(LocalCenter.Y, GridMinLocal.Y, SafeCellSize, WidthInCells, GridHeight);
		OutWallOpening.GridPoint = FIntPoint(LineX, OriginY);
	}
	else
	{
		const int32 LineY = FMath::Clamp(
			FMath::RoundToInt((LocalCenter.Y - GridMinLocal.Y) / SafeCellSize),
			0,
			GridHeight);
		const int32 OriginX = GetClampedOriginCell(LocalCenter.X, GridMinLocal.X, SafeCellSize, WidthInCells, GridWidth);
		OutWallOpening.GridPoint = FIntPoint(OriginX, LineY);
	}
	OutWallOpening.Length = WidthInCells;
	OutWallOpening.HeightOffset = LocalCenter.Z - BoxExtent.Z;
	OutWallOpening.VerticalSize = FMath::Max(BoxExtent.Z * 2.0f, 1.0f);
	return OutWallOpening.IsValid();
}

FSomeToolFloorInstanceInfo ASomeToolLevelLayoutPreviewActor::BuildFloorInstanceInfo(
	const FSomeToolLayoutFloorRegion& FloorRegion) const
{
	FSomeToolFloorInstanceInfo FloorInfo;
	FloorInfo.RoomId = FloorRegion.RoomId;
	FillTransformFields(
		BuildWorldTransform(BuildFloorRegionPreviewTransform(FloorRegion)),
		FloorInfo.Location,
		FloorInfo.Rotation,
		FloorInfo.Scale);
	return FloorInfo;
}

FSomeToolWallInstanceInfo ASomeToolLevelLayoutPreviewActor::BuildWallInstanceInfo(const FSomeToolLayoutWallSegment& WallSegment) const
{
	FSomeToolWallInstanceInfo WallInfo;
	FillTransformFields(
		BuildWorldTransform(BuildWallPreviewTransform(WallSegment)),
		WallInfo.Location,
		WallInfo.Rotation,
		WallInfo.Scale);
	return WallInfo;
}

FSomeToolOpeningInstanceInfo ASomeToolLevelLayoutPreviewActor::BuildOpeningInstanceInfo(
	const FSomeToolWallOpening& WallOpening) const
{
	const FVector GridMinLocal = GetGridMinLocal();
	const bool bIsVerticalWall = WallOpening.Orientation == ESomeToolLayoutWallOrientation::Vertical;
	const float OpeningLength = WallOpening.Length * CellSize;

	FVector LocalLocation(
		GridMinLocal.X + WallOpening.GridPoint.X * CellSize,
		GridMinLocal.Y + WallOpening.GridPoint.Y * CellSize,
		WallOpening.HeightOffset + WallOpening.VerticalSize * 0.5f);
	FRotator LocalRotation = FRotator::ZeroRotator;

	if (bIsVerticalWall)
	{
		LocalLocation.Y += OpeningLength * 0.5f;
		LocalRotation.Yaw = 90.0f;
	}
	else
	{
		LocalLocation.X += OpeningLength * 0.5f;
	}

	const FVector LocalScale(
		OpeningLength / GetSafeMeshDimension(WallMesh, EAxis::X),
		WallThickness / GetSafeMeshDimension(WallMesh, EAxis::Y),
		WallOpening.VerticalSize / GetSafeMeshDimension(WallMesh, EAxis::Z));

	FSomeToolOpeningInstanceInfo OpeningInfo;
	OpeningInfo.Mode = WallOpening.Mode;
	FillTransformFields(
		BuildWorldTransform(FTransform(LocalRotation, LocalLocation, LocalScale)),
		OpeningInfo.Location,
		OpeningInfo.Rotation,
		OpeningInfo.Scale);
	return OpeningInfo;
}

void ASomeToolLevelLayoutPreviewActor::BuildCornerInstanceInfos(const TArray<FSomeToolLayoutWallSegment>& WallSegments)
{
	TSet<FIntPoint> VerticalTouchPoints;
	TSet<FIntPoint> HorizontalTouchPoints;
	struct FCornerAggregate
	{
		float MinVisibleBaseHeight = TNumericLimits<float>::Max();
		float MaxVisibleTopHeight = -TNumericLimits<float>::Max();
		FLinearColor BestPreviewColor = FLinearColor::White;
		float BestTopHeight = -TNumericLimits<float>::Max();
		bool bHasValue = false;
	};

	TMap<FIntPoint, FCornerAggregate> CornerAggregates;
	auto AccumulateCornerPoint = [&CornerAggregates](const FIntPoint& GridPoint, const FSomeToolLayoutWallSegment& WallSegment)
	{
		FCornerAggregate& Aggregate = CornerAggregates.FindOrAdd(GridPoint);
		const float VisibleBase = WallSegment.HeightOffset;
		const float VisibleTop = WallSegment.HeightOffset + WallSegment.VerticalSize;

		Aggregate.MinVisibleBaseHeight = FMath::Min(Aggregate.MinVisibleBaseHeight, VisibleBase);
		Aggregate.MaxVisibleTopHeight = FMath::Max(Aggregate.MaxVisibleTopHeight, VisibleTop);
		if (!Aggregate.bHasValue || VisibleTop > Aggregate.BestTopHeight + KINDA_SMALL_NUMBER)
		{
			Aggregate.BestPreviewColor = WallSegment.PreviewColor;
			Aggregate.BestTopHeight = VisibleTop;
			Aggregate.bHasValue = true;
		}
	};

	for (const FSomeToolLayoutWallSegment& WallSegment : WallSegments)
	{
		for (int32 PointOffset = 0; PointOffset <= WallSegment.Length; ++PointOffset)
		{
			const FIntPoint GridPoint = WallSegment.Orientation == ESomeToolLayoutWallOrientation::Vertical
				? FIntPoint(WallSegment.GridPoint.X, WallSegment.GridPoint.Y + PointOffset)
				: FIntPoint(WallSegment.GridPoint.X + PointOffset, WallSegment.GridPoint.Y);

			if (WallSegment.Orientation == ESomeToolLayoutWallOrientation::Vertical)
			{
				VerticalTouchPoints.Add(GridPoint);
			}
			else
			{
				HorizontalTouchPoints.Add(GridPoint);
			}

			AccumulateCornerPoint(GridPoint, WallSegment);
		}
	}

	TArray<FIntPoint> CandidateCornerPoints;
	CandidateCornerPoints.Reserve(FMath::Min(VerticalTouchPoints.Num(), HorizontalTouchPoints.Num()));

	for (const FIntPoint& VerticalPoint : VerticalTouchPoints)
	{
		if (HorizontalTouchPoints.Contains(VerticalPoint))
		{
			CandidateCornerPoints.Add(VerticalPoint);
		}
	}

	Algo::Sort(CandidateCornerPoints, [] (const FIntPoint& Left, const FIntPoint& Right)
	{
		return Left.Y == Right.Y ? Left.X < Right.X : Left.Y < Right.Y;
	});

	GeneratedCornerInstanceInfos.Reserve(CandidateCornerPoints.Num());
	CornerPreviewColors.Reserve(CandidateCornerPoints.Num());

	for (const FIntPoint& GridPoint : CandidateCornerPoints)
	{
		const FCornerAggregate* Aggregate = CornerAggregates.Find(GridPoint);
		if (!Aggregate || !Aggregate->bHasValue)
		{
			continue;
		}

		FSomeToolCornerInstanceInfo CornerInfo;
		const float CornerBaseHeight = Aggregate->MinVisibleBaseHeight - FloorThickness;
		const float CornerVerticalSize = FMath::Max(
			Aggregate->MaxVisibleTopHeight - Aggregate->MinVisibleBaseHeight + FloorThickness,
			FloorThickness + 1.0f);

		FillTransformFields(
			BuildWorldTransform(BuildCornerPreviewTransform(GridPoint, CornerBaseHeight, CornerVerticalSize)),
			CornerInfo.Location,
			CornerInfo.Rotation,
			CornerInfo.Scale);
		GeneratedCornerInstanceInfos.Add(CornerInfo);
		CornerPreviewColors.Add(Aggregate->BestPreviewColor);
	}
}

FLinearColor ASomeToolLevelLayoutPreviewActor::GetRoomPreviewColor(int32 RoomId) const
{
	if (const FLinearColor* PreviewColor = RoomPreviewColors.Find(RoomId))
	{
		return *PreviewColor;
	}

	return FLinearColor::White;
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildFloorPreviewTransform(const FSomeToolGridCell& Cell) const
{
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector LocalLocation(
		GridMinLocal.X + (Cell.Coordinate.X + 0.5f) * CellSize,
		GridMinLocal.Y + (Cell.Coordinate.Y + 0.5f) * CellSize,
		Cell.HeightOffset + FloorThickness * 0.5f);
	const FVector LocalScale(
		CellSize / GetSafeMeshDimension(FloorMesh, EAxis::X),
		CellSize / GetSafeMeshDimension(FloorMesh, EAxis::Y),
		FloorThickness / GetSafeMeshDimension(FloorMesh, EAxis::Z));

	return FTransform(FRotator::ZeroRotator, LocalLocation, LocalScale);
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildFloorRegionPreviewTransform(const FSomeToolLayoutFloorRegion& FloorRegion) const
{
	const FVector GridMinLocal = GetGridMinLocal();
	const FVector LocalLocation(
		GridMinLocal.X + (FloorRegion.Origin.X + FloorRegion.Width * 0.5f) * CellSize,
		GridMinLocal.Y + (FloorRegion.Origin.Y + FloorRegion.Height * 0.5f) * CellSize,
		FloorRegion.HeightOffset + FloorThickness * 0.5f);
	const FVector LocalScale(
		(FloorRegion.Width * CellSize) / GetSafeMeshDimension(FloorMesh, EAxis::X),
		(FloorRegion.Height * CellSize) / GetSafeMeshDimension(FloorMesh, EAxis::Y),
		FloorThickness / GetSafeMeshDimension(FloorMesh, EAxis::Z));

	return FTransform(FRotator::ZeroRotator, LocalLocation, LocalScale);
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildWallPreviewTransform(const FSomeToolLayoutWallSegment& WallSegment) const
{
	const FVector GridMinLocal = GetGridMinLocal();
	const bool bIsVerticalWall = WallSegment.Orientation == ESomeToolLayoutWallOrientation::Vertical;
	const float WallLength = WallSegment.Length * CellSize;
	const float ActualWallHeight = FMath::Max(WallSegment.VerticalSize, 1.0f);

	FVector LocalLocation(
		GridMinLocal.X + WallSegment.GridPoint.X * CellSize,
		GridMinLocal.Y + WallSegment.GridPoint.Y * CellSize,
		WallSegment.HeightOffset + ActualWallHeight * 0.5f);
	FRotator LocalRotation = FRotator::ZeroRotator;

	if (bIsVerticalWall)
	{
		LocalLocation.Y += WallLength * 0.5f;
		LocalRotation.Yaw = 90.0f;
	}
	else
	{
		LocalLocation.X += WallLength * 0.5f;
	}

	const FVector LocalScale(
		WallLength / GetSafeMeshDimension(WallMesh, EAxis::X),
		WallThickness / GetSafeMeshDimension(WallMesh, EAxis::Y),
		ActualWallHeight / GetSafeMeshDimension(WallMesh, EAxis::Z));

	return FTransform(LocalRotation, LocalLocation, LocalScale);
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildCornerPreviewTransform(
	const FIntPoint& GridPoint,
	float BaseHeight,
	float VerticalSize) const
{
	const FVector GridMinLocal = GetGridMinLocal();
	const float ActualCornerHeight = FMath::Max(VerticalSize - FloorThickness, 1.0f);
	const FVector LocalLocation(
		GridMinLocal.X + GridPoint.X * CellSize,
		GridMinLocal.Y + GridPoint.Y * CellSize,
		BaseHeight + FloorThickness + ActualCornerHeight * 0.5f);
	const FVector LocalScale(
		WallThickness / GetSafeMeshDimension(CornerMesh, EAxis::X),
		WallThickness / GetSafeMeshDimension(CornerMesh, EAxis::Y),
		ActualCornerHeight / GetSafeMeshDimension(CornerMesh, EAxis::Z));

	return FTransform(FRotator::ZeroRotator, LocalLocation, LocalScale);
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildWorldTransform(const FTransform& LocalTransform) const
{
	return LocalTransform * GetActorTransform();
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildLocalTransformFromWorldFields(
	const FVector& Location,
	const FRotator& Rotation,
	const FVector& Scale) const
{
	return BuildPreviewTransform(Location, Rotation, Scale).GetRelativeTransform(GetActorTransform());
}

FTransform ASomeToolLevelLayoutPreviewActor::BuildPreviewTransform(
	const FVector& Location,
	const FRotator& Rotation,
	const FVector& Scale)
{
	return FTransform(Rotation, Location, Scale);
}

void ASomeToolLevelLayoutPreviewActor::FillTransformFields(
	const FTransform& Transform,
	FVector& OutLocation,
	FRotator& OutRotation,
	FVector& OutScale)
{
	OutLocation = Transform.GetLocation();
	OutRotation = Transform.Rotator();
	OutScale = Transform.GetScale3D();
}

float ASomeToolLevelLayoutPreviewActor::GetSafeMeshDimension(const UStaticMesh* Mesh, EAxis::Type Axis)
{
	if (!Mesh)
	{
		return 1.0f;
	}

	const FVector MeshSize = Mesh->GetBoundingBox().GetSize();

	switch (Axis)
	{
	case EAxis::X:
		return FMath::Max(MeshSize.X, 1.0f);
	case EAxis::Y:
		return FMath::Max(MeshSize.Y, 1.0f);
	default:
		return FMath::Max(MeshSize.Z, 1.0f);
	}
}
