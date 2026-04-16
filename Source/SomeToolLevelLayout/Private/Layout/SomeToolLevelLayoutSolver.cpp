#include "Layout/SomeToolLevelLayoutSolver.h"

#include "Algo/Sort.h"

namespace
{
struct FOrderedRoomRect
{
	const FSomeToolRoomRect* RoomRect = nullptr;
	int32 OriginalIndex = 0;
};

const FSomeToolGridCell* GetCellAt(const FSomeToolLayoutBuildResult& Layout, int32 X, int32 Y)
{
	if (X < 0 || Y < 0 || X >= Layout.GridWidth || Y >= Layout.GridHeight)
	{
		return nullptr;
	}

	return &Layout.Cells[Y * Layout.GridWidth + X];
}

bool IsMatchingFloorCell(const FSomeToolGridCell& Cell, int32 RoomId, float HeightOffset)
{
	return Cell.bIsOccupied
		&& Cell.RoomId == RoomId
		&& FMath::IsNearlyEqual(Cell.HeightOffset, HeightOffset);
}

float GetOccupiedBaseHeight(const FSomeToolGridCell* FirstCell, const FSomeToolGridCell* SecondCell)
{
	const bool bHasFirstCell = FirstCell && FirstCell->bIsOccupied;
	const bool bHasSecondCell = SecondCell && SecondCell->bIsOccupied;

	if (bHasFirstCell && bHasSecondCell)
	{
		return FMath::Min(FirstCell->HeightOffset, SecondCell->HeightOffset);
	}

	if (bHasFirstCell)
	{
		return FirstCell->HeightOffset;
	}

	if (bHasSecondCell)
	{
		return SecondCell->HeightOffset;
	}

	return 0.0f;
}

float GetOccupiedTopHeight(const FSomeToolGridCell* FirstCell, const FSomeToolGridCell* SecondCell)
{
	const bool bHasFirstCell = FirstCell && FirstCell->bIsOccupied;
	const bool bHasSecondCell = SecondCell && SecondCell->bIsOccupied;

	if (bHasFirstCell && bHasSecondCell)
	{
		return FMath::Max(
			FirstCell->HeightOffset + FirstCell->VerticalSize,
			SecondCell->HeightOffset + SecondCell->VerticalSize);
	}

	if (bHasFirstCell)
	{
		return FirstCell->HeightOffset + FirstCell->VerticalSize;
	}

	if (bHasSecondCell)
	{
		return SecondCell->HeightOffset + SecondCell->VerticalSize;
	}

	return 0.0f;
}

FLinearColor GetWallPreviewColor(
	const FSomeToolLayoutBuildResult& Layout,
	ESomeToolLayoutWallOrientation Orientation,
	int32 GridX,
	int32 GridY)
{
	if (Orientation == ESomeToolLayoutWallOrientation::Vertical)
	{
		if (const FSomeToolGridCell* LeftCell = GetCellAt(Layout, GridX - 1, GridY))
		{
			if (LeftCell->bIsOccupied)
			{
				return LeftCell->PreviewColor;
			}
		}

		if (const FSomeToolGridCell* RightCell = GetCellAt(Layout, GridX, GridY))
		{
			if (RightCell->bIsOccupied)
			{
				return RightCell->PreviewColor;
			}
		}
	}
	else
	{
		if (const FSomeToolGridCell* BottomCell = GetCellAt(Layout, GridX, GridY - 1))
		{
			if (BottomCell->bIsOccupied)
			{
				return BottomCell->PreviewColor;
			}
		}

		if (const FSomeToolGridCell* TopCell = GetCellAt(Layout, GridX, GridY))
		{
			if (TopCell->bIsOccupied)
			{
				return TopCell->PreviewColor;
			}
		}
	}

	return FLinearColor::White;
}

float GetWallBaseHeight(
	const FSomeToolLayoutBuildResult& Layout,
	ESomeToolLayoutWallOrientation Orientation,
	int32 GridX,
	int32 GridY)
{
	if (Orientation == ESomeToolLayoutWallOrientation::Vertical)
	{
		return GetOccupiedBaseHeight(
			GetCellAt(Layout, GridX - 1, GridY),
			GetCellAt(Layout, GridX, GridY));
	}

	return GetOccupiedBaseHeight(
		GetCellAt(Layout, GridX, GridY - 1),
		GetCellAt(Layout, GridX, GridY));
}

float GetWallVerticalSize(
	const FSomeToolLayoutBuildResult& Layout,
	ESomeToolLayoutWallOrientation Orientation,
	int32 GridX,
	int32 GridY)
{
	const FSomeToolGridCell* FirstCell = nullptr;
	const FSomeToolGridCell* SecondCell = nullptr;

	if (Orientation == ESomeToolLayoutWallOrientation::Vertical)
	{
		FirstCell = GetCellAt(Layout, GridX - 1, GridY);
		SecondCell = GetCellAt(Layout, GridX, GridY);
	}
	else
	{
		FirstCell = GetCellAt(Layout, GridX, GridY - 1);
		SecondCell = GetCellAt(Layout, GridX, GridY);
	}

	const float BaseHeight = GetOccupiedBaseHeight(FirstCell, SecondCell);
	const float TopHeight = GetOccupiedTopHeight(FirstCell, SecondCell);
	return FMath::Max(TopHeight - BaseHeight, 0.0f);
}
}

