#pragma once
#include "DrawComponent.h"
#include "Mesh.h"

class MeshComponent : public DrawComponent
{
    DECL_COMPONENT(MeshComponent, DrawComponent);
public:
    MeshComponent(Actor& owner);
    
    void Draw(class Renderer& render) override;
    
    void SetMesh(MeshPtr mesh) { mMesh = mesh; }
    MeshPtr GetMesh() { return mMesh; }
private:
    MeshPtr mMesh;
};

DECL_PTR(MeshComponent);
