#pragma once

#include "CoreMinimal.h"
#include "Layout/SomeToolLevelLayoutTypes.h"

class SOMETOOLLEVELLAYOUT_API FSomeToolLevelLayoutSolver
{
public:
	static FSomeToolLayoutBuildResult BuildLayout(
		int32 GridWidth,
		int32 GridHeight,
		const TArray<FSomeToolRoomRect>& RoomRects);

	static void BuildLayout(
		int32 GridWidth,
		int32 GridHeight,
		const TArray<FSomeToolRoomRect>& RoomRects,
		FSomeToolLayoutBuildResult& OutResult);

private:
	static void InitializeCells(int32 GridWidth, int32 GridHeight, FSomeToolLayoutBuildResult& OutResult);
	static void RasterizeRooms(const TArray<FSomeToolRoomRect>& RoomRects, FSomeToolLayoutBuildResult& OutResult);
	static void BuildWalls(FSomeToolLayoutBuildResult& OutResult);
	static void BuildFloorRegions(FSomeToolLayoutBuildResult& OutResult);
	static void BuildWallSegments(FSomeToolLayoutBuildResult& OutResult);
	static bool ShouldCreateWall(int32 FirstRoomId, int32 SecondRoomId);
	static int32 GetRoomIdAt(const FSomeToolLayoutBuildResult& Layout, int32 X, int32 Y);
	static int32 ToCellIndex(int32 X, int32 Y, int32 GridWidth);
};
