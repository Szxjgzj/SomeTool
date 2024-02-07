// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "GeometryBuilder.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SOMETOOL_API AGeometryBuilder : public AActor
{
	GENERATED_BODY()

public:
	AGeometryBuilder();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=GeometryBuilder)
	bool bEnableComputeMeshPool = true;
protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(Transient)
	TObjectPtr<UDynamicMeshPool> DynamicMeshPool;
	
public:
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, Category = GeometryBuilder)
	UDynamicMeshPool* GetComputeMeshPool();
	
	UFUNCTION(BlueprintCallable, Category = GeometryBuilder)
	UDynamicMesh* AllocateComputeMesh();
	
	UFUNCTION(BlueprintCallable, Category = GeometryBuilder)
	bool ReleaseComputeMesh(UDynamicMesh* Mesh);
	
	UFUNCTION(BlueprintCallable, Category = GeometryBuilder)
	void ReleaseAllComputeMeshes();
	
	UFUNCTION(BlueprintCallable, Category = GeometryBuilder)
	void FreeAllComputeMeshes();
	
	UFUNCTION(BlueprintCallable)
	UDynamicMesh* BuildShapeFormStaticMesh();
	
	UFUNCTION(BlueprintCallable)
	bool ChangeShape();
};
