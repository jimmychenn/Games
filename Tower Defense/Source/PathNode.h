//  PathNode.h
//
//  Created by Jimmy Chen on 10/6/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Tile.h"
#include "Math.h"

struct PathNode{
    std::vector<PathNode*> mAdjacencyList;
    TilePtr mTile;
    Vector2 mPosition;
    PathNode* mParent;
    float fVal = 0.0f;
    float gVal = 0.0f;
    float hVal = 0.0f ;
    bool IsBlocked = false;
    
    void ComputehVal(PathNode* target)
    {
        Vector2 TargetVector = target->mPosition - mPosition;
        hVal = std::abs(TargetVector.y) + std::abs(TargetVector.y);
    }

};