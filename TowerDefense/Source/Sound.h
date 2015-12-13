//  Sound.h
//
//  Created by Jimmy Chen on 9/17/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Asset.h"

class Sound : public Asset
{
    DECL_ASSET(Sound, Asset);
public:
    Sound();
    ~Sound();
    bool Load(const char* fileName, class AssetCache* cache) override;
    struct Mix_Chunk* GetData() {return mData; } ;

private:
    struct Mix_Chunk* mData;
};
DECL_PTR(Sound);