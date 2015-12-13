#include "World.h"
#include "Math.h"

World::World()
{

}

World::~World()
{

}

void World::AddActor(ActorPtr actor)
{
	mActors.emplace(actor);
}

void World::Tick(float deltaTime)
{
	// Tick a copy of the actor pointers, in case any actor adds more actors
	auto actors = mActors;
	for (auto& actor : actors)
	{
		actor->TickInternal(deltaTime);
	}

	// Remove any actors that are dead
	auto iter = mActors.begin();
	while (iter != mActors.end())
	{
		if (!(*iter)->IsAlive())
		{
			(*iter)->EndPlay();
			iter = mActors.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void World::RemoveAllActors()
{
    for (auto& actor : mActors)
    {
        actor->EndPlay();
    }
    mActors.clear();
}

void World::AddEnemy(Enemy* enemy)
{
    mEnemies.emplace(enemy);
}

void World::RemoveEnemy(Enemy* enemy)
{
    mEnemies.erase(enemy);
}

std::vector<Enemy*> World::GetEnemiesInRange(Vector3 pos, float r)
{
    float rsquared = powf(r, 2);
    std::vector<Enemy*> EnemyList;
    for( auto& enemy : mEnemies)
    {
        auto EnemyPos = enemy->GetPosition();
        Vector3 diff = EnemyPos - pos;
        float dist = Dot(diff, diff);
        if(dist < rsquared)
            EnemyList.push_back(enemy);
    }
    return EnemyList;
}

Enemy* World::GetClosestEnemy(Vector3 pos, float r)
{
    Enemy* ClosestEnemy = nullptr;
    float mindist = powf(r,2);
    for( auto& enemy : mEnemies)
    {
        auto EnemyPos = enemy->GetPosition();
        Vector3 diff = EnemyPos - pos;
        float dist = Dot(diff,diff);
        if ( dist < mindist)
        {
            ClosestEnemy = enemy;
            mindist = dist;
        }
    }
    
    return ClosestEnemy;
}