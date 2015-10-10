//  MeshComponent.h
//
//  Created by Jimmy Chen on 9/21/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "DrawComponent.h"
#include "Mesh.h"

class MeshComponent : public DrawComponent
{
    DECL_COMPONENT(MeshComponent, DrawComponent);
public:
    MeshComponent(Actor& owner);
    void Draw(class Renderer& render) override;
    
    MeshPtr& GetMesh(){ return mMesh;}
    void SetMesh(MeshPtr mesh) { mMesh = mesh; }
    void SetIndex(int index) {mIndex = index; }
    int GetIndex() {return mIndex; }
    
private:
    MeshPtr mMesh;
    int mIndex;

};

DECL_PTR(MeshComponent);