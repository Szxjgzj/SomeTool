#pragma once

#include "CoreMinimal.h"
#include "SomeToolLevelLayoutTypes.generated.h"

UENUM(BlueprintType)
enum class ESomeToolLayoutWallOrientation : uint8
{
	Horizontal,
	Vertical
};

UENUM(BlueprintType)
enum class ESomeToolOpeningMode : uint8
{
	Segment UMETA(DisplayName="整段删除"),
	Bounds UMETA(DisplayName="按尺寸删除")
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolRoomRect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(DisplayName="房间ID"))
	int32 RoomId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(DisplayName="起点格坐标"))
	FIntPoint Origin = FIntPoint::ZeroValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(ClampMin="1", DisplayName="宽度"))
	int32 Width = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(ClampMin="1", DisplayName="高度"))
	int32 Height = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(DisplayName="预览颜色"))
	FLinearColor PreviewColor = FLinearColor(0.15f, 0.55f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(DisplayName="底部高度"))
	float HeightOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(ClampMin="1.0", DisplayName="垂直尺寸"))
	float VerticalSize = 320.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room", meta=(DisplayName="优先级"))
	int32 Priority = 0;

	FIntPoint GetMaxExclusive() const
	{
		return FIntPoint(Origin.X + FMath::Max(Width, 0), Origin.Y + FMath::Max(Height, 0));
	}

	bool IsValid() const
	{
		return Width > 0 && Height > 0;
	}
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolGridCell
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell")
	FIntPoint Coordinate = FIntPoint::ZeroValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell")
	bool bIsOccupied = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell")
	int32 RoomId = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell")
	FLinearColor PreviewColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell")
	float HeightOffset = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cell")
	float VerticalSize = 320.0f;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolLayoutWallEdge
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	ESomeToolLayoutWallOrientation Orientation = ESomeToolLayoutWallOrientation::Horizontal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	FIntPoint GridPoint = FIntPoint::ZeroValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	int32 FirstRoomId = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	int32 SecondRoomId = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolLayoutFloorRegion
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	int32 RoomId = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	FIntPoint Origin = FIntPoint::ZeroValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	int32 Width = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	int32 Height = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	FLinearColor PreviewColor = FLinearColor::Transparent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	float HeightOffset = 0.0f;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolLayoutWallSegment
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	ESomeToolLayoutWallOrientation Orientation = ESomeToolLayoutWallOrientation::Horizontal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	FIntPoint GridPoint = FIntPoint::ZeroValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	int32 Length = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	int32 FirstRoomId = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	int32 SecondRoomId = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	FLinearColor PreviewColor = FLinearColor::White;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	float HeightOffset = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall")
	float VerticalSize = 320.0f;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolWallOpening
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(DisplayName="墙朝向"))
	ESomeToolLayoutWallOrientation Orientation = ESomeToolLayoutWallOrientation::Horizontal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(DisplayName="开口模式"))
	ESomeToolOpeningMode Mode = ESomeToolOpeningMode::Bounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(DisplayName="起点格坐标"))
	FIntPoint GridPoint = FIntPoint::ZeroValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(DisplayName="宽度格数"))
	int32 Length = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(DisplayName="底部高度"))
	float HeightOffset = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(DisplayName="垂直尺寸"))
	float VerticalSize = 220.0f;

	bool IsValid() const
	{
		return Length > 0 && VerticalSize > KINDA_SMALL_NUMBER;
	}
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolOpeningInstanceInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Opening", meta=(DisplayName="开口模式"))
	ESomeToolOpeningMode Mode = ESomeToolOpeningMode::Bounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Opening", meta=(DisplayName="位置"))
	FVector Location = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Opening", meta=(DisplayName="旋转"))
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Opening", meta=(DisplayName="缩放"))
	FVector Scale = FVector::OneVector;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolFloorInstanceInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Floor", meta=(DisplayName="房间ID"))
	int32 RoomId = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Floor", meta=(DisplayName="位置"))
	FVector Location = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Floor", meta=(DisplayName="旋转"))
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Floor", meta=(DisplayName="缩放"))
	FVector Scale = FVector::OneVector;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolWallInstanceInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall", meta=(DisplayName="位置"))
	FVector Location = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall", meta=(DisplayName="旋转"))
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wall", meta=(DisplayName="缩放"))
	FVector Scale = FVector::OneVector;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolCornerInstanceInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Corner", meta=(DisplayName="位置"))
	FVector Location = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Corner", meta=(DisplayName="旋转"))
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Corner", meta=(DisplayName="缩放"))
	FVector Scale = FVector::OneVector;
};

USTRUCT(BlueprintType)
struct SOMETOOLLEVELLAYOUT_API FSomeToolLayoutBuildResult
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	int32 GridWidth = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	int32 GridHeight = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	TArray<int32> RoomIds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	TArray<FSomeToolGridCell> Cells;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	TArray<FSomeToolLayoutWallEdge> WallEdges;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	TArray<FSomeToolLayoutFloorRegion> FloorRegions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Layout")
	TArray<FSomeToolLayoutWallSegment> WallSegments;

	void Reset(int32 InGridWidth, int32 InGridHeight)
	{
		GridWidth = InGridWidth;
		GridHeight = InGridHeight;
		RoomIds.Reset();
		Cells.Reset();
		WallEdges.Reset();
		FloorRegions.Reset();
		WallSegments.Reset();
	}
};
