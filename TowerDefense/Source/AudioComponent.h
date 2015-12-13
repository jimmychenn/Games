//  AudioComponent.h
//
//  Created by Jimmy Chen on 9/20/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Component.h"
#include "Sound.h"

class SoundCue
{
public:
    SoundCue() { mChannel = -1; };
    SoundCue(int ChannelNum) { mChannel = ChannelNum; };
    void Pause();
    void Resume();
    void Stop();
    bool Playing();
    bool Paused();
    
private:
    int mChannel;
};

class AudioComponent : public Component
{
    DECL_COMPONENT(AudioComponent, Component);
public:
    AudioComponent(Actor& owner);
    SoundCue PlaySound(SoundPtr sound, bool looping = false);
    
};
DECL_PTR(AudioComponent);