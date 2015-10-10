//  Tile.h
//
//  Created by Jimmy Chen on 9/30/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "Tower.h"

class Tile : public Actor
{
    DECL_ACTOR(Tile, Actor);
public:
    Tile(Game& game);
    ~Tile();
    
    MeshComponentPtr GetMeshComponent(){return mMeshCompPtr;}

    void SetColor(int index);
    int GetColor() { return mColor; }
    
    void SetTower(TowerPtr tower);
    bool IsTowerPresent(){ if(mTower != nullptr) return true; else return false;}

    enum TextureIndex{
        Default,
        Selected,
        Green,
        Red,
        DefaultOnPath,
        SelectedOnPath,
        GreenOnPath,
        RedOnPath
    };
    
    void SetIndex(int x, int y) {mIndex[0] = x; mIndex[1] = y;}
    int* GetIndex(){ return mIndex; }
    
    void SetVector2Position(float x, float y) {mPosition[0] = x; mPosition[1] = y;}
    float* GetVector2Position() { return mPosition; }

private:
    MeshComponentPtr mMeshCompPtr;
    Tile::TextureIndex mColor;
    TowerPtr mTower;
    int mIndex[2];
    float mPosition[2];
};

DECL_PTR(Tile);