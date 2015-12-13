// Ship.h
// Ship actor

#pragma once
#include "Actor.h"
#include "Texture.h"
#include "InputComponent.h"
#include "AudioComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "SphereCollision.h"

class Ship : public Actor
{
    DECL_ACTOR(Ship, Actor);
public:
    Ship(Game& game);
    
    void BeginPlay() override;
    void Tick(float deltaTime) override;
        
    void BeginTouch(Actor& other) override;
    
    void Recenter();
    void Die();
private:
    // Need pointer to my sprite component to change texture
    InputComponentPtr mInput;
    AudioComponentPtr mAudio;
    MeshComponentPtr mMesh;
    CameraComponentPtr mCamera;
    SphereCollisionPtr mSphere;
    
    SoundPtr mEngineSound;
    SoundPtr mDieSound;
    
    SoundCue mEngineCue;
};

DECL_PTR(Ship);
