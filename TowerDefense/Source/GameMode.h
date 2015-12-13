//  GameMode.h
//
//  Created by Jimmy Chen on 9/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"
#include "Tile.h"
#include "Spawner.h"
#include "SphereCollision.h"
#include "HUD.h"
#include "FontComponent.h"

class GameMode : public Actor
{
    DECL_ACTOR(GameMode, Actor);
public:
    GameMode(Game& game);
    ~GameMode();
    void BeginPlay() override;
    void Tick(float deltaTime) override;
    TilePtr& GetSelectedTile(){ return mSelected;}
    void SetSelectedTile();
    void BuildCannonTower();
    void BuildFrostTower();
    TilePtr& GetGridElement(int x, int y) { return mGrid[y][x];}
    
    int GetHealth() { return mHealth; }
    void DeductHealth(int damage){ mHealth -= damage;}
    
    int GetMoney() { return mMoney;}
    void AddMoney(int money){ mMoney += money; }
    
    HUDPtr GetHUD(){ return mHUD;}
private:
    int mHealth;
    int mMoney;
    int time;
    
    //Grid of tiles rows by columns (y by x, top left to bottom right)
    TilePtr mGrid[9][18];
    TilePtr mSelected;
    int PrevColorIndex;
    TilePtr RedTile;
    SphereCollisionPtr mCollisionComponent;
    
    HUDPtr mHUD;
    FontComponentPtr mFontComponent;
    
    SpawnerPtr mSpawner;
};

DECL_PTR(GameMode);