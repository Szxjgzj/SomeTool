#include "SomeToolRecordingBlueprintLibrary.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

URecordingPluginSubsystem* USomeToolRecordingBlueprintLibrary::GetSomeToolRecordingSubsystem(const UObject* WorldContextObject)
{
	if (!GEngine || !WorldContextObject)
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if (!World)
	{
		return nullptr;
	}

	UGameInstance* GameInstance = World->GetGameInstance();
	return GameInstance ? GameInstance->GetSubsystem<URecordingPluginSubsystem>() : nullptr;
}

bool USomeToolRecordingBlueprintLibrary::StartSomeToolRecording(
	const UObject* WorldContextObject,
	const FString& OutputPath,
	int32 FPS,
	int32 BitrateMbps)
{
	URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->StartRecording(OutputPath, FPS, BitrateMbps) : false;
}

void USomeToolRecordingBlueprintLibrary::StopSomeToolRecording(const UObject* WorldContextObject)
{
	if (URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject))
	{
		RecordingSubsystem->StopRecording();
	}
}

bool USomeToolRecordingBlueprintLibrary::IsSomeToolRecording(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->IsRecording() : false;
}

FIntPoint USomeToolRecordingBlueprintLibrary::GetSomeToolRecordingResolution(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->GetResolution() : FIntPoint::ZeroValue;
}

int32 USomeToolRecordingBlueprintLibrary::GetSomeToolRecordingFrameCount(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->GetFrameCount() : 0;
}

float USomeToolRecordingBlueprintLibrary::GetSomeToolRecordedSeconds(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->GetRecordedSeconds() : 0.0f;
}

FString USomeToolRecordingBlueprintLibrary::GetSomeToolRecordingOutputPath(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->GetOutputPath() : FString();
}

bool USomeToolRecordingBlueprintLibrary::OpenSomeToolRecordingPerformanceMonitorWindow(const UObject* WorldContextObject)
{
	URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->OpenPerformanceMonitorWindow() : false;
}

void USomeToolRecordingBlueprintLibrary::CloseSomeToolRecordingPerformanceMonitorWindow(const UObject* WorldContextObject)
{
	if (URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject))
	{
		RecordingSubsystem->ClosePerformanceMonitorWindow();
	}
}

void USomeToolRecordingBlueprintLibrary::ToggleSomeToolRecordingPerformanceMonitorWindow(const UObject* WorldContextObject)
{
	if (URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject))
	{
		RecordingSubsystem->TogglePerformanceMonitorWindow();
	}
}

bool USomeToolRecordingBlueprintLibrary::IsSomeToolRecordingPerformanceMonitorWindowOpen(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->IsPerformanceMonitorWindowOpen() : false;
}

FRecordingPerformanceStats USomeToolRecordingBlueprintLibrary::GetSomeToolRecordingPerformanceStats(const UObject* WorldContextObject)
{
	const URecordingPluginSubsystem* RecordingSubsystem = GetSomeToolRecordingSubsystem(WorldContextObject);
	return RecordingSubsystem ? RecordingSubsystem->GetRecordingPerformanceStats() : FRecordingPerformanceStats();
}
