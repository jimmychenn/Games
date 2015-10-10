// Laser.h
// Laser actor

#pragma once
#include "Actor.h"
#include "AudioComponent.h"

class Laser : public Actor
{
    DECL_ACTOR(Laser, Actor);
public:
    Laser(Game& game);
    void BeginPlay() override;
    void BeginTouch(Actor& other) override;
    
    void OnDieTimer();
private:
    SoundPtr mAsteroidDieSound;
    AudioComponentPtr mAudio;
};

DECL_PTR(Laser);
