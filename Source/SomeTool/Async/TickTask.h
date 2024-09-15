// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TickTask.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEventDelegate);
UCLASS(Blueprintable,BlueprintType)
class SOMETOOL_API UTickTask : public UObject,public FTickableGameObject
{
	GENERATED_BODY()
friend class UFunctionLibrary;
	~UTickTask();
public:
	bool IsInstantiated() const;
	virtual UWorld* GetWorld() const override;

	UPROPERTY(BlueprintAssignable)
	FTickEventDelegate OnTickEventDelegate;
	
	virtual bool ImplementsGetWorld() const;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual void PostInitProperties() override;
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
	UObject* GetOwner() const;

	UFUNCTION(BlueprintImplementableEvent)
	void BeginPlay();

private:
	UObject* Owner;
	bool IsStartTick = false;
};
