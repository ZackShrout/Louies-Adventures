// Copyright BunnySoft

#pragma once

#include "CoreMinimal.h"
#include "LACharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LAPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LOUIESADVENTURES_API ALAPlayer : public ALACharacterBase
{
	GENERATED_BODY()

public:
	ALAPlayer();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
};
