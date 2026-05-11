#include "Timeline/SomeToolFloatCurveTimelineHandle.h"

#include "Curves/CurveFloat.h"
#include "SomeToolAsyncTask.h"
#include "Timeline/SomeToolTimelineSubsystem.h"

void USomeToolFloatCurveTimelineHandle::Play(
	float NewDuration,
	float NewStartTime,
	float NewPlayRate,
	bool bNewLooping,
	bool bNewFireUpdateOnPlay)
{
	DurationSeconds = FMath::Max(NewDuration, 0.0f);
	CurrentTimeSeconds = FMath::Max(NewStartTime, 0.0f);
	PlaybackRate = FMath::Max(FMath::Abs(NewPlayRate), KINDA_SMALL_NUMBER);
	bLooping = bNewLooping;
	bFireUpdateOnPlay = bNewFireUpdateOnPlay;

	BeginPlayback();
}

void USomeToolFloatCurveTimelineHandle::PlayFromStart(
	float NewDuration,
	float NewPlayRate,
	bool bNewLooping,
	bool bNewFireUpdateOnPlay)
{
	Play(NewDuration, 0.0f, NewPlayRate, bNewLooping, bNewFireUpdateOnPlay);
}

void USomeToolFloatCurveTimelineHandle::Pause()
{
	if (!bPlaying)
	{
		return;
	}

	bPlaying = false;
	bPaused = true;
	UnregisterFromSubsystem();
}

void USomeToolFloatCurveTimelineHandle::Resume()
{
	if (bPlaying)
	{
		return;
	}

	BeginPlayback();
}

void USomeToolFloatCurveTimelineHandle::Stop()
{
	if (!bPlaying && !bPaused)
	{
		return;
	}

	bPlaying = false;
	bPaused = false;
	UnregisterFromSubsystem();
}

void USomeToolFloatCurveTimelineHandle::Finish()
{
	CurrentTimeSeconds = FMath::Max(DurationSeconds, 0.0f);
	InternalFinish(true);
}

void USomeToolFloatCurveTimelineHandle::SetPlaybackPosition(float NewTime, bool bFireUpdate)
{
	CurrentTimeSeconds = FMath::Max(NewTime, 0.0f);
	NormalizePlaybackTime();

	if (bFireUpdate)
	{
		BroadcastUpdate();
	}
}

void USomeToolFloatCurveTimelineHandle::SetCurve(UCurveFloat* NewCurveAsset)
{
	CurveAsset = NewCurveAsset;
	RefreshCurveTimeRange();
}

void USomeToolFloatCurveTimelineHandle::SetDuration(float NewDuration)
{
	DurationSeconds = FMath::Max(NewDuration, 0.0f);
	NormalizePlaybackTime();

	if (!bPlaying)
	{
		return;
	}

	if (DurationSeconds <= KINDA_SMALL_NUMBER)
	{
		if (bLooping)
		{
			Stop();
			BroadcastUpdate();
			return;
		}

		InternalFinish(true);
		return;
	}

	if (!bLooping && CurrentTimeSeconds >= DurationSeconds)
	{
		InternalFinish(true);
	}
}

void USomeToolFloatCurveTimelineHandle::SetPlayRate(float NewPlayRate)
{
	PlaybackRate = FMath::Max(FMath::Abs(NewPlayRate), KINDA_SMALL_NUMBER);
}

void USomeToolFloatCurveTimelineHandle::SetLooping(bool bNewLooping)
{
	bLooping = bNewLooping;
	NormalizePlaybackTime();
}

float USomeToolFloatCurveTimelineHandle::GetCurrentValue() const
{
	const float Alpha = GetPlaybackAlpha();

	if (!CurveAsset)
	{
		return Alpha;
	}

	if (FMath::IsNearlyEqual(CurveMinTime, CurveMaxTime))
	{
		return CurveAsset->GetFloatValue(CurveMinTime);
	}

	return CurveAsset->GetFloatValue(FMath::Lerp(CurveMinTime, CurveMaxTime, Alpha));
}

float USomeToolFloatCurveTimelineHandle::GetCurrentTime() const
{
	return CurrentTimeSeconds;
}

float USomeToolFloatCurveTimelineHandle::GetPlaybackAlpha() const
{
	if (DurationSeconds <= KINDA_SMALL_NUMBER)
	{
		return 1.0f;
	}

	return FMath::Clamp(CurrentTimeSeconds / DurationSeconds, 0.0f, 1.0f);
}

bool USomeToolFloatCurveTimelineHandle::IsPlaying() const
{
	return bPlaying;
}

bool USomeToolFloatCurveTimelineHandle::IsPaused() const
{
	return bPaused;
}

bool USomeToolFloatCurveTimelineHandle::IsLooping() const
{
	return bLooping;
}

