// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NoSkelCharacter.generated.h"

/**
 * ACharacter variant that skips the default skeletal mesh component.
 * Keeps capsule + character movement, but does not create the inherited Mesh component.
 */
UCLASS(Blueprintable, BlueprintType)
class SOMETOOL_API ANoSkelCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANoSkelCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
