// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ActionComponent.h"
#include "UObject/Object.h"
#include "ActionTask.generated.h"

class UActionComponent;
//DECLARE_EVENT_OneParam(F)
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class SOMETOOL_API UActionTask : public UObject
{
	GENERATED_BODY()

	friend class UActionComponent;
public:
	
	//UActionTask();
	~UActionTask();
	
private:
	bool IsInstantiated() const;
	UWorld* GetWorld() const override;
public:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void StartTask();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void EndTask();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UActionComponent* GetActionComponent();
	
private:
	FTimerHandle TimerHandle;
	TObjectPtr<UActionComponent> ActionComponent;
};