void USomeToolFloatCurveTimelineHandle::InitializeHandle(
	USomeToolTimelineSubsystem* InOwningSubsystem,
	UObject* InOwnerObject,
	UCurveFloat* InCurveAsset)
{
	OwningSubsystem = InOwningSubsystem;
	OwnerObject = InOwnerObject;
	bHasOwnerObject = InOwnerObject != nullptr;
	CurveAsset = InCurveAsset;
	DurationSeconds = 1.0f;
	CurrentTimeSeconds = 0.0f;
	PlaybackRate = 1.0f;
	bLooping = false;
	bFireUpdateOnPlay = true;
	bPlaying = false;
	bPaused = false;

	RefreshCurveTimeRange();
	NormalizePlaybackTime();
}

void USomeToolFloatCurveTimelineHandle::TickTimeline(float DeltaTime)
{
	if (!bPlaying)
	{
		return;
	}

	if (!OwningSubsystem.IsValid() || !OwningSubsystem->IsInitialized() || HasInvalidOwner())
	{
		Stop();
		return;
	}

	if (DurationSeconds <= KINDA_SMALL_NUMBER)
	{
		if (bLooping)
		{
			Stop();
			BroadcastUpdate();
			return;
		}

		InternalFinish(true);
		return;
	}

	CurrentTimeSeconds += FMath::Max(DeltaTime, 0.0f) * PlaybackRate;

	if (bLooping)
	{
		CurrentTimeSeconds = WrapTimeToDuration(CurrentTimeSeconds);
		BroadcastUpdate();
		return;
	}

	if (CurrentTimeSeconds >= DurationSeconds)
	{
		CurrentTimeSeconds = DurationSeconds;
		InternalFinish(true);
		return;
	}

	BroadcastUpdate();
}

bool USomeToolFloatCurveTimelineHandle::IsActiveForTick() const
{
	return bPlaying;
}

bool USomeToolFloatCurveTimelineHandle::HasInvalidOwner() const
{
	return bHasOwnerObject && !OwnerObject.IsValid();
}

void USomeToolFloatCurveTimelineHandle::HandleOwningSubsystemDeinitialized()
{
	bPlaying = false;
	bPaused = false;
	OwningSubsystem.Reset();
	OwnerObject.Reset();
	bHasOwnerObject = false;
}

void USomeToolFloatCurveTimelineHandle::BeginPlayback()
{
	if (!OwningSubsystem.IsValid() || !OwningSubsystem->IsInitialized() || HasInvalidOwner())
	{
		UE_LOG(LogSomeToolAsyncTask, Warning, TEXT("Play failed because the timeline subsystem is not valid or the owner object is invalid."));
		return;
	}

	NormalizePlaybackTime();
	bPaused = false;

	if (DurationSeconds <= KINDA_SMALL_NUMBER)
	{
		bPlaying = false;
		UnregisterFromSubsystem();

		if (bFireUpdateOnPlay)
		{
			BroadcastUpdate();
		}

		if (!bLooping)
		{
			OnFinish.Broadcast(GetCurrentValue());
		}

		return;
	}

	bPlaying = true;
	RegisterWithSubsystem();

	if (bFireUpdateOnPlay)
	{
		BroadcastUpdate();
	}

	if (!bLooping && CurrentTimeSeconds >= DurationSeconds)
	{
		InternalFinish(false);
	}
}

void USomeToolFloatCurveTimelineHandle::InternalFinish(bool bBroadcastUpdate)
{
	bPlaying = false;
	bPaused = false;
	UnregisterFromSubsystem();

	if (bBroadcastUpdate)
	{
		BroadcastUpdate();
	}

	OnFinish.Broadcast(GetCurrentValue());
}

void USomeToolFloatCurveTimelineHandle::BroadcastUpdate()
{
	OnUpdate.Broadcast(GetCurrentValue());
}

void USomeToolFloatCurveTimelineHandle::NormalizePlaybackTime()
{
	if (DurationSeconds <= KINDA_SMALL_NUMBER)
	{
		CurrentTimeSeconds = FMath::Max(CurrentTimeSeconds, 0.0f);
		return;
	}

	if (bLooping)
	{
		CurrentTimeSeconds = WrapTimeToDuration(CurrentTimeSeconds);
		return;
	}

	CurrentTimeSeconds = FMath::Clamp(CurrentTimeSeconds, 0.0f, DurationSeconds);
}

void USomeToolFloatCurveTimelineHandle::RefreshCurveTimeRange()
{
	CurveMinTime = 0.0f;
	CurveMaxTime = 1.0f;

	if (!CurveAsset)
	{
		return;
	}

	CurveAsset->GetTimeRange(CurveMinTime, CurveMaxTime);
}

float USomeToolFloatCurveTimelineHandle::WrapTimeToDuration(float InTime) const
{
	if (DurationSeconds <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	float WrappedTime = FMath::Fmod(InTime, DurationSeconds);
	if (WrappedTime < 0.0f)
	{
		WrappedTime += DurationSeconds;
	}

	return WrappedTime;
}

void USomeToolFloatCurveTimelineHandle::RegisterWithSubsystem()
{
	if (OwningSubsystem.IsValid())
	{
		OwningSubsystem->RegisterActiveHandle(this);
	}
}

void USomeToolFloatCurveTimelineHandle::UnregisterFromSubsystem()
{
	if (OwningSubsystem.IsValid())
	{
		OwningSubsystem->UnregisterActiveHandle(this);
	}
}
