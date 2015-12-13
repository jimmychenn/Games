//  NavWorld.h
//
//  Created by Jimmy Chen on 10/6/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#include "PathNode.h"
#include "GameMode.h"

class NavWorld
{
public:
    NavWorld();
    ~NavWorld();
    void Initialize(GameModePtr gamemode);
    void ComputehValues(PathNode* EndTarget);
    
    //UnsetTower only called when tower position is invalid
    void SetTower(int x, int y);
    void UnsetTower(int x, int y);
    
    PathNode* GetStartNode(){ return mStart;}
    
    bool TryFindPath();
private:
    void ResetPath();

    PathNode mPathNodeGrid[9][18];
    PathNode* mStart;
    PathNode* mEnd;

    
    std::unordered_set<PathNode*> OpenSet;
    std::unordered_set<PathNode*> ClosedSet;
};