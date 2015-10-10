#include "Asteroid.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "SphereCollision.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game)
:Actor(game)
{
    // Face in a random direction
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
    auto meshC = MeshComponent::Create(*this);
    meshC->SetMesh(mesh);
    
    auto move = MoveComponent::Create(*this, Component::PreTick);
    move->SetLinearSpeed(100.0f);
    move->SetLinearAxis(1.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mesh);
    coll->SetScale(0.9f);
}
