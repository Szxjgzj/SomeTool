#include "Blueprint/BlueprintObject.h"

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

	if (const UObject* OuterObject = GetOuter())
	{
		return OuterObject->GetWorld();
	}

	return nullptr;
}

void UBlueprintObject::SetWorldContextObject(UObject* WorldContextObject)
{
	CachedWorld = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
}

ULevel* UBlueprintObject::GetLevel() const
{
	if (const UWorld* World = GetWorld())
	{
		return World->PersistentLevel;
	}

	return nullptr;
}