FSomeToolLayoutBuildResult FSomeToolLevelLayoutSolver::BuildLayout(
	int32 GridWidth,
	int32 GridHeight,
	const TArray<FSomeToolRoomRect>& RoomRects)
{
	FSomeToolLayoutBuildResult Result;
	BuildLayout(GridWidth, GridHeight, RoomRects, Result);
	return Result;
}

void FSomeToolLevelLayoutSolver::BuildLayout(
	int32 GridWidth,
	int32 GridHeight,
	const TArray<FSomeToolRoomRect>& RoomRects,
	FSomeToolLayoutBuildResult& OutResult)
{
	GridWidth = FMath::Max(GridWidth, 1);
	GridHeight = FMath::Max(GridHeight, 1);

	OutResult.Reset(GridWidth, GridHeight);
	InitializeCells(GridWidth, GridHeight, OutResult);
	RasterizeRooms(RoomRects, OutResult);
	BuildWalls(OutResult);
	BuildFloorRegions(OutResult);
	BuildWallSegments(OutResult);
}

void FSomeToolLevelLayoutSolver::InitializeCells(int32 GridWidth, int32 GridHeight, FSomeToolLayoutBuildResult& OutResult)
{
	OutResult.Cells.SetNum(GridWidth * GridHeight);

	for (int32 Y = 0; Y < GridHeight; ++Y)
	{
		for (int32 X = 0; X < GridWidth; ++X)
		{
			FSomeToolGridCell& Cell = OutResult.Cells[ToCellIndex(X, Y, GridWidth)];
			Cell.Coordinate = FIntPoint(X, Y);
			Cell.bIsOccupied = false;
			Cell.RoomId = INDEX_NONE;
			Cell.PreviewColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
			Cell.HeightOffset = 0.0f;
			Cell.VerticalSize = 320.0f;
		}
	}
}

