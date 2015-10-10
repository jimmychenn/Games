//  NavComponent.h
//
//  Created by Jimmy Chen on 10/7/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "MoveComponent.h"
#include "Actor.h"
#include "PathNode.h"

class NavComponent : public MoveComponent
{
    DECL_COMPONENT(NavComponent, MoveComponent);
public:
    NavComponent(Actor& owner);
    ~NavComponent();
    void SetStartNode(PathNode* start);
    void FollowPath();
    void Tick(float deltaTime) override;
private:
    bool IsAtNode();
    PathNode* CurrentNode;
};

DECL_PTR(NavComponent);