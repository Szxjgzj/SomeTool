#include "WeaponActor.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Slience();
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::Slience()
{
	
}

void AWeaponActor::Active()
{
	
}

