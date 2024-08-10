// Copyright BunnySoft


#include "Character/LACharacterBase.h"

#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALACharacterBase::ALACharacterBase()
{
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	GetSprite()->SetCastShadow(true);
}
