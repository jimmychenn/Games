// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BeatSpawner.generated.h"

UCLASS()
class SDBX_API ABeatSpawner : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABeatSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> actorClass;

	UPROPERTY(EditAnywhere, Category = Player)
		int32 playerNum;

    void SpawnPoint();
    
    
protected:
	
    
private:

};
