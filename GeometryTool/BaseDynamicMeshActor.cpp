// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDynamicMeshActor.h"
#include "Components/DynamicMeshComponent.h"
#include "GeometryScript/CollisionFunctions.h"

#include "DynamicMesh/DynamicMesh3.h"
#include "DynamicMesh/MeshNormals.h"
#include "Operations/MeshConvexHull.h"
#include "Operations/MeshProjectionHull.h"
#include "UDynamicMesh.h"
#include "Components/DynamicMeshComponent.h"

#include "Selections/MeshConnectedComponents.h"
#include "DynamicSubmesh3.h"


// Sets default values
ABaseDynamicMeshActor::ABaseDynamicMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	S = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("Dynamic Mesh Componet"));

	S->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseDynamicMeshActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseDynamicMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseDynamicMeshActor::Test(UDynamicMesh* FromDynamicMesh, UDynamicMeshComponent* ToDynamicMeshComponent)
{
	if (S && FromDynamicMesh && ToDynamicMeshComponent)
	{
		FGeometryScriptCollisionFromMeshOptions Options;
		UGeometryScriptLibrary_CollisionFunctions::SetDynamicMeshCollisionFromMesh(FromDynamicMesh,ToDynamicMeshComponent,Options);
	}
}

