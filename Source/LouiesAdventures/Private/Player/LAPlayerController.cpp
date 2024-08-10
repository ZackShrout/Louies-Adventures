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
}

void ALAPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector{ InputActionValue.Get<FVector2D>() };

	if (APawn* ControlledPawn{ GetPawn<APawn>() })
	{
		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f), InputAxisVector.X);

		if (InputActionValue.GetMagnitude() >= 0.f)
			SetControlRotation(FRotator(0.f, 0.f, 0.f));
		else
			SetControlRotation(FRotator(0.f, 180.f, 0.f));
	}
}

void ALAPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn{ GetPawn<APawn>() })
	{
		ALAPlayer* ControlledCharacter{ CastChecked<ALAPlayer>(ControlledPawn) };

		ControlledCharacter->Jump();
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
