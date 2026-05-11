#include "Gameplay/NoSkelCharacter.h"

ANoSkelCharacter::ANoSkelCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
}
