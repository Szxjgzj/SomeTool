// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueprintObject.h"
#include "Engine/World.h"

UBlueprintObject::UBlueprintObject()
{
}

UWorld* UBlueprintObject::GetWorld() const
{
	// 如果有缓存的世界上下文，返回它
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(),
		TEXT("Actor: %s has a null OuterPrivate in AActor::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (ULevel* Level = GetLevel())
		{
			return Level->OwningWorld;
		}
	}
	return nullptr;
}

class ULevel* UBlueprintObject::GetLevel() const
{
	return GetTypedOuter<ULevel>();
}
