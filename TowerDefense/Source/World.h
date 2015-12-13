// World.h
// All actors in the game world should either
// directly or indirectly (by parent) be
// controlled by World

#pragma once
#include <memory>
#include <unordered_set>
#include "Actor.h"
#include "Enemy.h"

class World
{
public:
	World();
	~World();

	void AddActor(ActorPtr actor);

	void Tick(float deltaTime);
	
	void RemoveAllActors();
    
    void AddEnemy(Enemy* enemy);
    
    void RemoveEnemy(Enemy* enemy);
    
    std::vector<Enemy*> GetEnemiesInRange(Vector3 pos, float r);
    
    Enemy* GetClosestEnemy(Vector3 pos, float r);
private:
	std::unordered_set<ActorPtr> mActors;
    std::unordered_set<Enemy*> mEnemies;
};
