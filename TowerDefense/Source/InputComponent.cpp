//  InputComponent.cpp
//
//  Created by Jimmy Chen on 9/21/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"

IMPL_COMPONENT(InputComponent, MoveComponent);

InputComponent::InputComponent(Actor& owner) : MoveComponent(owner)
{
    
}

void InputComponent::OnLinearAxis(float value)
{
    SetLinearAxis(value);
}

void InputComponent::OnAngularAxis(float value)
{
    SetAngularAxis(value);
}


void InputComponent::BindLinearAxis(const std::string &name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::BindAngularAxis(const std::string &name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnAngularAxis);
}