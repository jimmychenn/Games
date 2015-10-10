#include "Laser.h"
#include "Game.h"
#include "SphereCollision.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

IMPL_ACTOR(Laser, Actor);

Laser::Laser(Game& game)
:Actor(game)
{
    auto sprite = SpriteComponent::Create(*this);
    auto tex = game.GetAssetCache().Load<Texture>("Textures/Laser.png");
    sprite->SetTexture(tex);
    
    auto move = MoveComponent::Create(*this, Component::PreTick);
    move->SetLinearSpeed(600.0f);
    move->SetLinearAxis(1.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromTexture(tex);
    coll->SetScale(0.9f);
    
    mAudio = AudioComponent::Create(*this);
    mAsteroidDieSound = game.GetAssetCache().Load<Sound>("Sounds/AsteroidDie.wav");
}

void Laser::BeginPlay()
{
    Super::BeginPlay();
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &Laser::OnDieTimer, 1.0f);
}

void Laser::BeginTouch(Actor& other)
{
    Super::BeginTouch(other);
    
    if (IsAlive() && IsA<Asteroid>(other))
    {
        mAudio->PlaySound(mAsteroidDieSound);
        // Kill myself
        SetIsAlive(false);
        // Kill the asteroid and spawn 4 smaller ones
        other.SetIsAlive(false);
        if (other.GetScale() > 0.5f)
        {
            for (int i = 0; i < 4; i++)
            {
                auto astr = Asteroid::Spawn(mGame);
                astr->SetScale(0.25f);
                astr->SetPosition(other.GetPosition());
            }
        }
    }
}

void Laser::OnDieTimer()
{
    SetIsAlive(false);
}
