// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BeatMarker.generated.h"

UCLASS()
class SDBX_API ABeatMarker : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABeatMarker();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	float GetXPosition(float t);

	void SetBMSprite(int pNum);

	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSprite* Player1Sprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UPaperSprite* Player2Sprite;

	UPROPERTY(EditDefaultsOnly, Category = "Sprites")
	class UPaperSpriteComponent* PrimarySprite;

	class APlayerController* playerController;

	float positionX;
	float positionY;

	int32 playerNum;

	UPROPERTY(EditAnywhere, Category = "Position")
	float multX = 0.0;
	UPROPERTY(EditAnywhere, Category = "Position")
	float multY = 20.0;
	UPROPERTY(EditAnywhere, Category = "Position")
	float depthOffset = 10.1;
	UPROPERTY(EditAnywhere, Category = "Position")
	float speed = 60.0;
	UPROPERTY(EditAnywhere, Category = "Position")
	float fScale = 0.0020;
	
	float bpm = 60;

	float life = 0.0;

	float screenWidth;
};
