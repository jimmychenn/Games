#include "Ship.h"
#include "Game.h"
#include "Laser.h"
#include "Asteroid.h"
#include "SphereCollision.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
:Actor(game)
{
    // 	mIdleTexture = mGame.GetAssetCache().
    // 		Load<Texture>("Textures/Spaceship.png");
    // 	mThrustTexture = mGame.GetAssetCache().
    // 		Load<Texture>("Textures/SpaceshipWithThrust.png");
    //
    // 	mSprite = SpriteComponent::Create(*this);
    // 	mSprite->SetTexture(mIdleTexture);
    
    mInput = InputComponent::Create(*this, Component::PreTick);
    mInput->SetLinearSpeed(400.0f);
    mInput->SetAngularSpeed(Math::TwoPi);
    
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/PlayerShip.itpmesh2");
    mMesh = MeshComponent::Create(*this);
    mMesh->SetMesh(mesh);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mesh);
    coll->SetScale(0.75f);
    
    mAudio = AudioComponent::Create(*this);
    mEngineSound = mGame.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav");
    mLaserSound = mGame.GetAssetCache().Load<Sound>("Sounds/Laser.wav");
    mDieSound = mGame.GetAssetCache().Load<Sound>("Sounds/ShipDie.wav");
    
    SetScale(0.5f);
}

void Ship::BeginPlay()
{
    Super::BeginPlay();
    
    // Setup our input component
    mInput->BindLinearAxis("Move");
    mInput->BindAngularAxis("Rotate");
    
    // Bind the fire button
    mGame.GetInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissile);
    
    // Start the loop sound
    mEngineCue = mAudio->PlaySound(mEngineSound, true);
    mEngineCue.Pause();
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    
    bool moving = !Math::IsZero(mInput->GetLinearAxis());
    if (!moving)
    {
        //mSprite->SetTexture(mIdleTexture);
        mEngineCue.Pause();
    }
    else
    {
        //mSprite->SetTexture(mThrustTexture);
        mEngineCue.Resume();
    }
}

void Ship::FireMissile()
{
    if (!IsPaused())
    {
        auto laser = Laser::Spawn(mGame);
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        mAudio->PlaySound(mLaserSound);
    }
}

void Ship::BeginTouch(Actor& other)
{
    if (!IsPaused() && IsA<Asteroid>(other))
    {
        SetIsPaused(true);
        mMesh->SetIsVisible(false);
        TimerHandle handle;
        mGame.GetGameTimers().SetTimer(handle, this, &Ship::Respawn, 1.0f);
        mEngineCue.Pause();
        mAudio->PlaySound(mDieSound);
    }
}

void Ship::Respawn()
{
    // Set position/rotation back to center and up
    SetPosition(Vector3::Zero);
    SetRotation(Math::PiOver2);
    // Unpause
    mMesh->SetIsVisible(true);
    SetIsPaused(false);
}
