#include "Ship.h"
#include "Game.h"
#include "Asteroid.h"
#include "SphereCollision.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
:Actor(game)
{
    mInput = InputComponent::Create(*this, Component::PreTick);
    mInput->SetLinearSpeed(400.0f);
    mInput->SetYawSpeed(-Math::Pi);
    mInput->SetPitchSpeed(-Math::Pi);
    
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/PlayerShip.itpmesh2");
    mMesh = MeshComponent::Create(*this);
    mMesh->SetMesh(mesh);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mesh);
    coll->SetScale(0.75f);
    
    mAudio = AudioComponent::Create(*this);
    mEngineSound = mGame.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav");
    mDieSound = mGame.GetAssetCache().Load<Sound>("Sounds/ShipDie.wav");
    
    mCamera = CameraComponent::Create(*this);
    mCamera->SetMoveComp(mInput);
    mCamera->SnapToIdealCamera();
    
    mSphere = SphereCollision::Create(*this);
    //mSphere->SetScale(0.9f);
    
    SetScale(0.5f);
}

void Ship::BeginPlay()
{
    Super::BeginPlay();
    
    // Setup our input component
    mInput->BindLinearAxis("Move");
    mInput->BindYawAxis("Yaw");
    mInput->BindPitchAxis("Pitch");
    mGame.GetInput().BindAction("Recenter", IE_Pressed, this, &Ship::Recenter);
    
    // Start the loop sound
    mEngineCue = mAudio->PlaySound(mEngineSound, true);
    mEngineCue.Pause();
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    
    bool moving = !Math::IsZero(mInput->GetLinearAxis());
    if (!moving )
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

void Ship::BeginTouch(Actor& other)
{
    if(IsAlive() && IsA<Checkpoint>(other))
    {
        other.SetIsAlive(false);
        mGame.GetGameMode()->CollectCheckpoint();
    }
}

void Ship::Recenter()
{
    Quaternion center;
    SetRotation(center);
    mCamera->SnapToCenter();
}

void Ship::Die()
{
    mEngineCue.Pause();
}