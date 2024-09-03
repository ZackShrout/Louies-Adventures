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
	virtual void Tick(float DeltaSeconds) override;

	float GetCrawlSpeedFactor() const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void DoSlurp();

	UFUNCTION(BlueprintCallable)
	bool IsSlurping() const;

	UFUNCTION(BlueprintCallable)
	void ShouldSlurp(const bool bShouldSlurp);

	UFUNCTION(BlueprintCallable)
	bool IsCrouching() const;

	UFUNCTION(BlueprintCallable)
	void ShouldCrouch(const bool bShouldCrouch);
	
protected:
	bool bSlurping{ false };
	bool bCrouching{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrawlSpeedFactor{ 0.5f };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float WallTraceLength{ 40.f };

private:
	void TryWallClimb(bool bDrawDebug = false);
};
