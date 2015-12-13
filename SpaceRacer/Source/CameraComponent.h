//  CameraComponent.h
//
//  Created by Jimmy Chen on 10/22/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Component.h"
#include "Math.h"
#include "MoveComponent.h"

class CameraComponent : public Component
{
    DECL_COMPONENT(CameraComponent,Component);
public:
    CameraComponent(Actor& owner);
    ~CameraComponent();
    void Tick(float deltaTime) override;
    void SnapToIdealCamera();
    void SnapToCenter();

    void SetMoveComp(MoveComponentPtr ptr){ mMoveComp = ptr; }
private:
    Vector3 IdealCameraPos();
    
    Vector3 mActualCameraPos;
    Vector3 mCameraForward;
    Vector3 mCameraLeft;
    Vector3 mCameraUp;
    Vector3 vCameraVelocity;
    
    Vector3 TargetPos;
    
    Matrix4 mFollowCamera;
    
    float minHFollow;
    float maxHFollow;
    
    MoveComponentPtr mMoveComp;
};

DECL_PTR(CameraComponent);