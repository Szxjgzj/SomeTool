#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BaseAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FAsyncDelegate,float,Time,float,CurveValue,float,A,float,B);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncDelegateTwo,float,RestTime,UObject*,Object);
UCLASS()
class SOMETOOL_API UBaseAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
	UBaseAsyncAction(const FObjectInitializer& ObjectInitializer);
	~UBaseAsyncAction();
	
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category=UIAsyncTask)
	static UBaseAsyncAction* AsyncAction(
		UObject* worldContext,
		UCurveFloat* CurveFloat,
		float CurveValue,
		bool bIsUseCurve,
		float A,
		float B,
		float DeltaSeconds = 1.f,
		float Time = 5.f,
		float FirstDelay = 0.f
		);
	
	virtual void Activate() override;
	
	UPROPERTY(BlueprintAssignable,DisplayName=OnComplete)
	FAsyncDelegate OnCompleteDelegate;
	
	UPROPERTY(BlueprintAssignable,DisplayName=OnUpdate)
	FAsyncDelegate OnUpdateDelegate;
	
	//UPROPERTY(BlueprintAssignable)
	//FAsyncDelegateTwo OnUpdateDelegateTwo;

private:
	
	bool bIsUseCurve = false;
	float Time;
	float LastTime = 0.f;
	float DeltaSeconds;
	float FirstDelay;
	float CurveValue = 0.f;
	float AValue = 0.f;
	float BValue = 0.f;
	
	UObject* WorldContext;
	UWorld* World;
	UCurveFloat* CurveFloat;
	FTimerHandle TimerHandle;
	
public:
	UFUNCTION()
	void OnUpdate();
};
