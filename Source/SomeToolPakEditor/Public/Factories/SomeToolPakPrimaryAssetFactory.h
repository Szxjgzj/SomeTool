#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SomeToolPakPrimaryAssetFactory.generated.h"

UCLASS()
class SOMETOOLPAKEDITOR_API USomeToolPakPrimaryAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	USomeToolPakPrimaryAssetFactory();

	virtual FString GetDefaultNewAssetName() const override;
	virtual FText GetDisplayName() const override;
	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(
		UClass* Class,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;
};
