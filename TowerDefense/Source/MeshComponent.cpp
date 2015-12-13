//  MeshComponent.cpp
//
//  Created by Jimmy Chen on 9/21/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//
#include "MeshComponent.h"
#include "Actor.h"
#include "Renderer.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner) : DrawComponent(owner)
{
    mIndex = 0;
}

void MeshComponent::Draw(class Renderer& render)
{
    if ( mMesh != nullptr)
    {
        render.DrawBasicMesh(mMesh->GetVertexArray(), mMesh->GetTexture(mIndex), mOwner.GetWorldTransform());
    }
}
