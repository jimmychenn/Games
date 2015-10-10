//  FrostTower.h
//
//  Created by Jimmy Chen on 10/4/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#pragma once

#include "Tower.h"
#include "AudioComponent.h"

class FrostTower : public Tower
{
    DECL_ACTOR(FrostTower, Tower)
public:
    FrostTower(Game& game);
    ~FrostTower();
    void Attack();
private:
    TowerPtr BaseTower;
    AudioComponentPtr mAudioComponentPtr;
    SoundPtr mFrostSound;
};

DECL_PTR(FrostTower);