void FSomeToolLevelLayoutSolver::RasterizeRooms(const TArray<FSomeToolRoomRect>& RoomRects, FSomeToolLayoutBuildResult& OutResult)
{
	TSet<int32> UniqueRoomIds;
	TArray<FOrderedRoomRect> OrderedRoomRects;
	OrderedRoomRects.Reserve(RoomRects.Num());

	for (int32 RoomIndex = 0; RoomIndex < RoomRects.Num(); ++RoomIndex)
	{
		FOrderedRoomRect& OrderedRoomRect = OrderedRoomRects.AddDefaulted_GetRef();
		OrderedRoomRect.RoomRect = &RoomRects[RoomIndex];
		OrderedRoomRect.OriginalIndex = RoomIndex;
	}

	OrderedRoomRects.Sort([](const FOrderedRoomRect& Left, const FOrderedRoomRect& Right)
	{
		const int32 LeftPriority = Left.RoomRect ? Left.RoomRect->Priority : 0;
		const int32 RightPriority = Right.RoomRect ? Right.RoomRect->Priority : 0;
		if (LeftPriority != RightPriority)
		{
			return LeftPriority < RightPriority;
		}

		return Left.OriginalIndex < Right.OriginalIndex;
	});

	for (const FOrderedRoomRect& OrderedRoomRect : OrderedRoomRects)
	{
		if (!OrderedRoomRect.RoomRect)
		{
			continue;
		}

		const FSomeToolRoomRect& RoomRect = *OrderedRoomRect.RoomRect;
		if (!RoomRect.IsValid())
		{
			continue;
		}

		const FIntPoint MaxExclusive = RoomRect.GetMaxExclusive();
		const int32 MinX = FMath::Clamp(RoomRect.Origin.X, 0, OutResult.GridWidth);
		const int32 MinY = FMath::Clamp(RoomRect.Origin.Y, 0, OutResult.GridHeight);
		const int32 MaxX = FMath::Clamp(MaxExclusive.X, 0, OutResult.GridWidth);
		const int32 MaxY = FMath::Clamp(MaxExclusive.Y, 0, OutResult.GridHeight);

		if (MinX >= MaxX || MinY >= MaxY)
		{
			continue;
		}

		UniqueRoomIds.Add(RoomRect.RoomId);

		for (int32 Y = MinY; Y < MaxY; ++Y)
		{
			for (int32 X = MinX; X < MaxX; ++X)
			{
				FSomeToolGridCell& Cell = OutResult.Cells[ToCellIndex(X, Y, OutResult.GridWidth)];
				Cell.bIsOccupied = true;
				Cell.RoomId = RoomRect.RoomId;
				Cell.PreviewColor = RoomRect.PreviewColor;
				Cell.HeightOffset = RoomRect.HeightOffset;
				Cell.VerticalSize = RoomRect.VerticalSize;
			}
		}
	}

	OutResult.RoomIds = UniqueRoomIds.Array();
	Algo::Sort(OutResult.RoomIds);
}

void FSomeToolLevelLayoutSolver::BuildWalls(FSomeToolLayoutBuildResult& OutResult)
{
	OutResult.WallEdges.Reset();

	for (int32 Y = 0; Y < OutResult.GridHeight; ++Y)
	{
		for (int32 X = 0; X <= OutResult.GridWidth; ++X)
		{
			const int32 LeftRoomId = GetRoomIdAt(OutResult, X - 1, Y);
			const int32 RightRoomId = GetRoomIdAt(OutResult, X, Y);

			if (!ShouldCreateWall(LeftRoomId, RightRoomId))
			{
				continue;
			}

			FSomeToolLayoutWallEdge& WallEdge = OutResult.WallEdges.AddDefaulted_GetRef();
			WallEdge.Orientation = ESomeToolLayoutWallOrientation::Vertical;
			WallEdge.GridPoint = FIntPoint(X, Y);
			WallEdge.FirstRoomId = LeftRoomId;
			WallEdge.SecondRoomId = RightRoomId;
		}
	}

	for (int32 Y = 0; Y <= OutResult.GridHeight; ++Y)
	{
		for (int32 X = 0; X < OutResult.GridWidth; ++X)
		{
			const int32 BottomRoomId = GetRoomIdAt(OutResult, X, Y - 1);
			const int32 TopRoomId = GetRoomIdAt(OutResult, X, Y);

			if (!ShouldCreateWall(BottomRoomId, TopRoomId))
			{
				continue;
			}

			FSomeToolLayoutWallEdge& WallEdge = OutResult.WallEdges.AddDefaulted_GetRef();
			WallEdge.Orientation = ESomeToolLayoutWallOrientation::Horizontal;
			WallEdge.GridPoint = FIntPoint(X, Y);
			WallEdge.FirstRoomId = BottomRoomId;
			WallEdge.SecondRoomId = TopRoomId;
		}
	}
}

