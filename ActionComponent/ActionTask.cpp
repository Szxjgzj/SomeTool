// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionTask.h"

UActionTask::~UActionTask()
{
	UE_LOG(LogTemp,Warning,TEXT("name:%s"),*GetName());
}

bool UActionTask::IsInstantiated() const
{
	return !HasAllFlags(RF_ClassDefaultObject);
}

UWorld* UActionTask::GetWorld() const
{
	if (!IsInstantiated())
	{
		return nullptr;
	}
	return UObject::GetWorld();
}

UActionComponent* UActionTask::GetActionComponent()
{
	return ActionComponent;
}

