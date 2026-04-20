#include "Timeline/SomeToolTimelineBlueprintLibrary.h"

#include "Curves/CurveFloat.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "SomeToolAsyncTask.h"
#include "Timeline/SomeToolFloatCurveTimelineHandle.h"
#include "Timeline/SomeToolTimelineSubsystem.h"

USomeToolFloatCurveTimelineHandle* USomeToolTimelineBlueprintLibrary::CreateFloatCurveTimelineHandle(
	UObject* WorldContextObject,
	UCurveFloat* CurveAsset)
{
	UWorld* World = GEngine
		? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull)
		: nullptr;

	if (!World)
	{
		UE_LOG(LogSomeToolAsyncTask, Warning, TEXT("CreateFloatCurveTimelineHandle failed because WorldContextObject does not resolve to a valid world."));
		return nullptr;
	}

	USomeToolTimelineSubsystem* TimelineSubsystem = World->GetSubsystem<USomeToolTimelineSubsystem>();
	if (!TimelineSubsystem)
	{
		UE_LOG(LogSomeToolAsyncTask, Warning, TEXT("CreateFloatCurveTimelineHandle failed because the timeline subsystem is unavailable."));
		return nullptr;
	}

	USomeToolFloatCurveTimelineHandle* Handle = NewObject<USomeToolFloatCurveTimelineHandle>(TimelineSubsystem);
	Handle->InitializeHandle(TimelineSubsystem, CurveAsset);

	return Handle;
}
