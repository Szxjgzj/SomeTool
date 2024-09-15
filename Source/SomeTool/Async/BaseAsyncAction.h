#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BaseAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncDelegate,float,Time);
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
		float DeltaSeconds = 1.f,
		float Time = 5.f,
		float FirstDelay = 0.f
		);
	
	virtual void Activate() override;


	UPROPERTY(BlueprintAssignable,DisplayName=OnStart)
	FAsyncDelegate OnStartDelegate;

	UPROPERTY(BlueprintAssignable,DisplayName=OnUpdate)
	FAsyncDelegate OnUpdateDelegate;
	
	UPROPERTY(BlueprintAssignable,DisplayName=OnComplete)
	FAsyncDelegate OnCompleteDelegate;
	
	//UPROPERTY(BlueprintAssignable)
	//FAsyncDelegateTwo OnUpdateDelegateTwo;

private:
	
	bool bIsUseCurve = false;
	float Time;
	float LastTime = 0.f;
	float DeltaSeconds;
	float FirstDelay;
	
	UObject* WorldContext;
	UWorld* World;
	FTimerHandle TimerHandle;
	
public:
	UFUNCTION()
	void OnUpdate();
};
