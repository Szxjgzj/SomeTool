// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SOMETOOL_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable,Category="Some Tool Func")
	static const FVector GetBezierPoint(const TArray<FVector>& Points, float Progress);

	UFUNCTION(BlueprintCallable,Category="Some Tool Func")
	static TArray<FTransform> GetPointsByShape(
		UShapeComponent* Shape,
		float Distance = 100.f,
		float Noise= 0.f,
		bool bIsUseLookAtOrigin = false,
		FRotator Rotator_A = FRotator(0,0,0),
		FRotator Rotator_B = FRotator(0,0,0),
		bool bIsUseRandomRotation = false,
		FVector Size_A = FVector(1,1,1),
		FVector Size_B = FVector(1,1,1),
		bool bIsUseRandomSize = false
		);
};
