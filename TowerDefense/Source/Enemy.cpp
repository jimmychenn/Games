//  Enemy.cpp
//
//  Created by Jimmy Chen on 10/3/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Enemy.h"
#include "Game.h"
#include "Tile.h"
#include "World.h"
#include "CannonBall.h"
#include "HUD.h"

IMPL_ACTOR(Enemy, Actor);

Enemy::Enemy(Game& game) : Actor(game)
{
    health = 3;
    mMeshComponentPtr = MeshComponent::Create(*this);
    auto mesh = GetGame().GetAssetCache().Load<Mesh>("Meshes/Peasant.itpmesh2");
    mMeshComponentPtr->SetMesh(mesh);
    
    mNavComponentPtr = NavComponent::Create(*this);
    mNavComponentPtr->SetLinearSpeed(60.0f);
    mNavComponentPtr->SetLinearAxis(1.0f);
    mNavComponentPtr->SetStartNode(mGame.GetNavWorld().GetStartNode());
    
    mSphereCollisionPtr = SphereCollision::Create(*this);
    mSphereCollisionPtr->RadiusFromMesh(mesh);
    mSphereCollisionPtr->SetScale(0.5f);
    
    mAudioComponentPtr = AudioComponent::Create(*this);
    mDieSound = GetGame().GetAssetCache().Load<Sound>("Sounds/WilhelmScream.wav");
}

Enemy::~Enemy()
{
    
}

void Enemy::BeginTouch(Actor& other)
{
    Super::BeginTouch(other);
    
    if(IsAlive() && IsA<Tile>(other))
    {
        SetIsAlive(false);
        if(mGame.GetGameMode()->GetHealth() >= 20)
            mGame.GetGameMode()->DeductHealth(20);
        if(mGame.GetGameMode()->GetHealth() <= 0)
        {
            mGame.GetGameMode()->GetHUD()->GameOver();
            mGame.SetGameOver();
        }
    }
    else if(IsAlive() && IsA<CannonBall>(other) )
    {
        other.SetIsAlive(false);
        health--;
        if(health == 0)
        {
            SetIsAlive(false);
            mAudioComponentPtr->PlaySound(mDieSound);
            mGame.GetGameMode()->AddMoney(10);
        }
    }
}

void Enemy::BeginPlay()
{
    mGame.GetWorld().AddEnemy(this);
}

void Enemy::EndPlay()
{
    Super::EndPlay();
    SetIsAlive(false);
    mGame.GetWorld().RemoveEnemy(this);
}

void Enemy::Slow()
{
    mNavComponentPtr->SetLinearAxis(0.5f);
    TimerHandle handle;
    GetGame().GetGameTimers().SetTimer(handle, this, &Enemy::Unslow, 1.0f);
    mMeshComponentPtr->SetIndex(1);
}

void Enemy::Unslow()
{
    mNavComponentPtr->SetLinearAxis(1.0f);
    mMeshComponentPtr->SetIndex(0);
}