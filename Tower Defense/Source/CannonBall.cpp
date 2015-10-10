//  CannonBall.cpp
//
//  Created by Jimmy Chen on 10/5/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "CannonBall.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"

IMPL_ACTOR(CannonBall, Actor);

CannonBall::CannonBall(Game& game) : Actor(game)
{
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Cannonball.itpmesh2");
    mMeshComponent = MeshComponent::Create(*this);
    mMeshComponent->SetMesh(mesh);
    
    mMoveComponent = MoveComponent::Create(*this);
    mMoveComponent->SetLinearSpeed(300.0f);
    mMoveComponent->SetLinearAxis(1.0f);
    
    mSphereCollision = SphereCollision::Create(*this);
    mSphereCollision->RadiusFromMesh(mesh);
    mSphereCollision->SetScale(0.9f);
    
}

CannonBall::~CannonBall()
{
    
}

void CannonBall::BeginPlay()
{
    Super::BeginPlay();
    TimerHandle Handle;
    mGame.GetGameTimers().SetTimer(Handle, this, &CannonBall::OnDieTimer, 3.0f);
}

void CannonBall::OnDieTimer()
{
    SetIsAlive(false);
}