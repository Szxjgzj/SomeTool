#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

class UShapeComponent;

UCLASS()
class SOMETOOLMATH_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="SomeTool|Math")
	static const FVector GetBezierPoint(const TArray<FVector>& Points, float Progress);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Math")
	static TArray<FTransform> GetPointsByShape(
		UShapeComponent* Shape,
		float Distance = 100.0f,
		float Noise = 0.0f,
		bool bIsUseLookAtOrigin = false,
		FRotator Rotator_A = FRotator(0, 0, 0),
		FRotator Rotator_B = FRotator(0, 0, 0),
		bool bIsUseRandomRotation = false,
		FVector Size_A = FVector(1, 1, 1),
		FVector Size_B = FVector(1, 1, 1),
		bool bIsUseRandomSize = false);
};
