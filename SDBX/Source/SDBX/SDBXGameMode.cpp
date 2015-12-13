// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SDBX.h"
#include "SDBXGameMode.h"
#include "SDBXCharacter.h"
#include "SDBXGameInstance.h"

ASDBXGameMode::ASDBXGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	firstPlayerSpawned = false;
	gameOver = false;
}

void ASDBXGameMode::BeginPlay(){
	Super::BeginPlay();
    
    UWorld* const World = GetWorld();
    FString prefix(World->StreamingLevelsPrefix);
    FString WorldName = World->GetMapName();
    FString Levelname = WorldName.Replace(*prefix, TEXT(""));
    
    FString WorldName1 = "BeginGame";
    FString WorldName2 = "SideScrollerExampleMap";
	if (World){
        if(Levelname.Equals(WorldName1)){
            ParseSongNames();
        }
        else if(Levelname.Equals(WorldName2)){

			if (World->GetNumPawns() < 2){ //spawn second player if there are less than 2
				UGameplayStatics::CreatePlayer(World);
			}

            //find beat slots
            for (TActorIterator<ABeatSlot> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                if (ActorItr->playerNum == 0){
                    BeatSlot1 = *ActorItr;
                }
                else if (ActorItr->playerNum == 1){
                    BeatSlot2 = *ActorItr;
                }
            }

            //find beat spawners
            for (TActorIterator<ABeatSpawner> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                if (ActorItr->playerNum == 0){
                    BeatSpawner1 = *ActorItr;
                }
                else if (ActorItr->playerNum == 1){
                    BeatSpawner2 = *ActorItr;
                }
            }

            //set actor beat spawners and beat slots

            for (TActorIterator<ASDBXCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                int32 id = ((APlayerController *)ActorItr->GetController())->GetLocalPlayer()->GetControllerId();
                if (id == 0){
                    p1 = *ActorItr;
                    if (BeatSpawner1){
                        ActorItr->SetBeatSpawner(BeatSpawner1);
                    }
                    if (BeatSlot1){
                        ActorItr->SetBeatSlot(BeatSlot1);
                    }
                    
                }
                else if (id == 1){
                    p2 = *ActorItr;
                    if (BeatSpawner2){
                        ActorItr->SetBeatSpawner(BeatSpawner2);
                    }
                    if (BeatSlot2){
                        ActorItr->SetBeatSlot(BeatSlot2);
                    }
                }
            }
            
            InitializeSpawners();
        }
	}
}

void ASDBXGameMode::InitializeSpawners()
{
    //Parse the beatmap
    FString GameDir = FPaths::GameDir();
    USDBXGameInstance* GInstance = Cast<USDBXGameInstance>(GetGameInstance());
    FString CompleteFilePath = GameDir + "Content/BeatMaps/" + GInstance->GetSongName() + ".txt";
    TArray<FString> songData;
    FFileHelper::LoadANSITextFileToStrings(*CompleteFilePath, NULL, songData);
    songLength = FCString::Atof(*songData[0]);
    bpm = FCString::Atof(*songData[1]);
    startOffset = FCString::Atof(*songData[2]);
    FTimerHandle handle1;
    GetWorldTimerManager().SetTimer(handle1, this, &ASDBXGameMode::StartSong, startOffset, false);
    ParseString(songData[3]);
    
}

void ASDBXGameMode::SetSongLoop()
{
    //Set the song loop to play
    USDBXGameInstance* GInstance = Cast<USDBXGameInstance>(GetGameInstance());
    FString name = GInstance->GetSongName();
    name = name.Replace(TEXT(" "), TEXT(""));
    name = name.Replace(TEXT("("), TEXT(""));
    name = name.Replace(TEXT(")"), TEXT(""));
    FString SoundCuePath = "/Game/Audio/" + name + "." + name;
    songLoop = Cast<USoundCue>(StaticLoadObject(USoundCue::StaticClass(), NULL, *SoundCuePath));
    UE_LOG(LogTemp, Warning, TEXT("%s"), *SoundCuePath);
}

