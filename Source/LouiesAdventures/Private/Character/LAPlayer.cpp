// Copyright BunnySoft


#include "Character/LAPlayer.h"

#include "PaperFlipbookComponent.h"
#include "Animation/AnimInstanceProxy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetSystemLibrary.h"

ALAPlayer::ALAPlayer()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->SetRelativeRotation(FRotator(-15.f, -90.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f);
	GetCapsuleComponent()->SetCapsuleRadius(34);

	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->FallingLateralFriction = 50.f;

	GetSprite()->SetRelativeTransform(FTransform(FVector(-5.f, 0.f, -2.1f)));

	JumpMaxHoldTime = 0.4f;
}
