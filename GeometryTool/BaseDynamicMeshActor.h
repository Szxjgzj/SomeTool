// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDynamicMeshActor.generated.h"

class UDynamicMesh;
class UDynamicMeshComponent;

UCLASS()
class SOMETOOL_API ABaseDynamicMeshActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseDynamicMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDynamicMeshComponent* S;
	UFUNCTION(BlueprintCallable)
	void Test(UDynamicMesh* FromDynamicMesh, UDynamicMeshComponent* ToDynamicMeshComponent);
};
