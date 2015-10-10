//  CannonBall.h
//
//  Created by Jimmy Chen on 10/5/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"

class CannonBall : public Actor
{
    DECL_ACTOR(CannonBall, Actor);
public:
    CannonBall(Game& game);
    ~CannonBall();
    void BeginPlay() override;
    void OnDieTimer();
private:
    MeshComponentPtr mMeshComponent;
    MoveComponentPtr mMoveComponent;
    SphereCollisionPtr mSphereCollision;
};

DECL_PTR(CannonBall);