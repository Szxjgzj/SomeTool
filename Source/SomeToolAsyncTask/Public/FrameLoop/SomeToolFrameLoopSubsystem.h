#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SomeToolFrameLoopSubsystem.generated.h"

class USomeToolFrameLoopTask;

UCLASS()
class SOMETOOLASYNCTASK_API USomeToolFrameLoopSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	void RegisterActiveTask(USomeToolFrameLoopTask* Task);
	void UnregisterActiveTask(USomeToolFrameLoopTask* Task);

private:
	void FlushPendingTasks();

	UPROPERTY(Transient)
	TArray<TObjectPtr<USomeToolFrameLoopTask>> ActiveTasks;

	UPROPERTY(Transient)
	TArray<TObjectPtr<USomeToolFrameLoopTask>> PendingRegisterTasks;

	bool bIsTicking = false;
	bool bNeedsCompaction = false;
};
