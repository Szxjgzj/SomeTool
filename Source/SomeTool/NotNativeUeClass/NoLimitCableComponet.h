// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CableComponent.h"

#include "NoLimitCableComponet.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType)
class SOMETOOL_API UNoLimitCableComponet : public UCableComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNoLimitCableComponet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AACable", meta=(ClampMin = "1", UIMin = "1", UIMax = "1000"))
	int32 MaxNumSegments = 100;
};
