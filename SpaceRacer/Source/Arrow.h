//  Arrow.h
//
//  Created by Jimmy Chen on 10/26/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"

class Arrow : public Actor
{
    DECL_ACTOR(Arrow, Actor);
public:
    Arrow(Game& game);
    ~Arrow();
    void BeginPlay() override;
    void Tick(float deltaTime) override;
    
    void UpdateWorldPos();
    
    void SetPlayer(ActorPtr player) { mPlayer = player; }
    ActorPtr GetPlayer() { return mPlayer;}
    void SetCheckpointPos(Vector3 pos) { mCheckpointPos = pos; }
    
private:
    ActorPtr mPlayer;
    Vector3 mCheckpointPos;
};

DECL_PTR(Arrow);