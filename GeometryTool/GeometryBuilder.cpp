#include "GeometryBuilder.h"
#include "GeometryScript/MeshBooleanFunctions.h"
#include "GeometryScript/MeshDecompositionFunctions.h"

UGeometryBuilder::UGeometryBuilder()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UGeometryBuilder::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGeometryBuilder::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGeometryBuilder::BuildShapeFormStaticMesh()
{
	//UGeometryScriptLibrary_MeshDecompositionFunctions::CopyMeshToMesh();
	//UGeometryScriptLibrary_MeshBooleanFunctions::ApplyMeshBoolean();
}

