// Fill out your copyright notice in the Description page of Project Settings.

#include "SDBX.h"
#include "BeatSlot.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABeatSlot::ABeatSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimarySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PrimarySprite"));
}

// Called when the game starts or when spawned
void ABeatSlot::BeginPlay()
{
	Super::BeginPlay();
	FVector angle(0.0, 0.0, -90.0);
	FVector scale(fScale, fScale, fScale);
	SetActorScale3D(scale);
	FRotator rot = FRotator::MakeFromEuler(angle);
	SetActorRotation(rot);
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//Viewport Size
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	//Viewport Center!            
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
	positionX = ViewportCenter.X + ViewportSize.X/multX;
	positionY = ViewportSize.Y / multY;
	FVector location, direction;
	if (playerController){
		bool conversionCheck = playerController->DeprojectScreenPositionToWorld(positionX, positionY, location, direction);
		location.X = depthOffset;
		if (conversionCheck){
			SetActorLocation(location);
		}
	}
}

// Called every frame
void ABeatSlot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector location, direction;
	if (playerController){
		bool conversionCheck = playerController->DeprojectScreenPositionToWorld(positionX, positionY, location, direction);
		location.X = playerController->PlayerCameraManager->GetCameraLocation().X - depthOffset;
		if (conversionCheck){
			SetActorLocation(location);
		}
	}
}

