// Copyright BunnySoft

#pragma once

#include "CoreMinimal.h"
#include "LACharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	float GetCrawlSpeedFactor() const { return CrawlSpeedFactor; }
	float GetWallTraceLength() const { return WallTraceLength; };
	
	UFUNCTION(BlueprintImplementableEvent)
	void DoSlurp();

	UFUNCTION(BlueprintCallable)
	bool IsSlurping() const { return bSlurping; }

	UFUNCTION(BlueprintCallable)
	void ShouldSlurp(const bool bShouldSlurp) { bSlurping = bShouldSlurp; }

	UFUNCTION(BlueprintCallable)
	bool IsCrouching() const { return bCrouching; }

	UFUNCTION(BlueprintCallable)
	void ShouldCrouch(const bool bShouldCrouch) { bCrouching = bShouldCrouch; }

	UFUNCTION(BlueprintCallable)
	bool IsWallClimbing() const { return bWallClimbing; }

	UFUNCTION(BlueprintCallable)
	void ShouldWallClimb(const bool bShouldWallClimb);

	UFUNCTION(BlueprintCallable)
	bool IsWallSliding() const { return bWallSliding; }

	UFUNCTION(BlueprintCallable)
	void ShouldWallSlide(const bool bShouldWallSlide);
	
protected:
	bool bSlurping{ false };
	bool bCrouching{ false };
	bool bWallClimbing{ false };
	bool bWallSliding{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrawlSpeedFactor{ 0.5f };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float WallTraceLength{ 40.f };

private:
	float GravityScale{ 5.5f };
};
