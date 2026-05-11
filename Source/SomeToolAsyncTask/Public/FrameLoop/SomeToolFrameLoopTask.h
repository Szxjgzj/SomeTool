#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SomeToolFrameLoopTask.generated.h"

class USomeToolFrameLoopSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FSomeToolFrameLoopStepSignature,
	int32,
	Index);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSomeToolFrameLoopCompletedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSomeToolFrameLoopCancelledSignature);

UCLASS(BlueprintType, meta=(ExposedAsyncProxy="Task"))
class SOMETOOLASYNCTASK_API USomeToolFrameLoopTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="SomeTool|AsyncTask|Frame Loop")
	FSomeToolFrameLoopStepSignature OnStep;

	UPROPERTY(BlueprintAssignable, Category="SomeTool|AsyncTask|Frame Loop")
	FSomeToolFrameLoopCompletedSignature OnCompleted;

	UPROPERTY(BlueprintAssignable, Category="SomeTool|AsyncTask|Frame Loop")
	FSomeToolFrameLoopCancelledSignature OnCancelled;

	UFUNCTION(
		BlueprintCallable,
		Category="SomeTool|AsyncTask|Frame Loop",
		meta=(
			WorldContext="WorldContextObject",
			DefaultToSelf="WorldContextObject",
			BlueprintInternalUseOnly="true",
			AdvancedDisplay="OwnerObject,StartIndex",
			DisplayName="Start Frame Loop Task",
			Keywords="SomeTool async task frame loop batch per frame"))
	static USomeToolFrameLoopTask* StartFrameLoopTask(
		UObject* WorldContextObject,
		UPARAM(DisplayName="Total Event Count")
		int32 TotalEventCount = 10,
		UPARAM(DisplayName="Frame Interval")
		int32 FrameInterval = 0,
		UPARAM(DisplayName="Events Per Execution")
		int32 EventsPerExecution = 1,
		UPARAM(DisplayName="Owner Object")
		UObject* OwnerObject = nullptr,
		UPARAM(DisplayName="Start Index")
		int32 StartIndex = 0);

	UFUNCTION(BlueprintCallable, Category="SomeTool|AsyncTask|Frame Loop")
	void Pause();

	UFUNCTION(BlueprintCallable, Category="SomeTool|AsyncTask|Frame Loop")
	void Resume();

	UFUNCTION(BlueprintCallable, Category="SomeTool|AsyncTask|Frame Loop")
	void Cancel();

	UFUNCTION(BlueprintPure, Category="SomeTool|AsyncTask|Frame Loop")
	bool IsRunning() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|AsyncTask|Frame Loop")
	bool IsPaused() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|AsyncTask|Frame Loop")
	bool IsFinished() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|AsyncTask|Frame Loop")
	int32 GetCurrentIndex() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|AsyncTask|Frame Loop")
	int32 GetTotalEventCount() const;

	UFUNCTION(BlueprintPure, Category="SomeTool|AsyncTask|Frame Loop")
	float GetProgress() const;

	virtual void Activate() override;

private:
	friend class USomeToolFrameLoopSubsystem;

	void InitializeTask(
		USomeToolFrameLoopSubsystem* InOwningSubsystem,
		int32 InTotalEventCount,
		int32 InFrameInterval,
		int32 InEventsPerExecution,
		UObject* InOwnerObject,
		int32 InStartIndex);

	void TickFrameLoop();
	bool IsActiveForTick() const;
	bool HasInvalidOwner() const;
	void HandleOwningSubsystemDeinitialized();
	void FinishTask();
	void RegisterWithSubsystem();
	void UnregisterFromSubsystem();

	TWeakObjectPtr<USomeToolFrameLoopSubsystem> OwningSubsystem;
	TWeakObjectPtr<UObject> OwnerObject;
	bool bHasOwnerObject = false;

	int32 TotalEventCount = 10;
	int32 FrameInterval = 0;
	int32 EventsPerExecution = 1;
	int32 StartIndex = 0;
	int32 CurrentIndex = 0;
	int32 FramesUntilNextExecution = 0;

	bool bRunning = false;
	bool bPaused = false;
	bool bFinished = false;
	bool bCancelled = false;
};
