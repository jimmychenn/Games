// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SDBXGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SDBX_API USDBXGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    USDBXGameInstance(const FObjectInitializer& ObjectInitializer);

    void SetSongName(FString name) {SongName = name;}
    FString GetSongName(){ return SongName;}

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SongName;
	
};
