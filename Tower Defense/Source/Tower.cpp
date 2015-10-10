//  Tower.cpp
//
//  Created by Jimmy Chen on 10/4/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "Tower.h"
#include "Game.h"
#include "Mesh.h"
#include "AudioComponent.h"
#include "Sound.h"

IMPL_ACTOR(Tower,Actor);

Tower::Tower(Game& game) : Actor(game)
{
    
    auto basemesh = mGame.GetAssetCache().Load<Mesh>("Meshes/TowerBase.itpmesh2");
    auto mMeshComponent = MeshComponent::Create(*this);
    mMeshComponent->SetMesh(basemesh);
    
    mAudioComponentPtr = AudioComponent::Create(*this);
    mBuildingSound = mGame.GetAssetCache().Load<Sound>("Sounds/Building.wav");
    mAudioComponentPtr->PlaySound(mBuildingSound);
}

Tower::~Tower()
{
    
}
