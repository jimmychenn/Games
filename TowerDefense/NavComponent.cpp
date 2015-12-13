//  NavComponent.cpp
//
//  Created by Jimmy Chen on 10/7/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "NavComponent.h"

IMPL_COMPONENT(NavComponent, MoveComponent);

NavComponent::NavComponent(Actor& owner) : MoveComponent(owner)
{
    
}

NavComponent::~NavComponent()
{
    
}

void NavComponent::SetStartNode(PathNode* start)
{
    CurrentNode = start;
}

void NavComponent::FollowPath()
{
    if(CurrentNode->mParent != nullptr)
    {
        float* startposfloat = CurrentNode->mTile->GetVector2Position();
        Vector3 startpos(startposfloat[0],startposfloat[1], 0.0f);
        
        float* endposfloat = CurrentNode->mParent->mTile->GetVector2Position();
        Vector3 endpos(endposfloat[0], endposfloat[1], 0.0f);
        
        
        float rotation = 0.0f;
        if( startposfloat[0] < endposfloat[0])
            rotation = 0.0f;
        else if (startposfloat[0] > endposfloat[0])
            rotation = 2 * Math::PiOver2;
        else if ( startposfloat[1] > endposfloat[1])
            rotation = 3 * Math::PiOver2;
        else if ( startposfloat[1] < endposfloat[1])
            rotation = Math::PiOver2;
        
        CurrentNode = CurrentNode->mParent;
        mOwner.SetRotation(rotation);
    }
}

void NavComponent::Tick(float deltaTime)
{
    float* pos = CurrentNode->mTile->GetVector2Position();
    Vector3 nodePos(pos[0], pos[1], 0.0f);
    Vector3 ownerPos = mOwner.GetPosition();
    float dist = (nodePos - ownerPos).Length();
    if(dist < 2.0f)
    {
        FollowPath();
    }
    
    Super::Tick(deltaTime);
}