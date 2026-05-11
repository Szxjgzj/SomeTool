#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SomeToolPakResourceRegistryFactory.generated.h"

UCLASS()
class SOMETOOLPAKEDITOR_API USomeToolPakResourceRegistryFactory : public UFactory
{
	GENERATED_BODY()

public:
	USomeToolPakResourceRegistryFactory();

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
