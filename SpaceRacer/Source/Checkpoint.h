//  Checkpoint.h
//
//  Created by Jimmy Chen on 10/26/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "SphereCollision.h"

class Checkpoint : public Actor
{
    DECL_ACTOR(Checkpoint, Actor);
public:
    Checkpoint(Game& game);
    ~Checkpoint();
private:
    
    SphereCollisionPtr mSphereCol;
    
};

DECL_PTR(Checkpoint);