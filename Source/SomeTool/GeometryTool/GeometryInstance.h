// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GeometryInstance.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOMETOOL_API UGeometryInstance : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
	UGeometryInstance();
protected:
	virtual void BeginPlay() override;
protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	UFUNCTION(BlueprintCallable,Category="Geometry Instance Tool")
	void GetPointsByCustomRect(
		FTransform OriginTransform,
		FVector Counts3D = FVector(5,5,1),
		FVector Distance3D = FVector(100.f,100.f,100.f),
		bool bIsUseWorldSpace = true,
		FRotator Rotator_A = FRotator(0,0,0),
		FRotator Rotator_B = FRotator(0,0,0),
		bool bIsUseRandomRotation = false,
		FVector Size_A = FVector(1,1,1),
		FVector Size_B = FVector(1,1,1),
		bool bIsUseRandomSize = false);

	UFUNCTION(BlueprintCallable,Category="Geometry Instance Tool")
	TArray<FTransform> GetPointsByShape(
		UShapeComponent* Shape,
		bool bIsAddInstance = true,
		float Distance = 100.f,
		float Noise= 0.f,
		bool bIsUseLookAtOrigin = false,
		FRotator Rotator_A = FRotator(0,0,0),
		FRotator Rotator_B = FRotator(0,0,0),
		bool bIsUseRandomRotation = false,
		FVector Size_A = FVector(1,1,1),
		FVector Size_B = FVector(1,1,1),
		bool bIsUseRandomSize = false,
		FRotator Rotator_Delta = FRotator(0,0,0)
		);

	UFUNCTION(BlueprintCallable,Category="Geometry Instance Tool")
	TArray<FTransform> GetPointsByCircle(int32 InitCount=5,float InitAngle=0.f,int32 Level=3,float RadiusDelta=100.0f);
};
