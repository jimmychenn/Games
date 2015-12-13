//  AudioComponent.cpp
//
//  Created by Jimmy Chen on 9/20/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "AudioComponent.h"
#include "Actor.h"
#include <SDL/SDL_mixer.h>
IMPL_COMPONENT(AudioComponent,Component);

void SoundCue::Pause()
{
    if(mChannel != -1)
        Mix_Pause(mChannel);
}

void SoundCue::Resume()
{
    if(mChannel != -1)
        Mix_Resume(mChannel);
}

void SoundCue::Stop()
{
    if(mChannel != -1)
        Mix_HaltChannel(mChannel);
}

bool SoundCue::Playing()
{
    if(mChannel != -1)
        return Mix_Playing(mChannel);
    else
        return false;
}

bool SoundCue::Paused()
{
    if(mChannel != -1)
        return Mix_Paused(mChannel);
    else
        return false;
}

AudioComponent::AudioComponent(Actor& owner) : Component(owner)
{
    
}

SoundCue AudioComponent::PlaySound( SoundPtr sound, bool looping)
{
    int Channelnum;
    if(looping){
        Channelnum = Mix_PlayChannel(-1, sound->GetData(), -1);
    }
    else{
        Channelnum = Mix_PlayChannel(-1, sound->GetData(), 0);
    }
    return SoundCue(Channelnum);
}
