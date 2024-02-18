// Fill out your copyright notice in the Description page of Project Settings.


#include "Map.h"


// Sets default values
AMap::AMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