void FSomeToolLevelLayoutSolver::BuildFloorRegions(FSomeToolLayoutBuildResult& OutResult)
{
	OutResult.FloorRegions.Reset();

	TArray<bool> Visited;
	Visited.Init(false, OutResult.Cells.Num());

	for (int32 Y = 0; Y < OutResult.GridHeight; ++Y)
	{
		for (int32 X = 0; X < OutResult.GridWidth; ++X)
		{
			const int32 StartIndex = ToCellIndex(X, Y, OutResult.GridWidth);
			const FSomeToolGridCell& StartCell = OutResult.Cells[StartIndex];

			if (Visited[StartIndex] || !StartCell.bIsOccupied)
			{
				continue;
			}

			int32 RegionWidth = 0;
			while (X + RegionWidth < OutResult.GridWidth)
			{
				const int32 TestIndex = ToCellIndex(X + RegionWidth, Y, OutResult.GridWidth);
				const FSomeToolGridCell& TestCell = OutResult.Cells[TestIndex];
				if (Visited[TestIndex] || !IsMatchingFloorCell(TestCell, StartCell.RoomId, StartCell.HeightOffset))
				{
					break;
				}

				++RegionWidth;
			}

			int32 RegionHeight = 1;
			bool bCanGrowHeight = true;
			while (Y + RegionHeight < OutResult.GridHeight && bCanGrowHeight)
			{
				for (int32 ScanX = 0; ScanX < RegionWidth; ++ScanX)
				{
					const int32 TestIndex = ToCellIndex(X + ScanX, Y + RegionHeight, OutResult.GridWidth);
					const FSomeToolGridCell& TestCell = OutResult.Cells[TestIndex];
					if (Visited[TestIndex] || !IsMatchingFloorCell(TestCell, StartCell.RoomId, StartCell.HeightOffset))
					{
						bCanGrowHeight = false;
						break;
					}
				}

				if (bCanGrowHeight)
				{
					++RegionHeight;
				}
			}

			for (int32 FillY = 0; FillY < RegionHeight; ++FillY)
			{
				for (int32 FillX = 0; FillX < RegionWidth; ++FillX)
				{
					Visited[ToCellIndex(X + FillX, Y + FillY, OutResult.GridWidth)] = true;
				}
			}

			FSomeToolLayoutFloorRegion& FloorRegion = OutResult.FloorRegions.AddDefaulted_GetRef();
			FloorRegion.RoomId = StartCell.RoomId;
			FloorRegion.Origin = FIntPoint(X, Y);
			FloorRegion.Width = RegionWidth;
			FloorRegion.Height = RegionHeight;
			FloorRegion.PreviewColor = StartCell.PreviewColor;
			FloorRegion.HeightOffset = StartCell.HeightOffset;
		}
	}
}

