//  Enemy.h
//
//  Created by Jimmy Chen on 10/3/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"
#include "SphereCollision.h"
#include "MoveComponent.h"
#include "MeshComponent.h"
#include "AudioComponent.h"
#include "Sound.h"
#include "NavComponent.h"

class Enemy : public Actor
{
    DECL_ACTOR(Enemy, Actor);
public:
    Enemy(Game& game);
    ~Enemy();
    void BeginTouch(Actor& other) override;
    void BeginPlay() override;
    void EndPlay() override;
    void Slow();
    void Unslow();
private:
    int health;
    MeshComponentPtr mMeshComponentPtr;
    SphereCollisionPtr mSphereCollisionPtr;
    NavComponentPtr mNavComponentPtr;
    AudioComponentPtr mAudioComponentPtr;
    SoundPtr mDieSound;
};

DECL_PTR(Enemy);