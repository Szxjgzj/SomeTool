#include "Layout/SomeToolLevelLayoutDoorToolActor.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Layout/SomeToolLevelLayoutPreviewActor.h"

ASomeToolLevelLayoutDoorToolActor::ASomeToolLevelLayoutDoorToolActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	DoorBoundsComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorBounds"));
	DoorBoundsComponent->SetupAttachment(SceneRoot);
	DoorBoundsComponent->SetBoxExtent(FVector(100.0f, 10.0f, 110.0f));
	DoorBoundsComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DoorBoundsComponent->SetGenerateOverlapEvents(false);
	DoorBoundsComponent->SetHiddenInGame(true);
	DoorBoundsComponent->ShapeColor = FColor(255, 160, 48);
}

void ASomeToolLevelLayoutDoorToolActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (DoorBoundsComponent)
	{
		const FVector CurrentRelativeLocation = DoorBoundsComponent->GetRelativeLocation();
		if (!CurrentRelativeLocation.IsNearlyZero(KINDA_SMALL_NUMBER))
		{
			const FVector PreservedBoundsWorldLocation = DoorBoundsComponent->GetComponentLocation();
			DoorBoundsComponent->SetRelativeLocation(FVector::ZeroVector);
			SetActorLocation(PreservedBoundsWorldLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}

		DoorBoundsComponent->ShapeColor = PreviewColor.ToFColor(true);
	}

	if (!bIsApplyingToolSync && bSnapToLayoutGrid && LayoutOwner)
	{
		bIsApplyingToolSync = true;
		const bool bChangedBySnap = LayoutOwner->SnapDoorToolActorToGrid(*this);
		bIsApplyingToolSync = false;
		const bool bShouldDeferRebuild = bIsInteractiveEditorTransform
			&& LayoutOwner
			&& LayoutOwner->bDeferRoomToolRebuildWhileDragging;
		if (bChangedBySnap)
		{
			if (bAutoRebuildLayoutOwner && !bShouldDeferRebuild)
			{
				NotifyLayoutOwnerChanged();
			}
			return;
		}
	}

	if (bIsApplyingToolSync)
	{
		return;
	}

	const bool bShouldDeferRebuild = bIsInteractiveEditorTransform
		&& LayoutOwner
		&& LayoutOwner->bDeferRoomToolRebuildWhileDragging;
	if (bAutoRebuildLayoutOwner && !bShouldDeferRebuild)
	{
		NotifyLayoutOwnerChanged();
	}
}

void ASomeToolLevelLayoutDoorToolActor::NotifyLayoutOwnerChanged()
{
	if (LayoutOwner)
	{
		LayoutOwner->RebuildLayout();
	}
}

#if WITH_EDITOR
void ASomeToolLevelLayoutDoorToolActor::EditorApplyTranslation(
	const FVector& DeltaTranslation,
	bool bAltDown,
	bool bShiftDown,
	bool bCtrlDown)
{
	bIsInteractiveEditorTransform = true;
	Super::EditorApplyTranslation(DeltaTranslation, bAltDown, bShiftDown, bCtrlDown);
}

void ASomeToolLevelLayoutDoorToolActor::EditorApplyRotation(
	const FRotator& DeltaRotation,
	bool bAltDown,
	bool bShiftDown,
	bool bCtrlDown)
{
	bIsInteractiveEditorTransform = true;
	Super::EditorApplyRotation(DeltaRotation, bAltDown, bShiftDown, bCtrlDown);
}

void ASomeToolLevelLayoutDoorToolActor::EditorApplyScale(
	const FVector& DeltaScale,
	const FVector* PivotLocation,
	bool bAltDown,
	bool bShiftDown,
	bool bCtrlDown)
{
	bIsInteractiveEditorTransform = true;
	Super::EditorApplyScale(DeltaScale, PivotLocation, bAltDown, bShiftDown, bCtrlDown);
}

void ASomeToolLevelLayoutDoorToolActor::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);

	if (!bFinished)
	{
		return;
	}

	const bool bWasInteractiveEditorTransform = bIsInteractiveEditorTransform;
	bIsInteractiveEditorTransform = false;

	if (!LayoutOwner)
	{
		return;
	}

	if (!bIsApplyingToolSync && bSnapToLayoutGrid)
	{
		bIsApplyingToolSync = true;
		LayoutOwner->SnapDoorToolActorToGrid(*this);
		bIsApplyingToolSync = false;
	}

	if (bAutoRebuildLayoutOwner && (bWasInteractiveEditorTransform || LayoutOwner->bDeferRoomToolRebuildWhileDragging))
	{
		NotifyLayoutOwnerChanged();
	}
}

void ASomeToolLevelLayoutDoorToolActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (bAutoRebuildLayoutOwner)
	{
		NotifyLayoutOwnerChanged();
	}
}
#endif
