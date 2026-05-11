#pragma once

#include "Commandlets/Commandlet.h"
#include "SomeToolPakBuildCommandlet.generated.h"

UCLASS()
class USomeToolPakBuildCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	USomeToolPakBuildCommandlet();

	virtual int32 Main(const FString& Params) override;
};
