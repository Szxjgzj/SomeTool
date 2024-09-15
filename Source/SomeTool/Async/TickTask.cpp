// Fill out your copyright notice in the Description page of Project Settings.


#include "TickTask.h"

UTickTask::~UTickTask()
{
	UE_LOG(LogTemp,Warning,TEXT("Task Delete:%s"),*GetName());
}

bool UTickTask::IsInstantiated() const
{
	return !HasAllFlags(RF_ClassDefaultObject);
}

UWorld* UTickTask::GetWorld() const
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

bool UTickTask::ImplementsGetWorld() const
{
	return true;
}

TStatId UTickTask::GetStatId() const
{
	return Super::GetStatID();
}

bool UTickTask::IsTickable() const
{
	return true;
}

void UTickTask::PostInitProperties()
{
	UObject::PostInitProperties();
}

void UTickTask::Tick(float DeltaTime)
{
	if (IsStartTick)
	{
		if (GetOwner())
		{
			OnTickEventDelegate.Broadcast();
		}
		else
		{
			MarkAsGarbage();
		}
	}
}

UObject* UTickTask::GetOwner() const
{
	return Owner;
}
