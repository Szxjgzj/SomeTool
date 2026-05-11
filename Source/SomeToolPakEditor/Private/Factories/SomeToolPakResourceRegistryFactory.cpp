#include "Factories/SomeToolPakResourceRegistryFactory.h"

#include "Pak/SomeToolPakResourceRegistry.h"

#define LOCTEXT_NAMESPACE "SomeToolPakResourceRegistryFactory"

USomeToolPakResourceRegistryFactory::USomeToolPakResourceRegistryFactory()
{
	SupportedClass = USomeToolPakResourceRegistry::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

FString USomeToolPakResourceRegistryFactory::GetDefaultNewAssetName() const
{
	return TEXT("DA_PakRegistry_New");
}

FText USomeToolPakResourceRegistryFactory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "SomeTool Pak Resource Registry");
}

bool USomeToolPakResourceRegistryFactory::ConfigureProperties()
{
	return true;
}

UObject* USomeToolPakResourceRegistryFactory::FactoryCreateNew(
	UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn)
{
	return NewObject<USomeToolPakResourceRegistry>(
		InParent,
		USomeToolPakResourceRegistry::StaticClass(),
		Name,
		Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE
