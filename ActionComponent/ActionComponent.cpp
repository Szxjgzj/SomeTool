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

	if (!TasksClass.IsEmpty())
	{
		for (auto taskclas : TasksClass)
		{
			UActionTask* newtask = NewObject<UActionTask>(GetOuter(),taskclas);
			if (newtask)
			{
				newtask->ActionComponent = this;
				Tasks.Add(newtask);
				newtask->BeginPlay();
				UE_LOG(LogTemp,Warning,TEXT("Task Is Spawn"));
			}
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

void UActionComponent::ExcuteTask(int32 Index)
{
	if (!Tasks.IsEmpty())
	{
		CuetIndex = Index;
		if (Index >= Tasks.Num())
		{
			CuetIndex = 0;
		}
		//UE_LOG(LogTemp,Warning,TEXT("Do Next Task"));
		Tasks[CuetIndex]->StartTask();
	}
	return;
}

UActionTask* UActionComponent::GetCurtTask() const
{
	if (!Tasks.IsEmpty())
	{
		if (Tasks[CuetIndex])
		{
			return Tasks[CuetIndex];
		}
	}
	return nullptr;
}

