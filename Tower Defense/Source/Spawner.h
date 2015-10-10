//  Spawner.h
//
//  Created by Jimmy Chen on 10/3/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"
#include "GameTimers.h"

class Spawner : public Actor
{
    DECL_ACTOR(Spawner, Actor);
public:
    Spawner(Game& game);
    ~Spawner();
    void BeginPlay() override;
    void SpawnWave();
    void PauseWave();
    void SpawnEnemy();
    
    int GetTime() {return mTimeUntilNextWave;}
private:
    int mWaveNum;
    int mEnemyNum;
    int mTimeUntilNextWave;
    int mPauseTime;
    TimerHandle mWaveHandle;
};

DECL_PTR(Spawner);