void FSomeToolLevelLayoutSolver::BuildWallSegments(FSomeToolLayoutBuildResult& OutResult)
{
	OutResult.WallSegments.Reset();

	for (int32 X = 0; X <= OutResult.GridWidth; ++X)
	{
		int32 Y = 0;
		while (Y < OutResult.GridHeight)
		{
			const int32 FirstRoomId = GetRoomIdAt(OutResult, X - 1, Y);
			const int32 SecondRoomId = GetRoomIdAt(OutResult, X, Y);
			if (!ShouldCreateWall(FirstRoomId, SecondRoomId))
			{
				++Y;
				continue;
			}

			const FLinearColor PreviewColor = GetWallPreviewColor(
				OutResult,
				ESomeToolLayoutWallOrientation::Vertical,
				X,
				Y);
			const float HeightOffset = GetWallBaseHeight(
				OutResult,
				ESomeToolLayoutWallOrientation::Vertical,
				X,
				Y);
			const float VerticalSize = GetWallVerticalSize(
				OutResult,
				ESomeToolLayoutWallOrientation::Vertical,
				X,
				Y);

			int32 SegmentLength = 1;
			while (Y + SegmentLength < OutResult.GridHeight)
			{
				const int32 NextFirstRoomId = GetRoomIdAt(OutResult, X - 1, Y + SegmentLength);
				const int32 NextSecondRoomId = GetRoomIdAt(OutResult, X, Y + SegmentLength);
				const float NextHeightOffset = GetWallBaseHeight(
					OutResult,
					ESomeToolLayoutWallOrientation::Vertical,
					X,
					Y + SegmentLength);
				const float NextVerticalSize = GetWallVerticalSize(
					OutResult,
					ESomeToolLayoutWallOrientation::Vertical,
					X,
					Y + SegmentLength);
				if (NextFirstRoomId != FirstRoomId
					|| NextSecondRoomId != SecondRoomId
					|| !FMath::IsNearlyEqual(NextHeightOffset, HeightOffset)
					|| !FMath::IsNearlyEqual(NextVerticalSize, VerticalSize))
				{
					break;
				}

				++SegmentLength;
			}

			FSomeToolLayoutWallSegment& WallSegment = OutResult.WallSegments.AddDefaulted_GetRef();
			WallSegment.Orientation = ESomeToolLayoutWallOrientation::Vertical;
			WallSegment.GridPoint = FIntPoint(X, Y);
			WallSegment.Length = SegmentLength;
			WallSegment.FirstRoomId = FirstRoomId;
			WallSegment.SecondRoomId = SecondRoomId;
			WallSegment.PreviewColor = PreviewColor;
			WallSegment.HeightOffset = HeightOffset;
			WallSegment.VerticalSize = VerticalSize;

			Y += SegmentLength;
		}
	}

	for (int32 Y = 0; Y <= OutResult.GridHeight; ++Y)
	{
		int32 X = 0;
		while (X < OutResult.GridWidth)
		{
			const int32 FirstRoomId = GetRoomIdAt(OutResult, X, Y - 1);
			const int32 SecondRoomId = GetRoomIdAt(OutResult, X, Y);
			if (!ShouldCreateWall(FirstRoomId, SecondRoomId))
			{
				++X;
				continue;
			}

			const FLinearColor PreviewColor = GetWallPreviewColor(
				OutResult,
				ESomeToolLayoutWallOrientation::Horizontal,
				X,
				Y);
			const float HeightOffset = GetWallBaseHeight(
				OutResult,
				ESomeToolLayoutWallOrientation::Horizontal,
				X,
				Y);
			const float VerticalSize = GetWallVerticalSize(
				OutResult,
				ESomeToolLayoutWallOrientation::Horizontal,
				X,
				Y);

			int32 SegmentLength = 1;
			while (X + SegmentLength < OutResult.GridWidth)
			{
				const int32 NextFirstRoomId = GetRoomIdAt(OutResult, X + SegmentLength, Y - 1);
				const int32 NextSecondRoomId = GetRoomIdAt(OutResult, X + SegmentLength, Y);
				const float NextHeightOffset = GetWallBaseHeight(
					OutResult,
					ESomeToolLayoutWallOrientation::Horizontal,
					X + SegmentLength,
					Y);
				const float NextVerticalSize = GetWallVerticalSize(
					OutResult,
					ESomeToolLayoutWallOrientation::Horizontal,
					X + SegmentLength,
					Y);
				if (NextFirstRoomId != FirstRoomId
					|| NextSecondRoomId != SecondRoomId
					|| !FMath::IsNearlyEqual(NextHeightOffset, HeightOffset)
					|| !FMath::IsNearlyEqual(NextVerticalSize, VerticalSize))
				{
					break;
				}

				++SegmentLength;
			}

			FSomeToolLayoutWallSegment& WallSegment = OutResult.WallSegments.AddDefaulted_GetRef();
			WallSegment.Orientation = ESomeToolLayoutWallOrientation::Horizontal;
			WallSegment.GridPoint = FIntPoint(X, Y);
			WallSegment.Length = SegmentLength;
			WallSegment.FirstRoomId = FirstRoomId;
			WallSegment.SecondRoomId = SecondRoomId;
			WallSegment.PreviewColor = PreviewColor;
			WallSegment.HeightOffset = HeightOffset;
			WallSegment.VerticalSize = VerticalSize;

			X += SegmentLength;
		}
	}
}

bool FSomeToolLevelLayoutSolver::ShouldCreateWall(int32 FirstRoomId, int32 SecondRoomId)
{
	if (FirstRoomId == SecondRoomId)
	{
		return false;
	}

	return FirstRoomId != INDEX_NONE || SecondRoomId != INDEX_NONE;
}

int32 FSomeToolLevelLayoutSolver::GetRoomIdAt(const FSomeToolLayoutBuildResult& Layout, int32 X, int32 Y)
{
	if (X < 0 || Y < 0 || X >= Layout.GridWidth || Y >= Layout.GridHeight)
	{
		return INDEX_NONE;
	}

	const FSomeToolGridCell& Cell = Layout.Cells[ToCellIndex(X, Y, Layout.GridWidth)];
	return Cell.bIsOccupied ? Cell.RoomId : INDEX_NONE;
}

int32 FSomeToolLevelLayoutSolver::ToCellIndex(int32 X, int32 Y, int32 GridWidth)
{
	return Y * GridWidth + X;
}
