// World.h
// All actors in the game world should either
// directly or indirectly (by parent) be
// controlled by World

#pragma once
#include <memory>
#include <vector>
#include "Actor.h"

class World
{
public:
	World();
	~World();

	void AddActor(ActorPtr actor);

	void Tick(float deltaTime);
	
	void RemoveAllActors();
private:
	std::vector<ActorPtr> mActors;
};
