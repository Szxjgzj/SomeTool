#include "Factories/SomeToolPakPrimaryAssetFactory.h"

#include "Pak/SomeToolPakPrimaryAsset.h"

#define LOCTEXT_NAMESPACE "SomeToolPakPrimaryAssetFactory"

USomeToolPakPrimaryAssetFactory::USomeToolPakPrimaryAssetFactory()
{
	SupportedClass = USomeToolPakPrimaryAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

FString USomeToolPakPrimaryAssetFactory::GetDefaultNewAssetName() const
{
	return TEXT("DA_PakEntry_New");
}

FText USomeToolPakPrimaryAssetFactory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "SomeTool Pak Entry");
}

bool USomeToolPakPrimaryAssetFactory::ConfigureProperties()
{
	return true;
}

UObject* USomeToolPakPrimaryAssetFactory::FactoryCreateNew(
	UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn)
{
	return NewObject<USomeToolPakPrimaryAsset>(InParent, USomeToolPakPrimaryAsset::StaticClass(), Name, Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE
