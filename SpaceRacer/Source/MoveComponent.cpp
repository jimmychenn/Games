#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mYawSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mYawAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
    Quaternion NewRotation = mOwner.GetRotation();
    
    if(!Math::IsZero(mYawAxis))
    {
        // Update direction
        float angle = mYawSpeed * mYawAxis * deltaTime;
        Quaternion YawIncrm = Quaternion(mOwner.GetWorldTransform().GetZAxis(), angle);
        
        NewRotation = Concatenate(NewRotation, YawIncrm);
    }
    
    if(!Math::IsZero(mPitchAxis))
    {
        // Update direction
        float angle = mPitchSpeed * mPitchAxis * deltaTime;
        Quaternion PitchIncrm = Quaternion(mOwner.GetWorldTransform().GetYAxis(), angle);
        
        NewRotation = Concatenate(NewRotation, PitchIncrm);
        
    }
    
    mOwner.SetRotation(NewRotation);

    
    if(!Math::IsZero(mLinearAxis))
    {
        // Update velocity based on current forward
        Vector3 NewVelocity = mOwner.GetForward() * mLinearSpeed * mLinearAxis;
        
        // Update position of owner based on velocity
        Vector3 NewPosition = mOwner.GetPosition() + NewVelocity * deltaTime;
        
        mOwner.SetPosition(NewPosition);
    }
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToYawAxis(float delta)
{
	mYawAxis += delta;
	mYawAxis = Math::Clamp(mYawAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToPitchAxis(float delta)
{
    mPitchAxis += delta;
    mPitchAxis = Math::Clamp(mPitchAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetYawAxis(float axis)
{
    mYawAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetPitchAxis(float axis)
{
    mPitchAxis = Math::Clamp(axis, -1.0f, 1.0f);
}
