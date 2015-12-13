//  CannonTower.h
//
//  Created by Jimmy Chen on 10/4/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Tower.h"
#include "AudioComponent.h"
#include "Sound.h"

class CannonTower : public Tower
{
    DECL_ACTOR(CannonTower, Tower);
public:
    CannonTower(Game& game);
    ~CannonTower();
    void Attack();
private:
    TowerPtr BaseTower;
    AudioComponentPtr mAudioComponentPtr;
    SoundPtr mCannonSound;
};

DECL_PTR(CannonTower);