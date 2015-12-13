//  CameraComponent.cpp
//
//  Created by Jimmy Chen on 10/22/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "CameraComponent.h"
#include "Actor.h"
#include "Ship.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(CameraComponent, Component);

CameraComponent::CameraComponent(Actor& owner) : Component(owner)
{
    minHFollow = 200.0f;
    maxHFollow = 250.0f;
}

CameraComponent::~CameraComponent()
{
    
}

void CameraComponent::Tick(float deltaTime)
{
    float fSpringConstant = 200.0f;
    float fDampConstant = 2.0f * Math::Sqrt(fSpringConstant);
    
    Vector3 vDisplacement = mActualCameraPos - IdealCameraPos();
    Vector3 vSpringAccel = (-fSpringConstant * vDisplacement) - (fDampConstant * vCameraVelocity);
    vCameraVelocity += vSpringAccel * deltaTime;
    mActualCameraPos += vCameraVelocity * deltaTime;
    
    
    mFollowCamera = Matrix4::CreateLookAt(mActualCameraPos, TargetPos, mCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(mFollowCamera);
}

void CameraComponent::SnapToIdealCamera()
{
    mFollowCamera = Matrix4::CreateLookAt(IdealCameraPos(), TargetPos, mCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(mFollowCamera);
}

void CameraComponent::SnapToCenter()
{
    mFollowCamera = Matrix4::CreateLookAt(IdealCameraPos(), TargetPos, mCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(mFollowCamera);
}

Vector3 CameraComponent::IdealCameraPos()
{
    Vector3 ShipPos = mOwner.GetPosition();
    Vector3 ShipForward = mOwner.GetWorldTransform().GetXAxis();
    Vector3 ShipUp = mOwner.GetWorldTransform().GetZAxis();
    ShipForward.Normalize(); ShipUp.Normalize();
    TargetPos = ShipPos + 150.0f * ShipForward;
    
    float hFollow = Math::Lerp(minHFollow, maxHFollow, mMoveComp->GetLinearAxis());
    
    Vector3 mCameraPos = ShipPos - hFollow * ShipForward + 100.0f * ShipUp;
    mCameraForward = TargetPos - mActualCameraPos;
    mCameraForward.Normalize();
    mCameraLeft = Cross(ShipUp,mCameraForward);
    mCameraLeft.Normalize();
    mCameraUp = Cross(mCameraForward,mCameraLeft);
    mCameraUp.Normalize();
    return mCameraPos;
}