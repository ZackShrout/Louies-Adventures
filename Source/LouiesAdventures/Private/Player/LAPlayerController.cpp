// Copyright BunnySoft


#include "Player/LAPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/LAPlayer.h"

void ALAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(LAContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem{ ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) })
		Subsystem->AddMappingContext(LAContext, 0);

	// These will probably change later, but this helps for debugging for now
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ALAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALAPlayerController::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALAPlayerController::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &ALAPlayerController::StopJump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ALAPlayerController::StopJump);
	EnhancedInputComponent->BindAction(SlurpAction, ETriggerEvent::Started, this, &ALAPlayerController::Slurp);
}

void ALAPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector{ InputActionValue.Get<FVector2D>() };

	if (APawn* ControlledPawn{ GetPawn<APawn>() })
	{
		ALAPlayer* ControlledCharacter{ CastChecked<ALAPlayer>(ControlledPawn) };
		
		if (InputAxisVector.Y < -.8f && !ControlledCharacter->IsCrouching())
			ControlledCharacter->ShouldCrouch(true);

		if (InputAxisVector.Y > .8f && ControlledCharacter->IsCrouching())
			ControlledCharacter->ShouldCrouch(false);

		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f),
		                                 InputAxisVector.X * (!ControlledCharacter->IsCrouching()
			                                 ? 1.f
			                                 : ControlledCharacter->GetCrawlSpeedFactor()));

		if (InputAxisVector.X > .0f)
			SetControlRotation(FRotator(0.f, 0.f, 0.f));
		else if (InputAxisVector.X < .0f)
			SetControlRotation(FRotator(0.f, 180.f, 0.f));
	}
}

void ALAPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn{ GetPawn<APawn>() })
	{
		ALAPlayer* ControlledCharacter{ CastChecked<ALAPlayer>(ControlledPawn) };

		ControlledCharacter->Jump();
		ControlledCharacter->ShouldCrouch(false);
	}
}

void ALAPlayerController::StopJump(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn{ GetPawn<APawn>() })
	{
		ALAPlayer* ControlledCharacter{ CastChecked<ALAPlayer>(ControlledPawn) };

		ControlledCharacter->StopJumping();
	}
}

void ALAPlayerController::Slurp(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn{ GetPawn<APawn>() })
	{
		ALAPlayer* ControlledCharacter{ CastChecked<ALAPlayer>(ControlledPawn) };

		if (!ControlledCharacter->IsSlurping())
			ControlledCharacter->DoSlurp();
	}
}
