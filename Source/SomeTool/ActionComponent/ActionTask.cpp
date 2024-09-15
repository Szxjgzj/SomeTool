// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionTask.h"

#include "ActionComponent.h"

UActionTask::~UActionTask()
{
	UE_LOG(LogTemp,Warning,TEXT("Task Delete:%s"),*GetName());
}

bool UActionTask::IsInstantiated() const
{
	return !HasAllFlags(RF_ClassDefaultObject);
}

UWorld* UActionTask::GetWorld() const
{
	if (UObject* Outer = GetOuter())
	{
		if (!HasAnyFlags(RF_ClassDefaultObject)
			&& !Outer->HasAnyFlags(RF_BeginDestroyed)
			&& !Outer->IsUnreachable())
		{
			return Outer->GetWorld();
		}
	}
	return nullptr;
}

bool UActionTask::ImplementsGetWorld() const
{
	return true;
}

void UActionTask::StartTask()
{
	if (GetActionComponent() && GetOwner())
	{
		if (bIsEnd)
		{
			bIsEnd = false;
			OnTickEventDelegate.RemoveAll(this);
			//UE_LOG(LogTemp,Warning,TEXT("Task Start:%s"),*GetName());
			OnTaskStart();
		}
	}
}

void UActionTask::EndTask()
{
	if (GetActionComponent() && GetOwner())
	{
		if (!bIsEnd)
		{
			bIsEnd = true;
			OnTickEventDelegate.RemoveAll(this);
			if(ActionComponent && ActionComponent->bIsAuto)
			{
				ActionComponent->ExcuteTask(ActionComponent->CuetIndex + 1);
			}
			OnTaskEnd();
		}
	}
}

UActionComponent* UActionTask::GetActionComponent()
{
	return ActionComponent;
}

AActor* UActionTask::GetOwner()
{
	return ActionComponent->GetOwner();
}

void UActionTask::PostInitProperties()
{
	UObject::PostInitProperties();
}

void UActionTask::BeginPlay_Implementation()
{
	
}

void UActionTask::UActionTask::Tick(float DeltaTime)
{
	if (!bIsToDestory)
	{
		if (GetActionComponent() && GetOwner())
		{
			OnTickEventDelegate.Broadcast();
		}
	}
}

TStatId UActionTask::GetStatId() const
{
	return Super::GetStatID();
}

bool UActionTask::IsTickable() const
{
	return true;
}

