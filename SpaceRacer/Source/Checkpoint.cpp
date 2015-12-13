//  Checkpoint.cpp
//
//  Created by Jimmy Chen on 10/26/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "Checkpoint.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"

IMPL_ACTOR(Checkpoint, Actor);

Checkpoint::Checkpoint(Game& game) : Actor(game)
{
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Checkpoint.itpmesh2");
    auto meshcomp = MeshComponent::Create(*this);
    meshcomp->SetMesh(mesh);

    mSphereCol = SphereCollision::Create(*this);
    mSphereCol->RadiusFromMesh(mesh);
    mSphereCol->SetScale(0.75f);
}

Checkpoint::~Checkpoint()
{
    
}

