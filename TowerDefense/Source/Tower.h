//  Tower.h
//
//  Created by Jimmy Chen on 10/4/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "Sound.h"

class Tower : public Actor
{
    DECL_ACTOR(Tower, Actor);
public:
    Tower(Game& game);
    ~Tower();
private:
    AudioComponentPtr mAudioComponentPtr;
    SoundPtr mBuildingSound;
};

DECL_PTR(Tower);