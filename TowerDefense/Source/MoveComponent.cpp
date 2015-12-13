#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mAngularSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mAngularAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
    if(!Math::IsZero(mAngularAxis))
    {
        // Update direction
        float NewRotation = mOwner.GetRotation() + mAngularSpeed * mAngularAxis * deltaTime;
        
        mOwner.SetRotation(NewRotation);
    }
    
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

void MoveComponent::AddToAngularAxis(float delta)
{
	mAngularAxis += delta;
	mAngularAxis = Math::Clamp(mAngularAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetAngularAxis(float axis)
{
	mAngularAxis = Math::Clamp(axis, -1.0f, 1.0f);
}
