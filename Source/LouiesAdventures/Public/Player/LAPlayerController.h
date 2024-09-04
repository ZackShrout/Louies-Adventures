// Copyright BunnySoft

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "LAPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class LOUIESADVENTURES_API ALAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALAPlayerController() {  }
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void StopJump(const FInputActionValue& InputActionValue);
	void Slurp(const FInputActionValue& InputActionValue);
	void TryWallInteract(bool bDrawDebug = false) const;

	FEnhancedInputActionValueBinding* MoveActionBinding{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> LAContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> SlurpAction;
};
