// Copyright Epic Games, Inc. All Rights Reserved.

#include "Blueprint/BlueprintObject.h"

#include "Engine/Engine.h"
#include "Engine/Level.h"
#include "Engine/World.h"

UBlueprintObject::UBlueprintObject()
{
}

UWorld* UBlueprintObject::GetWorld() const
{
	if (CachedWorld.IsValid())
	{
		return CachedWorld.Get();
	}

	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(),
		TEXT("Object: %s has a null OuterPrivate in UBlueprintObject::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (UWorld* OuterWorld = GetOuter()->GetWorld())
		{
			return OuterWorld;
		}

		if (ULevel* Level = GetLevel())
		{
			return Level->OwningWorld;
		}
	}

	return nullptr;
}

void UBlueprintObject::SetWorldContextObject(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		CachedWorld.Reset();
		return;
	}

	if (GEngine)
	{
		CachedWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	}
	else
	{
		CachedWorld = WorldContextObject->GetWorld();
	}
}

class ULevel* UBlueprintObject::GetLevel() const
{
	return GetTypedOuter<ULevel>();
}
