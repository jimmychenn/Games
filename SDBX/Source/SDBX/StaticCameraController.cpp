// Fill out your copyright notice in the Description page of Project Settings.

#include "SDBX.h"
#include "StaticCameraController.h"


// Sets default values
AStaticCameraController::AStaticCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStaticCameraController::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerController = this->GetWorld()->GetFirstPlayerController();
	if (this->PlayerController && this->ViewTarget)
	{
		this->PlayerController->SetViewTarget(this->ViewTarget);
	}
	
}

