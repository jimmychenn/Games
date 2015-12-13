// Fill out your copyright notice in the Description page of Project Settings.

#include "SDBX.h"
#include "BeatSpawner.h"
#include "BeatMarker.h"
#include "SDBXGameInstance.h"

// Sets default values
ABeatSpawner::ABeatSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeatSpawner::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void ABeatSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABeatSpawner::SpawnPoint(){
    ABeatMarker *bM = GetWorld()->SpawnActor<ABeatMarker>(actorClass);
    bM->playerNum = playerNum;
	bM->SetBMSprite(playerNum);
}



