#include "Layout/SomeToolLevelLayoutRoomToolActor.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h"
#include "Layout/SomeToolLevelLayoutPreviewActor.h"
#include "Math/RotationMatrix.h"

ASomeToolLevelLayoutRoomToolActor::ASomeToolLevelLayoutRoomToolActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	RoomBoundsComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomBounds"));
	RoomBoundsComponent->SetupAttachment(SceneRoot);
	RoomBoundsComponent->SetBoxExtent(FVector(100.0f, 100.0f, 160.0f));
	RoomBoundsComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RoomBoundsComponent->SetGenerateOverlapEvents(false);
	RoomBoundsComponent->SetHiddenInGame(true);
	RoomBoundsComponent->ShapeColor = FColor(64, 160, 255);

	RoomIdPreviewComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RoomIdPreview"));
	RoomIdPreviewComponent->SetupAttachment(SceneRoot);
	RoomIdPreviewComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RoomIdPreviewComponent->SetGenerateOverlapEvents(false);
	RoomIdPreviewComponent->SetCastShadow(false);
	RoomIdPreviewComponent->SetHiddenInGame(true);
	RoomIdPreviewComponent->SetCanEverAffectNavigation(false);
	RoomIdPreviewComponent->SetHorizontalAlignment(EHTA_Center);
	RoomIdPreviewComponent->SetVerticalAlignment(EVRTA_TextCenter);
	RoomIdPreviewComponent->SetText(FText::FromString(TEXT("自动")));
	RoomIdPreviewComponent->SetTextRenderColor(FColor::White);
	RoomIdPreviewComponent->SetAbsolute(false, true, false);
}

void ASomeToolLevelLayoutRoomToolActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (RoomBoundsComponent)
	{
		const FVector CurrentRelativeLocation = RoomBoundsComponent->GetRelativeLocation();
		if (!CurrentRelativeLocation.IsNearlyZero(KINDA_SMALL_NUMBER))
		{
			const FVector PreservedBoundsWorldLocation = RoomBoundsComponent->GetComponentLocation();
			RoomBoundsComponent->SetRelativeLocation(FVector::ZeroVector);
			SetActorLocation(PreservedBoundsWorldLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}

		RoomBoundsComponent->ShapeColor = PreviewColor.ToFColor(true);
	}

	if (!LayoutOwner)
	{
		ResolvedPreviewRoomId = INDEX_NONE;
	}

	UpdateRoomIdPreview();

	if (!bIsApplyingToolSync && bSnapToLayoutGrid && LayoutOwner)
	{
		bIsApplyingToolSync = true;
		const bool bChangedBySnap = LayoutOwner->SnapRoomToolActorToGrid(*this);
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

void ASomeToolLevelLayoutRoomToolActor::SetResolvedPreviewRoomId(int32 InRoomId)
{
	if (ResolvedPreviewRoomId == InRoomId)
	{
		return;
	}

	ResolvedPreviewRoomId = InRoomId;
	UpdateRoomIdPreview();
}

void ASomeToolLevelLayoutRoomToolActor::NotifyLayoutOwnerChanged()
{
	if (LayoutOwner)
	{
		LayoutOwner->RebuildLayout();
	}
}

void ASomeToolLevelLayoutRoomToolActor::UpdateRoomIdPreview()
{
	if (!RoomIdPreviewComponent || !RoomBoundsComponent)
	{
		return;
	}

	const FVector BoundsExtent = RoomBoundsComponent->GetUnscaledBoxExtent();
	const float LabelWorldSize = FMath::Clamp(FMath::Min(BoundsExtent.X, BoundsExtent.Y) * 0.35f, 24.0f, 96.0f);
	const int32 DisplayRoomId = ResolvedPreviewRoomId != INDEX_NONE
		? ResolvedPreviewRoomId
		: (bUseExplicitRoomId ? ExplicitRoomId : INDEX_NONE);
	const FText LabelText = DisplayRoomId != INDEX_NONE
		? FText::AsNumber(DisplayRoomId)
		: FText::FromString(TEXT("自动"));

	RoomIdPreviewComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BoundsExtent.Z + 4.0f));
	RoomIdPreviewComponent->SetWorldRotation(FRotationMatrix::MakeFromXZ(FVector::UpVector, FVector::YAxisVector).Rotator());
	RoomIdPreviewComponent->SetWorldSize(LabelWorldSize);
	RoomIdPreviewComponent->SetTextRenderColor(PreviewColor.ToFColor(true));
	RoomIdPreviewComponent->SetText(LabelText);
}

#if WITH_EDITOR
void ASomeToolLevelLayoutRoomToolActor::EditorApplyTranslation(
	const FVector& DeltaTranslation,
	bool bAltDown,
	bool bShiftDown,
	bool bCtrlDown)
{
	bIsInteractiveEditorTransform = true;
	Super::EditorApplyTranslation(DeltaTranslation, bAltDown, bShiftDown, bCtrlDown);
}

void ASomeToolLevelLayoutRoomToolActor::EditorApplyRotation(
	const FRotator& DeltaRotation,
	bool bAltDown,
	bool bShiftDown,
	bool bCtrlDown)
{
	bIsInteractiveEditorTransform = true;
	Super::EditorApplyRotation(DeltaRotation, bAltDown, bShiftDown, bCtrlDown);
}

void ASomeToolLevelLayoutRoomToolActor::EditorApplyScale(
	const FVector& DeltaScale,
	const FVector* PivotLocation,
	bool bAltDown,
	bool bShiftDown,
	bool bCtrlDown)
{
	bIsInteractiveEditorTransform = true;
	Super::EditorApplyScale(DeltaScale, PivotLocation, bAltDown, bShiftDown, bCtrlDown);
}

void ASomeToolLevelLayoutRoomToolActor::PostEditMove(bool bFinished)
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
		LayoutOwner->SnapRoomToolActorToGrid(*this);
		bIsApplyingToolSync = false;
	}

	if (bAutoRebuildLayoutOwner && (bWasInteractiveEditorTransform || LayoutOwner->bDeferRoomToolRebuildWhileDragging))
	{
		NotifyLayoutOwnerChanged();
	}
}
#endif
