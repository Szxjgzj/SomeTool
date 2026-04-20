#include "Timeline/SomeToolTimelineSubsystem.h"

#include "Timeline/SomeToolFloatCurveTimelineHandle.h"

void USomeToolTimelineSubsystem::Deinitialize()
{
	for (USomeToolFloatCurveTimelineHandle* Handle : ActiveHandles)
	{
		if (IsValid(Handle))
		{
			Handle->HandleOwningSubsystemDeinitialized();
		}
	}

	for (USomeToolFloatCurveTimelineHandle* Handle : PendingRegisterHandles)
	{
		if (IsValid(Handle))
		{
			Handle->HandleOwningSubsystemDeinitialized();
		}
	}

	ActiveHandles.Reset();
	PendingRegisterHandles.Reset();
	bIsTicking = false;
	bNeedsCompaction = false;

	Super::Deinitialize();
}

void USomeToolTimelineSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveHandles.IsEmpty())
	{
		FlushPendingHandles();
		return;
	}

	bIsTicking = true;

	for (int32 HandleIndex = 0; HandleIndex < ActiveHandles.Num(); ++HandleIndex)
	{
		USomeToolFloatCurveTimelineHandle* Handle = ActiveHandles[HandleIndex];
		if (!IsValid(Handle))
		{
			bNeedsCompaction = true;
			continue;
		}

		if (!Handle->IsActiveForTick())
		{
			bNeedsCompaction = true;
			continue;
		}

		Handle->TickTimeline(DeltaTime);

		if (!IsValid(Handle) || !Handle->IsActiveForTick())
		{
			bNeedsCompaction = true;
		}
	}

	bIsTicking = false;
	FlushPendingHandles();
}

bool USomeToolTimelineSubsystem::IsTickable() const
{
	return IsInitialized() && ActiveHandles.Num() > 0;
}

TStatId USomeToolTimelineSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(USomeToolTimelineSubsystem, STATGROUP_Tickables);
}

void USomeToolTimelineSubsystem::RegisterActiveHandle(USomeToolFloatCurveTimelineHandle* Handle)
{
	if (!IsValid(Handle))
	{
		return;
	}

	const bool bAlreadyRegistered = ActiveHandles.ContainsByPredicate(
		[Handle](const TObjectPtr<USomeToolFloatCurveTimelineHandle>& Candidate)
		{
			return Candidate.Get() == Handle;
		});

	if (bAlreadyRegistered)
	{
		return;
	}

	if (bIsTicking)
	{
		const bool bAlreadyPending = PendingRegisterHandles.ContainsByPredicate(
			[Handle](const TObjectPtr<USomeToolFloatCurveTimelineHandle>& Candidate)
			{
				return Candidate.Get() == Handle;
			});

		if (!bAlreadyPending)
		{
			PendingRegisterHandles.Add(Handle);
		}

		return;
	}

	if (!bAlreadyRegistered)
	{
		ActiveHandles.Add(Handle);
	}
}

void USomeToolTimelineSubsystem::UnregisterActiveHandle(USomeToolFloatCurveTimelineHandle* Handle)
{
	if (!Handle)
	{
		return;
	}

	PendingRegisterHandles.RemoveAll(
		[Handle](const TObjectPtr<USomeToolFloatCurveTimelineHandle>& Candidate)
		{
			return Candidate.Get() == Handle;
		});

	if (bIsTicking)
	{
		bNeedsCompaction = true;
		return;
	}

	ActiveHandles.RemoveAll(
		[Handle](const TObjectPtr<USomeToolFloatCurveTimelineHandle>& Candidate)
		{
			return Candidate.Get() == Handle;
		});
}

void USomeToolTimelineSubsystem::FlushPendingHandles()
{
	if (bNeedsCompaction)
	{
		ActiveHandles.RemoveAll(
			[](const TObjectPtr<USomeToolFloatCurveTimelineHandle>& Handle)
			{
				return !IsValid(Handle) || !Handle->IsActiveForTick();
			});

		bNeedsCompaction = false;
	}

	if (PendingRegisterHandles.IsEmpty())
	{
		return;
	}

	for (USomeToolFloatCurveTimelineHandle* Handle : PendingRegisterHandles)
	{
		if (!IsValid(Handle) || !Handle->IsActiveForTick())
		{
			continue;
		}

		const bool bAlreadyRegistered = ActiveHandles.ContainsByPredicate(
			[Handle](const TObjectPtr<USomeToolFloatCurveTimelineHandle>& Candidate)
			{
				return Candidate.Get() == Handle;
			});

		if (!bAlreadyRegistered)
		{
			ActiveHandles.Add(Handle);
		}
	}

	PendingRegisterHandles.Reset();
}
