// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BeatSlot.generated.h"

UCLASS()
class SDBX_API ABeatSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeatSlot();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = "Player")
		int32 playerNum;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* PrimarySprite;

	class APlayerController* playerController;

	float positionX;
	float positionY;

	UPROPERTY(EditAnywhere, Category = "Position")
	float multX = 0.0;
	UPROPERTY(EditAnywhere, Category = "Position")
	float multY = 20.0;
	UPROPERTY(EditAnywhere, Category = "Position")
	float depthOffset = 10.1;
	UPROPERTY(EditAnywhere, Category = "Position")
	float fScale = 0.0020;
};
