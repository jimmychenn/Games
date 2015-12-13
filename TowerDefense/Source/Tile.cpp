//  Tile.cpp
//
//  Created by Jimmy Chen on 9/30/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Tile.h"
#include "Game.h"

IMPL_ACTOR(Tile, Actor);

Tile::Tile(Game& game) : Actor(game)
{
    mMeshCompPtr = MeshComponent::Create(*this);
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Tile.itpmesh2");
    mMeshCompPtr->SetMesh(mesh);
    mColor = Default;
    mMeshCompPtr->SetIndex(mColor);
}

Tile::~Tile()
{
    
}

void Tile::SetColor(int index)
{
    if( index == 0)
        mColor = Default;
    else if( index == 1)
        mColor = Selected;
    else if( index == 2)
        mColor = Green;
    else if( index == 3)
        mColor = Red;
    else if( index == 4)
        mColor = DefaultOnPath;
    else if( index == 5)
        mColor = SelectedOnPath;
    else if( index == 6)
        mColor = GreenOnPath;
    else if( index == 7)
        mColor = RedOnPath;
    
    mMeshCompPtr->SetIndex(mColor);
}

void Tile::SetTower(TowerPtr tower)
{
    mTower = tower;
}