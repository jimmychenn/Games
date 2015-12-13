//  FrostTower.cpp
//
//  Created by Jimmy Chen on 10/4/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "FrostTower.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Enemy.h"

IMPL_ACTOR(FrostTower, Tower);

FrostTower::FrostTower(Game& game) : Tower(game)
{
    auto towermesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Frost.itpmesh2");
    
    auto mMeshComponent = MeshComponent::Create(*this);
    mMeshComponent->SetMesh(towermesh);
    
    mAudioComponentPtr = AudioComponent::Create(*this);
    mFrostSound = mGame.GetAssetCache().Load<Sound>("Sounds/Freeze.wav");    
    
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &FrostTower::Attack, 2.0f,true);
}

FrostTower::~FrostTower()
{
    
}

void FrostTower::Attack()
{
    Vector3 pos = GetWorldTransform().GetTranslation();
    std::vector<Enemy*> enemies = mGame.GetWorld().GetEnemiesInRange(pos, 150.0f);
    if(!enemies.empty())
    {
        for( auto& enemy : enemies)
        {
            enemy->Slow();
            mAudioComponentPtr->PlaySound(mFrostSound);
        }
    }
}