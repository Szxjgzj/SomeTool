#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SomeToolFloatCurveTimelineHandle.generated.h"

class UCurveFloat;
class USomeToolTimelineBlueprintLibrary;
class USomeToolTimelineSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FSomeToolFloatCurveTimelineUpdateSignature,
	float,
	Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FSomeToolFloatCurveTimelineFinishSignature,
	float,
	Value);

UCLASS(BlueprintType)
class SOMETOOLASYNCTASK_API USomeToolFloatCurveTimelineHandle : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="SomeTool|Timeline")
	FSomeToolFloatCurveTimelineUpdateSignature OnUpdate;

	UPROPERTY(BlueprintAssignable, Category="SomeTool|Timeline")
	FSomeToolFloatCurveTimelineFinishSignature OnFinish;

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void Play(
		float NewDuration = 1.0f,
		float NewStartTime = 0.0f,
		float NewPlayRate = 1.0f,
		bool bNewLooping = false,
		bool bNewFireUpdateOnPlay = true);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void PlayFromStart(
		float NewDuration = 1.0f,
		float NewPlayRate = 1.0f,
		bool bNewLooping = false,
		bool bNewFireUpdateOnPlay = true);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void Pause();

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void Resume();

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void Stop();

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void Finish();

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void SetPlaybackPosition(float NewTime, bool bFireUpdate = true);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void SetCurve(UCurveFloat* NewCurveAsset);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void SetDuration(float NewDuration);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void SetPlayRate(float NewPlayRate);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Timeline")
	void SetLooping(bool bNewLooping);

	UFUNCTION(BlueprintPure, Category="SomeTool|Timeline")
	float GetCurrentValue() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|Timeline")
	float GetCurrentTime() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|Timeline")
	float GetPlaybackAlpha() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|Timeline")
	bool IsPlaying() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|Timeline")
	bool IsPaused() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|Timeline")
	bool IsLooping() const;

private:
	friend class USomeToolTimelineBlueprintLibrary;
	friend class USomeToolTimelineSubsystem;

	void InitializeHandle(
		USomeToolTimelineSubsystem* InOwningSubsystem,
		UObject* InOwnerObject,
		UCurveFloat* InCurveAsset);

	void TickTimeline(float DeltaTime);
	bool IsActiveForTick() const;
	bool HasInvalidOwner() const;
	void HandleOwningSubsystemDeinitialized();
	void BeginPlayback();
	void InternalFinish(bool bBroadcastUpdate);
	void BroadcastUpdate();
	void NormalizePlaybackTime();
	void RefreshCurveTimeRange();
	float WrapTimeToDuration(float InTime) const;
	void RegisterWithSubsystem();
	void UnregisterFromSubsystem();

	UPROPERTY(Transient)
	TObjectPtr<UCurveFloat> CurveAsset;

	TWeakObjectPtr<USomeToolTimelineSubsystem> OwningSubsystem;
	TWeakObjectPtr<UObject> OwnerObject;
	bool bHasOwnerObject = false;

	float DurationSeconds = 1.0f;
	float CurrentTimeSeconds = 0.0f;
	float PlaybackRate = 1.0f;
	float CurveMinTime = 0.0f;
	float CurveMaxTime = 1.0f;
	bool bLooping = false;
	bool bPlaying = false;
	bool bPaused = false;
	bool bFireUpdateOnPlay = true;
};
