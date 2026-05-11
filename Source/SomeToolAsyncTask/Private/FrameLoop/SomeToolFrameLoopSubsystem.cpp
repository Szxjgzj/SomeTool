#include "FrameLoop/SomeToolFrameLoopSubsystem.h"

#include "FrameLoop/SomeToolFrameLoopTask.h"

void USomeToolFrameLoopSubsystem::Deinitialize()
{
	for (USomeToolFrameLoopTask* Task : ActiveTasks)
	{
		if (IsValid(Task))
		{
			Task->HandleOwningSubsystemDeinitialized();
		}
	}

	for (USomeToolFrameLoopTask* Task : PendingRegisterTasks)
	{
		if (IsValid(Task))
		{
			Task->HandleOwningSubsystemDeinitialized();
		}
	}

	ActiveTasks.Reset();
	PendingRegisterTasks.Reset();
	bIsTicking = false;
	bNeedsCompaction = false;

	Super::Deinitialize();
}

void USomeToolFrameLoopSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTasks.IsEmpty())
	{
		FlushPendingTasks();
		return;
	}

	bIsTicking = true;

	for (int32 TaskIndex = 0; TaskIndex < ActiveTasks.Num(); ++TaskIndex)
	{
		USomeToolFrameLoopTask* Task = ActiveTasks[TaskIndex];
		if (!IsValid(Task))
		{
			bNeedsCompaction = true;
			continue;
		}

		if (!Task->IsActiveForTick())
		{
			bNeedsCompaction = true;
			continue;
		}

		Task->TickFrameLoop();

		if (!IsValid(Task) || !Task->IsActiveForTick())
		{
			bNeedsCompaction = true;
		}
	}

	bIsTicking = false;
	FlushPendingTasks();
}

bool USomeToolFrameLoopSubsystem::IsTickable() const
{
	return IsInitialized() && ActiveTasks.Num() > 0;
}

TStatId USomeToolFrameLoopSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(USomeToolFrameLoopSubsystem, STATGROUP_Tickables);
}

void USomeToolFrameLoopSubsystem::RegisterActiveTask(USomeToolFrameLoopTask* Task)
{
	if (!IsValid(Task))
	{
		return;
	}

	const bool bAlreadyRegistered = ActiveTasks.ContainsByPredicate(
		[Task](const TObjectPtr<USomeToolFrameLoopTask>& Candidate)
		{
			return Candidate.Get() == Task;
		});

	if (bAlreadyRegistered)
	{
		return;
	}

	if (bIsTicking)
	{
		const bool bAlreadyPending = PendingRegisterTasks.ContainsByPredicate(
			[Task](const TObjectPtr<USomeToolFrameLoopTask>& Candidate)
			{
				return Candidate.Get() == Task;
			});

		if (!bAlreadyPending)
		{
			PendingRegisterTasks.Add(Task);
		}

		return;
	}

	ActiveTasks.Add(Task);
}

void USomeToolFrameLoopSubsystem::UnregisterActiveTask(USomeToolFrameLoopTask* Task)
{
	if (!Task)
	{
		return;
	}

	PendingRegisterTasks.RemoveAll(
		[Task](const TObjectPtr<USomeToolFrameLoopTask>& Candidate)
		{
			return Candidate.Get() == Task;
		});

	if (bIsTicking)
	{
		bNeedsCompaction = true;
		return;
	}

	ActiveTasks.RemoveAll(
		[Task](const TObjectPtr<USomeToolFrameLoopTask>& Candidate)
		{
			return Candidate.Get() == Task;
		});
}

void USomeToolFrameLoopSubsystem::FlushPendingTasks()
{
	if (bNeedsCompaction)
	{
		ActiveTasks.RemoveAll(
			[](const TObjectPtr<USomeToolFrameLoopTask>& Task)
			{
				return !IsValid(Task) || !Task->IsActiveForTick();
			});

		bNeedsCompaction = false;
	}

	if (PendingRegisterTasks.IsEmpty())
	{
		return;
	}

	for (USomeToolFrameLoopTask* Task : PendingRegisterTasks)
	{
		if (!IsValid(Task) || !Task->IsActiveForTick())
		{
			continue;
		}

		const bool bAlreadyRegistered = ActiveTasks.ContainsByPredicate(
			[Task](const TObjectPtr<USomeToolFrameLoopTask>& Candidate)
			{
				return Candidate.Get() == Task;
			});

		if (!bAlreadyRegistered)
		{
			ActiveTasks.Add(Task);
		}
	}

	PendingRegisterTasks.Reset();
}
