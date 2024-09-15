// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ActionComponent.h"
#include "UObject/Object.h"
#include "ActionTask.generated.h"

class UActionComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEventDelegate);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEvent)
UCLASS(Blueprintable,BlueprintType)
class SOMETOOL_API UActionTask : public UObject,public FTickableGameObject
{
	GENERATED_BODY()

	friend class UActionComponent;
public:
	
	//UActionTask();
	~UActionTask();
	
private:
	bool IsInstantiated() const;
	virtual UWorld* GetWorld() const override;
	virtual bool ImplementsGetWorld() const;
public:
	
	void StartTask();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OnTaskStart();

	UFUNCTION(BlueprintCallable)
	void EndTask();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OnTaskEnd();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UActionComponent* GetActionComponent();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	AActor* GetOwner();

	UPROPERTY(BlueprintAssignable)
	FTickEventDelegate OnTickEventDelegate;

	bool bIsEnd = true;

	bool bIsToDestory = false;
	////////
	
	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintNativeEvent)
	void BeginPlay();
	
	//UFUNCTION(BlueprintNativeEvent)
	void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
private:
	FTimerHandle TimerHandle;
	UActionComponent* ActionComponent;
};
