// Ship.h
// Ship actor

#pragma once
#include "Actor.h"
#include "Texture.h"
#include "InputComponent.h"
#include "AudioComponent.h"
#include "MeshComponent.h"

class Ship : public Actor
{
    DECL_ACTOR(Ship, Actor);
public:
    Ship(Game& game);
    
    void BeginPlay() override;
    void Tick(float deltaTime) override;
    
    void FireMissile();
    
    void BeginTouch(Actor& other) override;
    void Respawn();
private:
    // Need pointer to my sprite component to change texture
    InputComponentPtr mInput;
    AudioComponentPtr mAudio;
    MeshComponentPtr mMesh;
    
    TexturePtr mIdleTexture;
    TexturePtr mThrustTexture;
    
    SoundPtr mEngineSound;
    SoundPtr mLaserSound;
    SoundPtr mDieSound;
    
    SoundCue mEngineCue;
};

DECL_PTR(Ship);
