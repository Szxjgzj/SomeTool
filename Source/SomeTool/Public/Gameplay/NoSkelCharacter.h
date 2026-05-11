#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NoSkelCharacter.generated.h"

/**
 * ACharacter variant that keeps capsule and character movement, but skips the default skeletal mesh component.
 * Intended as a lightweight Blueprint base when skeletal mesh behavior is not needed.
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="No Skel Character"))
class SOMETOOL_API ANoSkelCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANoSkelCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
