//  Sound.cpp
//
//  Created by Jimmy Chen on 9/17/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Sound.h"
#include <fstream>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>

Sound::Sound()
{
    mData = nullptr;
}

Sound::~Sound()
{
    if(mData != nullptr)
        Mix_FreeChunk(mData);
}

bool Sound::Load(const char* fileName, class AssetCache* cache)
{
    mData = Mix_LoadWAV(fileName);
    if(mData == nullptr)
    {
        SDL_Log("Failed to load file");
        return false;
    }
    else
    {
        return true;
    }
}