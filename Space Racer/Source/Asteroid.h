// Asteroid.h
// Asteroid actor

#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
    DECL_ACTOR(Asteroid, Actor);
public:
    Asteroid(Game& game);
};

DECL_PTR(Asteroid);
