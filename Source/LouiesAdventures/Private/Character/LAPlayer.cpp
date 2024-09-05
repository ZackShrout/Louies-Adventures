// Copyright BunnySoft


#include "Character/LAPlayer.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"

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
	GetCharacterMovement()->GravityScale = GravityScale;

	GetSprite()->SetRelativeTransform(FTransform(FVector(-5.f, 0.f, -2.1f)));

	JumpMaxHoldTime = 0.4f;
}

void ALAPlayer::ShouldWallClimb(const bool bShouldWallClimb)
{
	bWallClimbing = bShouldWallClimb;

	if (bWallClimbing) ShouldWallSlide(false);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	
	MovementComponent->GravityScale = bWallClimbing ? 0.f : GravityScale;
	MovementComponent->Velocity.Z = bWallClimbing ? FMath::Max(0.0, MovementComponent->Velocity.Z) : MovementComponent->Velocity.Z;
	GetSprite()->SetRelativeTransform(FTransform(FVector(bWallClimbing ? 4.f : -5.f, 0.f, -2.1f)));
}

void ALAPlayer::ShouldWallSlide(const bool bShouldWallSlide)
{
	bWallSliding = bShouldWallSlide;

	if (bWallSliding) ShouldWallClimb(false);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	
	MovementComponent->Velocity.Z = bWallSliding ? FMath::Max(-20.0, MovementComponent->Velocity.Z) : MovementComponent->Velocity.Z;
	GetSprite()->SetRelativeTransform(FTransform(FVector(bWallSliding ? 4.f : -5.f, 0.f, -2.1f)));
}

void ALAPlayer::WallJump()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();

	if (bWallClimbing)
	{
		MovementComponent->GravityScale = GravityScale;
		MovementComponent->Velocity.Z = FMath::Max(-20.0, MovementComponent->Velocity.Z);
	}

	GetSprite()->SetRelativeTransform(FTransform(FVector(-5.f, 0.f, -2.1f)));
	MovementComponent->Velocity.Z = FMath::Max<FVector::FReal>(MovementComponent->Velocity.Z, WallJumpStrength);
}
