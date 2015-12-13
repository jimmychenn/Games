//  Arrow.cpp
//
//  Created by Jimmy Chen on 10/26/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "Arrow.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Math.h"

IMPL_ACTOR(Arrow, Actor);

Arrow::Arrow(Game& game) : Actor(game)
{
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Arrow.itpmesh2");
    auto meshC = MeshComponent::Create(*this);
    meshC->SetMesh(mesh);
}

Arrow::~Arrow()
{
    
}

void Arrow::BeginPlay()
{
    UpdateWorldPos();
}

void Arrow::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    UpdateWorldPos();
    
    Vector3 shippos = mPlayer->GetPosition();
    Vector3 checkpos = mCheckpointPos;
    Vector3 direction = checkpos - shippos;
    direction.Normalize();
    if( direction.x == 1 && direction.y == 0 && direction.z == 0)
    {
        SetRotation(Quaternion::Identity);
    }
    else
    {
        Vector3 axis = Cross(Vector3::UnitX,direction);
        float angle = Math::Acos(Dot(Vector3::UnitX,direction));
        axis.Normalize();
        Quaternion rotation(axis, angle);
        SetRotation(rotation);
        
    }
}

void Arrow::UpdateWorldPos()
{
    Vector3 pos = mGame.GetRenderer().Unproject(Vector3(0, 150, 0.6));
    SetPosition(pos);
}