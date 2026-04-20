// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gameplay/NoSkelCharacter.h"

ANoSkelCharacter::ANoSkelCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
}
