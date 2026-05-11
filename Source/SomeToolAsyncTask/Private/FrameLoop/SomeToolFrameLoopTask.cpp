#include "FrameLoop/SomeToolFrameLoopTask.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "FrameLoop/SomeToolFrameLoopSubsystem.h"
#include "SomeToolAsyncTask.h"

USomeToolFrameLoopTask* USomeToolFrameLoopTask::StartFrameLoopTask(
	UObject* WorldContextObject,
	const int32 TotalEventCount,
	const int32 FrameInterval,
	const int32 EventsPerExecution,
	UObject* OwnerObject,
	const int32 StartIndex)
{
	UWorld* World = GEngine
		? GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull)
		: nullptr;

	if (!World)
	{
		UE_LOG(LogSomeToolAsyncTask, Warning, TEXT("StartFrameLoopTask failed because WorldContextObject does not resolve to a valid world."));
		return nullptr;
	}

	USomeToolFrameLoopSubsystem* FrameLoopSubsystem = World->GetSubsystem<USomeToolFrameLoopSubsystem>();
	if (!FrameLoopSubsystem)
	{
		UE_LOG(LogSomeToolAsyncTask, Warning, TEXT("StartFrameLoopTask failed because the frame loop subsystem is unavailable."));
		return nullptr;
	}

	USomeToolFrameLoopTask* Task = NewObject<USomeToolFrameLoopTask>(FrameLoopSubsystem);
	Task->InitializeTask(
		FrameLoopSubsystem,
		TotalEventCount,
		FrameInterval,
		EventsPerExecution,
		OwnerObject,
		StartIndex);
	return Task;
}

void USomeToolFrameLoopTask::Pause()
{
	if (!bRunning || bFinished || bCancelled)
	{
		return;
	}

	bRunning = false;
	bPaused = true;
	UnregisterFromSubsystem();
}

void USomeToolFrameLoopTask::Resume()
{
	if (!bPaused || bFinished || bCancelled)
	{
		return;
	}

	bRunning = true;
	bPaused = false;
	RegisterWithSubsystem();
}

void USomeToolFrameLoopTask::Cancel()
{
	if (bFinished || bCancelled)
	{
		return;
	}

	bRunning = false;
	bPaused = false;
	bCancelled = true;
	UnregisterFromSubsystem();

	OnCancelled.Broadcast();
	SetReadyToDestroy();
}

bool USomeToolFrameLoopTask::IsRunning() const
{
	return bRunning;
}

bool USomeToolFrameLoopTask::IsPaused() const
{
	return bPaused;
}

bool USomeToolFrameLoopTask::IsFinished() const
{
	return bFinished;
}

int32 USomeToolFrameLoopTask::GetCurrentIndex() const
{
	return CurrentIndex;
}

int32 USomeToolFrameLoopTask::GetTotalEventCount() const
{
	return TotalEventCount;
}

float USomeToolFrameLoopTask::GetProgress() const
{
	if (TotalEventCount <= 0)
	{
		return 1.0f;
	}

	const int32 CompletedCount = FMath::Clamp(CurrentIndex - StartIndex, 0, TotalEventCount);
	return static_cast<float>(CompletedCount) / static_cast<float>(TotalEventCount);
}

void USomeToolFrameLoopTask::Activate()
{
	if (bFinished || bCancelled)
	{
		return;
	}

	if (!OwningSubsystem.IsValid() || !OwningSubsystem->IsInitialized())
	{
		UE_LOG(LogSomeToolAsyncTask, Warning, TEXT("StartFrameLoopTask activation failed because the frame loop subsystem is not valid."));
		Cancel();
		return;
	}

	RegisterWithGameInstance(OwningSubsystem->GetWorld());

	if (TotalEventCount <= 0)
	{
		FinishTask();
		return;
	}

	bRunning = true;
	bPaused = false;
	RegisterWithSubsystem();
}

void USomeToolFrameLoopTask::InitializeTask(
	USomeToolFrameLoopSubsystem* InOwningSubsystem,
	const int32 InTotalEventCount,
	const int32 InFrameInterval,
	const int32 InEventsPerExecution,
	UObject* InOwnerObject,
	const int32 InStartIndex)
{
	OwningSubsystem = InOwningSubsystem;
	OwnerObject = InOwnerObject;
	bHasOwnerObject = InOwnerObject != nullptr;
	TotalEventCount = FMath::Max(InTotalEventCount, 0);
	FrameInterval = FMath::Max(InFrameInterval, 0);
	EventsPerExecution = FMath::Max(InEventsPerExecution, 1);
	StartIndex = InStartIndex;
	CurrentIndex = StartIndex;
	FramesUntilNextExecution = 0;

	bRunning = false;
	bPaused = false;
	bFinished = false;
	bCancelled = false;
}

void USomeToolFrameLoopTask::TickFrameLoop()
{
	if (!bRunning || bPaused || bFinished || bCancelled)
	{
		return;
	}

	if (!OwningSubsystem.IsValid() || !OwningSubsystem->IsInitialized() || HasInvalidOwner())
	{
		Cancel();
		return;
	}

	if (FramesUntilNextExecution > 0)
	{
		--FramesUntilNextExecution;
		return;
	}

	const int32 EndIndex = StartIndex + TotalEventCount;
	int32 ExecutedThisFrame = 0;
	while (ExecutedThisFrame < EventsPerExecution && CurrentIndex < EndIndex)
	{
		OnStep.Broadcast(CurrentIndex);
		++CurrentIndex;
		++ExecutedThisFrame;

		if (!bRunning || bPaused || bFinished || bCancelled)
		{
			return;
		}
	}

	if (CurrentIndex >= EndIndex)
	{
		FinishTask();
		return;
	}

	FramesUntilNextExecution = FrameInterval;
}

bool USomeToolFrameLoopTask::IsActiveForTick() const
{
	return bRunning && !bPaused && !bFinished && !bCancelled;
}

bool USomeToolFrameLoopTask::HasInvalidOwner() const
{
	return bHasOwnerObject && !OwnerObject.IsValid();
}

void USomeToolFrameLoopTask::HandleOwningSubsystemDeinitialized()
{
	bRunning = false;
	bPaused = false;
	bCancelled = true;
	OwningSubsystem.Reset();
	OwnerObject.Reset();
	bHasOwnerObject = false;
	SetReadyToDestroy();
}

void USomeToolFrameLoopTask::FinishTask()
{
	if (bFinished || bCancelled)
	{
		return;
	}

	bRunning = false;
	bPaused = false;
	bFinished = true;
	UnregisterFromSubsystem();

	OnCompleted.Broadcast();
	SetReadyToDestroy();
}

void USomeToolFrameLoopTask::RegisterWithSubsystem()
{
	if (OwningSubsystem.IsValid())
	{
		OwningSubsystem->RegisterActiveTask(this);
	}
}

void USomeToolFrameLoopTask::UnregisterFromSubsystem()
{
	if (OwningSubsystem.IsValid())
	{
		OwningSubsystem->UnregisterActiveTask(this);
	}
}
