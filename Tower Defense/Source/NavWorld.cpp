//  NavWorld.cpp
//
//  Created by Jimmy Chen on 10/6/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "NavWorld.h"

NavWorld::NavWorld()
{

}

NavWorld::~NavWorld()
{
    
}

void NavWorld::Initialize(GameModePtr gamemode)
{
    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 18; x++)
        {
            mPathNodeGrid[y][x].mTile = gamemode->GetGridElement(x, y);
            Vector2 vecPos(x,y);
            mPathNodeGrid[y][x].mPosition = vecPos;
            
            if( y != 0)
                mPathNodeGrid[y][x].mAdjacencyList.push_back(&mPathNodeGrid[y-1][x]);
            if( y != 8)
                mPathNodeGrid[y][x].mAdjacencyList.push_back(&mPathNodeGrid[y+1][x]);
            if( x != 0)
                mPathNodeGrid[y][x].mAdjacencyList.push_back(&mPathNodeGrid[y][x-1]);
            if( x != 17)
                mPathNodeGrid[y][x].mAdjacencyList.push_back(&mPathNodeGrid[y][x+1]);
            
        }
    }
    mStart = &mPathNodeGrid[4][0];

    mEnd = &mPathNodeGrid[4][17];
    mEnd->mParent = nullptr;
    
    ComputehValues(mStart);
}

void NavWorld::ComputehValues(PathNode* EndTarget)
{
    for(int y = 0; y < 9; y++)
    {
        for( int x = 0; x < 18; x++)
        {
            mPathNodeGrid[y][x].ComputehVal(EndTarget);
        }
    }
    
}

void NavWorld::SetTower(int x, int y)
{
    mPathNodeGrid[y][x].IsBlocked = true;
}

void NavWorld::UnsetTower(int x, int y)
{
    mPathNodeGrid[y][x].IsBlocked = false;
}


bool NavWorld::TryFindPath()
{
    ResetPath();
    
    PathNode* currentNode = mEnd;
    ClosedSet.insert(currentNode);
    
    while(currentNode != mStart)
    {
        for(int i=0; i < currentNode->mAdjacencyList.size(); i++)
        {
            PathNode* adjNode = currentNode->mAdjacencyList[i];
            if(adjNode->IsBlocked)
            {
                continue;
            }
            else if( ClosedSet.find(adjNode) != ClosedSet.end())
            {
                continue;
            }
            else if( OpenSet.find(adjNode) != OpenSet.end())
            {
                float new_gVal = currentNode->gVal + 1;
                if (new_gVal < adjNode->gVal)
                {
                    adjNode->mParent = currentNode;
                    adjNode->gVal = new_gVal;
                    adjNode->fVal = adjNode->gVal + adjNode->hVal;
                }
            }
            else
            {
                adjNode->mParent = currentNode;
                adjNode->gVal = currentNode->gVal+1;
                adjNode->fVal = adjNode->gVal + adjNode->hVal;
                OpenSet.insert(adjNode);
            }
        }
        
        if(OpenSet.empty() ){
            return false;
        }
        
        currentNode = *OpenSet.begin();
        for( auto& node : OpenSet)
        {
            PathNode* minfnode = node;
            if( minfnode->fVal < currentNode->fVal)
            {
                currentNode = minfnode;
            }
        }
        ClosedSet.insert(currentNode);
        OpenSet.erase(currentNode);
    }
    
    while(currentNode->mParent != nullptr)
    {
        int ColorIndex = currentNode->mTile->GetColor();
        currentNode->mTile->SetColor(ColorIndex + 4);
        currentNode = currentNode->mParent;
    }
    
    return true;
}


void NavWorld::ResetPath()
{
    OpenSet.clear();
    ClosedSet.clear();
    PathNode* node = mStart;
    while(node->mParent != nullptr)
    {
        int colorindex = node->mTile->GetColor();
        node->mTile->SetColor(colorindex - 4);
        node = node->mParent;
    }
}