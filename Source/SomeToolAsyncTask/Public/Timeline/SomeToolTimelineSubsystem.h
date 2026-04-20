#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SomeToolTimelineSubsystem.generated.h"

class USomeToolFloatCurveTimelineHandle;

UCLASS()
class SOMETOOLASYNCTASK_API USomeToolTimelineSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	void RegisterActiveHandle(USomeToolFloatCurveTimelineHandle* Handle);
	void UnregisterActiveHandle(USomeToolFloatCurveTimelineHandle* Handle);

private:
	void FlushPendingHandles();

	UPROPERTY(Transient)
	TArray<TObjectPtr<USomeToolFloatCurveTimelineHandle>> ActiveHandles;

	UPROPERTY(Transient)
	TArray<TObjectPtr<USomeToolFloatCurveTimelineHandle>> PendingRegisterHandles;

	bool bIsTicking = false;
	bool bNeedsCompaction = false;
};
