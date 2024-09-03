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
	PrimaryActorTick.bCanEverTick = true;

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

void ALAPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TryWallClimb(true);
}

float ALAPlayer::GetCrawlSpeedFactor() const
{
	return CrawlSpeedFactor;
}

void ALAPlayer::ShouldSlurp(const bool bShouldSlurp)
{
	bSlurping = bShouldSlurp;
}

bool ALAPlayer::IsCrouching() const
{
	return bCrouching;
}

void ALAPlayer::ShouldCrouch(const bool bShouldCrouch)
{
	bCrouching = bShouldCrouch;
}

void ALAPlayer::TryWallClimb(bool bDrawDebug/* = false*/)
{
	FHitResult Hit;
	const TArray<AActor*> ActorsToIgnore{};
	const TArray<TEnumAsByte<EObjectTypeQuery>> Types{ ObjectTypeQuery1 }; // ObjectTypeQuery1 is WorldStatic
	
	FVector TraceVector{ GetActorForwardVector() };
	TraceVector.X *= WallTraceLength;
	FVector EndTraceLocation{ GetActorLocation() + TraceVector };

	UKismetSystemLibrary::LineTraceSingleForObjects(this, GetActorLocation(), EndTraceLocation, Types, false,
	                                                ActorsToIgnore,
	                                                bDrawDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
	                                                Hit, true);
}

bool ALAPlayer::IsSlurping() const
{
	return bSlurping;
}
