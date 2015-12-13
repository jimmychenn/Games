//  InputComponent.h
//
//  Created by Jimmy Chen on 9/21/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "MoveComponent.h"
#include <string>

class InputComponent : public MoveComponent
{
    DECL_COMPONENT(InputComponent, MoveComponent);
public:
    InputComponent(Actor& owner);
    void BindLinearAxis(const std::string& name);
    void BindYawAxis(const std::string& name);
    void OnLinearAxis(float value);
    void OnYawAxis(float value);
    void BindPitchAxis(const std::string& name);
    void OnPitchAxis(float value);
};
DECL_PTR(InputComponent);