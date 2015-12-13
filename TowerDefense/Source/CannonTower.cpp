//  CannonTower.cpp
//
//  Created by Jimmy Chen on 10/4/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#include "CannonTower.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Enemy.h"
#include "CannonBall.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game& game) : Tower(game)
{

    auto towermesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Cannon.itpmesh2");
    
    auto mMeshComponent = MeshComponent::Create(*this);
    mMeshComponent->SetMesh(towermesh);
    
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &CannonTower::Attack, 2.0f,true);
    
    mAudioComponentPtr = AudioComponent::Create(*this);
    mCannonSound = mGame.GetAssetCache().Load<Sound>("Sounds/CannonFire.wav");
    
}

CannonTower::~CannonTower()
{
    
}

void CannonTower::Attack()
{
    Vector3 pos = GetWorldTransform().GetTranslation();
    Enemy* target = mGame.GetWorld().GetClosestEnemy(pos, 150.0f);
    if(target != nullptr)
    {
        Vector3 targetpos = target->GetPosition();
        Vector3 directionvector = targetpos - pos;
        directionvector.Normalize();
        Vector3 unitx(1.0f, 0.0f, 0.0f);
        float cosineangle = Dot(directionvector,unitx);
        float angle = Math::Acos(cosineangle);
    
        Vector3 crossprod = Cross(unitx,directionvector);
        if(crossprod.z < 0.0f)
            angle = angle * -1.0f;
        auto cannonball = CannonBall::Spawn(mGame);
        mAudioComponentPtr->PlaySound(mCannonSound);
        
        cannonball->SetPosition(pos);
        cannonball->SetRotation(angle);
        SetRotation(angle);
        
    }
}