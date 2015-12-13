// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SDBXPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SDBX_API ASDBXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASDBXPlayerController();

protected:
	virtual void SetupInputComponent() override;

	void MoveRight(float Value);

	void Jump();

	UPROPERTY(EditAnywhere, Category = PlayerActions)
		float JumpHeight = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
		UAnimMontage * DeathAnim;

private:
	bool isJumping;
};
