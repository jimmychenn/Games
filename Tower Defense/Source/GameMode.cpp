//  GameMode.cpp
//
//  Created by Jimmy Chen on 9/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "GameMode.h"
#include "Tile.h"
#include "Game.h"
#include "InputManager.h"
#include "Tower.h"
#include "FrostTower.h"
#include "CannonTower.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Actor(game)
{
    mHealth = 100;
    mMoney = 150;
}

GameMode::~GameMode()
{

}

void GameMode::BeginPlay()
{
    for(int i=0; i < 9; i++)
    {
        float ypos = 225.0f - (float) i * 50.0f;
        for(int j=0; j<18; j++)
        {
            float xpos = -450 + (float) j * 50.0f;
            Vector3 pos(xpos, ypos , 0.0f);
            auto mTile = Tile::Spawn(GetGame());
            mTile->SetPosition(pos);
            mTile ->SetIndex(j,i);
            mTile->SetVector2Position(xpos, ypos);
            
            //Hard-code a few specific tiles
            if(j == 0 && (i == 3 || i == 4 || i == 5))
                mTile->SetColor(2);
            if(j == 1 && i == 4)
                mTile->SetColor(2);
            if(j == 17 && i == 4){
                mTile->SetColor(3);
                RedTile = mTile;
            }

            mGrid[i][j] = mTile;
        }
    }
    
    auto coll = SphereCollision::Create(*RedTile);
    coll->RadiusFromMesh(RedTile->GetMeshComponent()->GetMesh());
    coll->SetScale(0.5f);
    
    GetGame().GetInput().BindAction("Select", IE_Pressed, this, &GameMode::SetSelectedTile );
    GetGame().GetInput().BindAction("Build Cannon Tower", IE_Pressed, this, &GameMode::BuildCannonTower );
    GetGame().GetInput().BindAction("Build Frost Tower", IE_Pressed, this, &GameMode::BuildFrostTower );

    
    mSpawner = Spawner::Spawn(mGame);
    mHUD = HUD::Spawn(mGame);
    time = mSpawner->GetTime();
    mHUD->UpdateTime(time);
    
    mGame.GetNavWorld().Initialize(ThisPtr());
    mGame.GetNavWorld();
    mGame.GetNavWorld().TryFindPath();
    
}

void GameMode::Tick(float deltaTime)
{
    if( mSpawner->GetTime() != time)
    {
        time = mSpawner->GetTime();
        mHUD->UpdateTime(time);
    }
}

void GameMode::SetSelectedTile( )
{
    int xpos = GetGame().GetInput().GetMousexPos();
    int ypos = GetGame().GetInput().GetMouseyPos();
    
    int xindex = -1;
    int yindex = -1;
    
    for(int j=0; j<18; j++)
    {
        float xlower = 37.0f + (float) j * 50.0f;
        float xupper = 37.0f + (float) (j+1) * 50.0f;
        if( (float) xpos > xlower && (float) xpos < xupper)
            xindex = j;
    }
    
    for(int i=0; i < 9; i++)
    {
        float ylower = 134.0f + (float) i * 50.0f;
        float yupper = 134.0f + (float) (i+1) * 50.0f;
        if( (float) ypos > ylower && (float) ypos < yupper)
            yindex = i;
    }
    
    if(xindex != -1 && yindex != -1)
    {
        if( (xindex != 0 || yindex != 3) && (xindex != 0 || yindex != 4) && (xindex != 0 || yindex != 5) && (xindex != 1 || yindex != 4) && (xindex != 17 || yindex != 4) )
        {
            if(mSelected == nullptr)
            {
                mSelected = mGrid[yindex][xindex];
                PrevColorIndex = mSelected->GetColor();
                if(PrevColorIndex> 3)
                    mSelected->SetColor(5);
                else
                    mSelected->SetColor(1);
            }
            else
            {
                mSelected->SetColor(PrevColorIndex);
                
                mSelected = mGrid[yindex][xindex];
                PrevColorIndex = mSelected->GetColor();
                if(PrevColorIndex> 3)
                    mSelected->SetColor(5);
                else
                    mSelected->SetColor(1);
            }
        }
    }
}

void GameMode::BuildCannonTower()
{
    if(!mGame.IsGameOver())
    {
        if(mSelected != nullptr)
        {
            if(! mSelected->IsTowerPresent())
            {
                if(mMoney < 30)
                {
                    mHUD->NotEnoughMoney();
                }
                else
                {
                    int* pos = mSelected->GetIndex();
                    mGame.GetNavWorld().SetTower(pos[0],pos[1]);
                    if( mGame.GetNavWorld().TryFindPath())
                    {
                        auto tower = Tower::SpawnAttached(*mSelected);
                        auto cannontower = CannonTower::SpawnAttached(*tower);
                        mSelected->SetTower(cannontower);
                        mMoney -= 30;

                    }
                    else
                    {
                        mGame.GetNavWorld().UnsetTower(pos[0],pos[1]);
                        mHUD->PathIsBlocked();
                        mGame.GetNavWorld().TryFindPath();
                    }
                }
            }
        }
    }
}

void GameMode::BuildFrostTower()
{
    if(!mGame.IsGameOver())
    {
        if(mSelected != nullptr)
        {
            if( ! mSelected->IsTowerPresent())
            {
                if(mMoney < 50)
                {
                    mHUD->NotEnoughMoney();
                }
                else
                {
                    int* pos = mSelected->GetIndex();
                    mGame.GetNavWorld().SetTower(pos[0],pos[1]);
                    if(mGame.GetNavWorld().TryFindPath() )
                    {
                        auto tower = Tower::SpawnAttached(*mSelected);
                        auto frosttower = FrostTower::SpawnAttached(*tower);
                        mSelected->SetTower(frosttower);
                        mMoney -= 50;
                    }
                    else
                    {
                        mGame.GetNavWorld().UnsetTower(pos[0],pos[1]);
                        mHUD->PathIsBlocked();
                        mGame.GetNavWorld().TryFindPath();
                    }
                }
            }
        }
    }
}
