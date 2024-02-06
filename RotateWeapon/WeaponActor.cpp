#include "WeaponActor.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

