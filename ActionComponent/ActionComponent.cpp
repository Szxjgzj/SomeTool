// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"


// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!Tasks.IsEmpty())
	{
		for (auto task : Tasks)
		{
			UActionTask* newtask = NewObject<UActionTask>(this,task);
			if (newtask)
			{
				newtask->ActionComponent = this;
				newtask->StartTask();
			}
			//task = UActionTask::StaticClass();
		}
	}
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

