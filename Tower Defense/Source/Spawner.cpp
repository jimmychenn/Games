//  Spawner.cpp
//
//  Created by Jimmy Chen on 10/3/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Spawner.h"
#include "Game.h"
#include "Enemy.h"

IMPL_ACTOR(Spawner,Actor);

Spawner::Spawner(Game& game) : Actor(game)
{
    mWaveNum = 0;
    mEnemyNum = 0;
    mTimeUntilNextWave = 5;
    mPauseTime = 5;
}

Spawner::~Spawner()
{
    
}

void Spawner::BeginPlay()
{
    PauseWave();
}

void Spawner::SpawnWave()
{
    mWaveNum++;
    mTimeUntilNextWave = 5 * mWaveNum + mPauseTime;
    GetGame().GetGameTimers().ClearTimer(mWaveHandle);
    
    GetGame().GetGameTimers().SetTimer(mWaveHandle, this, &Spawner::SpawnEnemy, 1.0f, true);
}

void Spawner::PauseWave()
{
    if(mPauseTime != 0)
    {
        GetGame().GetGameTimers().AddTime(mWaveHandle, 1.0f);
        mPauseTime--;
        mTimeUntilNextWave = mPauseTime;
        //Loop Pausewave when decremented from 5. (initially called only once from Spawn Enemy
        if(mPauseTime == 4)
        {
            GetGame().GetGameTimers().SetTimer(mWaveHandle, this, &Spawner::PauseWave, 1.0f, true);
        }
    }
    else
    {
        mPauseTime = 5;
        GetGame().GetGameTimers().ClearTimer(mWaveHandle);
        SpawnWave();
    }
}

void Spawner::SpawnEnemy()
{
    if(mEnemyNum < mWaveNum * 5){
        auto enemy = Enemy::Spawn(mGame);
        Vector3 pos = Vector3(-450.0f, 25.0f, 0.0f);
        enemy->SetPosition(pos);
        mEnemyNum++;
        mTimeUntilNextWave--;
    }
    else
    {
        mEnemyNum = 0;
        GetGame().GetGameTimers().ClearTimer(mWaveHandle);
        PauseWave();
    }
}
