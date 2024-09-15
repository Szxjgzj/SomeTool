// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionTask.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType)
class SOMETOOL_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<UActionTask>> TasksClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<UActionTask*> Tasks;
	
	UPROPERTY(EditDefaultsOnly)
	bool bIsAuto = false;
	
	int32 CuetIndex = 0;

	UFUNCTION(BlueprintCallable)
	void ExcuteTask(int32 Index = 0);

	UFUNCTION(BlueprintCallable)
	UActionTask* GetCurtTask() const;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
