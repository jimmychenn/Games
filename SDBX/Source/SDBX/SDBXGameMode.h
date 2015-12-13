// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BeatSlot.h"
#include "BeatSpawner.h"
#include "SDBXGameMode.generated.h"

UCLASS(minimalapi)
class ASDBXGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASDBXGameMode();
	void BeginPlay() override;
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	void SetScore(float delta){ Score = delta; }
    
    void ParseSongNames();
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "LocalMP")
	class ASDBXCharacter* GetP1(){ return p1; }
	UFUNCTION(BlueprintCallable, Category = "LocalMP")
	class ASDBXCharacter* GetP2(){ return p2; }

    UFUNCTION(BlueprintCallable, Category = "GameMode Function")
    void SetSongLoop();

	UFUNCTION(BlueprintCallable, Category = "GameMode Function")
		bool isGameOver() { return gameOver; }

	UFUNCTION(BlueprintCallable, Category = "GameMode Function")
		int32 GetWinner();

protected:
	ABeatSpawner * BeatSpawner1;
	ABeatSpawner * BeatSpawner2;
	ABeatSlot * BeatSlot1;
	ABeatSlot * BeatSlot2;
	bool firstPlayerSpawned;

	class ASDBXCharacter* p1;
	class ASDBXCharacter* p2;

	/** Keeps track of player 1's score for the bar position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Scoring)
	float Score = 0.5;
    
    float startOffset;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TArray<FString> SongNames;
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* songLoop;
    
    UPROPERTY(Transient)
    class UAudioComponent* songAC;

private:
    //BeatSpawner initialization functions
    void InitializeSpawners();
    void ParseString(FString data);
    void StartSong();
    void SpawnPoint();
    void SetBeatTimer(float t);
    void IncrementCurrTime(){ currentTime += 1.0; }
	void GoToMainMenu();
    
    float bpm = 60;
    float songLength;
    float currentTime = 0.0f;

	bool gameOver;
};



