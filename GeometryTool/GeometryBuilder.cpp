#include "GeometryBuilder.h"
#include "GeometryScript/MeshBooleanFunctions.h"
#include "GeometryScript/MeshDecompositionFunctions.h"

AGeometryBuilder::AGeometryBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGeometryBuilder::BeginPlay()
{
	Super::BeginPlay();
}

void AGeometryBuilder::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UDynamicMesh* AGeometryBuilder::BuildShapeFormStaticMesh()
{
	UDynamicMesh* Mesh = AllocateComputeMesh();
	//Mesh;
	return Mesh;
}

bool AGeometryBuilder::ChangeShape()
{
	return false;
}
UDynamicMeshPool* AGeometryBuilder::GetComputeMeshPool()
{
	if (DynamicMeshPool == nullptr && bEnableComputeMeshPool)
	{
		DynamicMeshPool = NewObject<UDynamicMeshPool>();
	}
	return DynamicMeshPool;
}

UDynamicMesh* AGeometryBuilder::AllocateComputeMesh()
{
	if (bEnableComputeMeshPool)
	{
		UDynamicMeshPool* UsePool = GetComputeMeshPool();
		if (UsePool)
		{
			return UsePool->RequestMesh();
		}
	}
	return nullptr;
}


bool AGeometryBuilder::ReleaseComputeMesh(UDynamicMesh* Mesh)
{
	if (Mesh)
	{
		UDynamicMeshPool* UsePool = GetComputeMeshPool();
		if (UsePool != nullptr)
		{
			UsePool->ReturnMesh(Mesh);
			return true;
		}
	}
	return false;
}


void AGeometryBuilder::ReleaseAllComputeMeshes()
{
	UDynamicMeshPool* UsePool = GetComputeMeshPool();
	if (UsePool)
	{
		UsePool->ReturnAllMeshes();
	}
}

void AGeometryBuilder::FreeAllComputeMeshes()
{
	UDynamicMeshPool* UsePool = GetComputeMeshPool();
	if (UsePool)
	{
		UsePool->FreeAllMeshes();
	}
}
