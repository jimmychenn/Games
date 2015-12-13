//  GameMode.cpp
//
//  Created by Jimmy Chen on 9/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "GameMode.h"
#include "Game.h"
#include "InputManager.h"
#include "Asteroid.h"
#include "Random.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Actor(game)
{
    mAudioC = AudioComponent::Create(*this);
    mSound = mGame.GetAssetCache().Load<Sound>("Sounds/Checkpoint.wav");
    time = 15;
    score = 0;
}

GameMode::~GameMode()
{
    mShip = nullptr;
}

void GameMode::BeginPlay()
{
    const int NUM_ASTEROIDS = 500;
    Vector3 minVec(-5000.f, -5000.f, -5000.f);
    Vector3 maxVec(5000.f, 5000.f, 5000.f);
    for (int i = 0; i < NUM_ASTEROIDS; i++){
        auto ast = Asteroid::Spawn(GetGame());
        ast->SetPosition(Random::GetVector(minVec,maxVec));
        ast->SetScale(0.75f);
    }
    mShip = Ship::Spawn(GetGame());
    mArrow = Arrow::Spawn(GetGame());
    mArrow->SetPlayer(mShip);
    SpawnCheckpoint();
    
    mHUD = HUD::Spawn(GetGame());
    GetGame().GetGameTimers().SetTimer(mHandle, this, &GameMode::CountDown, 1.0f, true);
    mHUD->UpdateTime(time);
    mHUD->UpdateScore(score);
}

void GameMode::Tick(float deltaTime)
{

}

void GameMode::CollectCheckpoint()
{
    mAudioC->PlaySound(mSound);
    SpawnCheckpoint();
    score += 100;
    mHUD->UpdateScore(score);
    time += 3;
    mHUD->UpdateTime(time);
}

void GameMode::SpawnCheckpoint()
{
    Vector3 ShipPos = mShip->GetPosition();
    float range = 1000.0f + (float) score;
    Vector3 max(range, range, range);
    Vector3 min = ShipPos - max;
    max = ShipPos + max;
    Vector3 pos = Random::GetVector(min, max);
    
    mCheckp = Checkpoint::Spawn(GetGame());
    mCheckp->SetPosition(pos);
    mArrow->SetCheckpointPos(pos);
}

void GameMode::CountDown()
{
    time -= 1;
    mHUD->UpdateTime(time);
    if(time == 0)
    {
        mShip->Die();
        mHUD->GameOver();
        mGame.SetGameOver();
    }
}
