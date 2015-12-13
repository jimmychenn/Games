//  GameMode.h
//
//  Created by Jimmy Chen on 9/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"
#include "SphereCollision.h"
#include "HUD.h"
#include "FontComponent.h"
#include "Ship.h"
#include "Checkpoint.h"
#include "AudioComponent.h"
#include "Arrow.h"
#include "GameTimers.h"

class GameMode : public Actor
{
    DECL_ACTOR(GameMode, Actor);
public:
    GameMode(Game& game);
    ~GameMode();
    void BeginPlay() override;
    void Tick(float deltaTime) override;
    
    ShipPtr GetShip() {return mShip; }
    CheckpointPtr GetCheckpoint() {return mCheckp;}
    void CollectCheckpoint();
    void CountDown();

    int GetTime() {return time;}
    int GetScore() {return score;}
    HUDPtr GetHUD(){ return mHUD;}
private:
    void SpawnCheckpoint();
    
    int time;
    int score;
    
    ShipPtr mShip;
    CheckpointPtr mCheckp;
    ArrowPtr mArrow;
    
    HUDPtr mHUD;
    TimerHandle mHandle;
    FontComponentPtr mFontComponent;
    AudioComponentPtr mAudioC;
    SoundPtr mSound;
};

DECL_PTR(GameMode);