void ASDBXGameMode::ParseString(FString data){
    int measure;
    float beatTime, measureTime;
    beatTime = 60.0 / (bpm*4);
    measureTime = 16.0 * beatTime;
    for (int32 i = 0; i < data.Len(); i++){
        FString currChar = data.Mid(i, 1);
        if (currChar.Equals(TEXT("}"))){
            break;
        }
        else if (currChar.Equals(TEXT("{"))){
            measure = 0;
        }
        else if (currChar.Equals(TEXT("["))){
            measure++;
        }
        else if (currChar.Equals(TEXT(" "))){
            continue;
        }
        else if (currChar.IsNumeric()){
            FString nextChar = data.Mid(i + 1, 1);
            int32 num = FCString::Atoi(*currChar);
            if (nextChar.IsNumeric()){
                i++;
                int num2 = FCString::Atoi(*nextChar);
                num *= 10;
                num += num2;
            }
            float t = (measure - 1) * measureTime + num * beatTime;
            SetBeatTimer(t);
        }
    }
}

void ASDBXGameMode::StartSong(){
    
    if (songLoop){
        songAC = UGameplayStatics::SpawnSound2D(this, songLoop);
    }

    FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle, this, &ASDBXGameMode::IncrementCurrTime, 1.0, true);
	FTimerHandle endSongTimer;
	GetWorldTimerManager().SetTimer(endSongTimer, this, &ASDBXGameMode::OnGameOver, songLength);
}

void ASDBXGameMode::SpawnPoint(){
    BeatSpawner1->SpawnPoint();
    BeatSpawner2->SpawnPoint();
    SetBeatTimer(songLength);
}

void ASDBXGameMode::SetBeatTimer(float t){
    FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle, this, &ASDBXGameMode::SpawnPoint, t, false);
}

AActor * ASDBXGameMode::ChoosePlayerStart_Implementation(AController * Player){

	APlayerStart * player1Spawn = NULL;
	APlayerStart * player2Spawn = NULL;
	APlayerStart * startToSpawnAt = NULL;

	//player start tags
	FString tag1 = "0";
	FString tag2 = "1";

	for (TActorIterator<APlayerStart> ActorItr(GetWorld()); ActorItr; ++ActorItr){
		if (ActorItr->PlayerStartTag == FName(*tag1)){
			player1Spawn = *ActorItr;
		}
		else if (ActorItr->PlayerStartTag == FName(*tag2)){
			player2Spawn = *ActorItr;
		}
	}

	if (player1Spawn && !firstPlayerSpawned){
		startToSpawnAt = player1Spawn;
		firstPlayerSpawned = true;
	}
	else if (player2Spawn && firstPlayerSpawned){
		startToSpawnAt = player2Spawn;
	}


	return startToSpawnAt ? startToSpawnAt : Super::ChoosePlayerStart_Implementation(Player);
}

void ASDBXGameMode::ParseSongNames()
{
    FString GameDir = FPaths::GameDir();
    FString CompleteFilePath = GameDir + "Content/Songs/Songs.txt";
    FFileHelper::LoadANSITextFileToStrings(*CompleteFilePath, NULL, SongNames);
}


void ASDBXGameMode::OnGameOver(){
	gameOver = true;
	FTimerHandle MainMenuTimer;
	GetWorldTimerManager().SetTimer(MainMenuTimer, this, &ASDBXGameMode::GoToMainMenu, 5.0f);
}

int32 ASDBXGameMode::GetWinner(){
	if (Score > 0.5){ //p1 wins
		return 1;
	}
	else if (Score < 0.5){ //p2 wins
		return 2;
	} 
	else { //draw
		return 0;
	}
}

void ASDBXGameMode::GoToMainMenu(){

	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("BeginGame")));
}