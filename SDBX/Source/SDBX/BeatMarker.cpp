// Fill out your copyright notice in the Description page of Project Settings.

#include "SDBX.h"
#include "BeatMarker.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABeatMarker::ABeatMarker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimarySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PrimarySprite"));
}

// Called when the game starts or when spawned
void ABeatMarker::BeginPlay()
{
	Super::BeginPlay();
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//Viewport Size
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	
	//Viewport Center!            
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
	screenWidth = ViewportSize.X;
	positionX = playerNum*ViewportSize.X + pow(-1.0, playerNum)*multX;
	positionY = ViewportSize.Y/multY;

	FVector location, direction;
	if (playerController){
		bool conversionCheck = playerController->DeprojectScreenPositionToWorld(positionX, positionY, location, direction);
		if (conversionCheck){
			SetActorLocation(location);
		}
	}
	FVector angle(0.0, 0.0, -90.0);
	FRotator rot = FRotator::MakeFromEuler(angle);
	SetActorRotation(rot);
	FVector scale(fScale, fScale, fScale);
	SetActorScale3D(scale);
}


// Called every frame
void ABeatMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	life += DeltaTime;
	positionX += DeltaTime*speed;
	FVector location, direction;
	if (playerController){
		bool conversionCheck = playerController->DeprojectScreenPositionToWorld(GetXPosition(positionX), positionY, location, direction);
		location.X = playerController->PlayerCameraManager->GetCameraLocation().X - depthOffset;
		if (conversionCheck){
			SetActorLocation(location);
		}
	}
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	if (positionX > 1.0){
		Destroy();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(life));
	}
}

float ABeatMarker::GetXPosition(float t){
	return playerNum*screenWidth + pow(-1.0, playerNum)*t*screenWidth / 2;
}

void ABeatMarker::SetBMSprite(int pNum){
	if (pNum == 1){
		PrimarySprite->SetSprite(Player2Sprite);
	}
	else{
		PrimarySprite->SetSprite(Player1Sprite);
	}
}