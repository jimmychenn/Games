// Fill out your copyright notice in the Description page of Project Settings.

#include "SDBX.h"
#include "SDBXPlayerController.h"

ASDBXPlayerController::ASDBXPlayerController(){
	bShowMouseCursor = false;
}

void ASDBXPlayerController::SetupInputComponent(){
	int32 id = GetLocalPlayer()->GetControllerId();
	InputComponent->BindAxis("MoveRight", this, &ASDBXPlayerController::MoveRight);
}

void ASDBXPlayerController::MoveRight(float Value)
{
	// add movement in that direction
	if (Value != 0.0f){
		APawn* Pawn = GetPawn();
		if (Pawn)
		{
			Pawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	}
}

void ASDBXPlayerController::Jump(){
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		Pawn->AddMovementInput(FVector(0.0f, 0.0f, 0.0f), JumpHeight);
	}

}




