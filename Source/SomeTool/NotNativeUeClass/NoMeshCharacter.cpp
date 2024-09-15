#include "NoMeshCharacter.h"

ANoMeshCharacter::ANoMeshCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANoMeshCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ANoMeshCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANoMeshCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

