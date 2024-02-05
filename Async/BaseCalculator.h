#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCalculator.generated.h"

DECLARE_MULTICAST_DELEGATE(FCalculatorDelegate);
class FBaseCalculator:public FRunnable
{
public:
	FBaseCalculator(const FString& name,const FCalculatorDelegate::FDelegate& Delegate);
	FBaseCalculator();
	~FBaseCalculator();
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	
	TArray<FCalculatorDelegate::FDelegate> OnRunDelegates;
	FCalculatorDelegate::FDelegate OnRunDelegates111;
	FString Name="CalculThread";
	
	FRunnableThread* CalculThread = nullptr;
};

UCLASS(BlueprintType,Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOMETOOL_API UBaseCalculator : public UActorComponent
{
	GENERATED_BODY()

public:
	friend class FBaseCalculator;
	UBaseCalculator();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void StartCalculate();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnCalculateWork();
};
