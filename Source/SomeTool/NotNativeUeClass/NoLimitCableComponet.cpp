// Fill out your copyright notice in the Description page of Project Settings.


#include "NoLimitCableComponet.h"


// Sets default values for this component's properties
UNoLimitCableComponet::UNoLimitCableComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	NumSegments = MaxNumSegments;
	// ...
}


// Called when the game starts
void UNoLimitCableComponet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNoLimitCableComponet::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

