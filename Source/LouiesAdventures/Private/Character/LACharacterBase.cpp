// Copyright BunnySoft


#include "Character/LACharacterBase.h"

#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALACharacterBase::ALACharacterBase()
{
	UCharacterMovementComponent* MovementComponent{ GetCharacterMovement() };
	MovementComponent->bUseFlatBaseForFloorChecks = true;
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
	MovementComponent->GravityScale = 5.5f;
	MovementComponent->JumpZVelocity = 600.f;
	MovementComponent->AirControl = 0.7f;

	GetSprite()->SetCastShadow(true);
}
