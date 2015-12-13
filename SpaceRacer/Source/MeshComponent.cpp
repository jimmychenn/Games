#include "MeshComponent.h"
#include "Actor.h"
#include "Renderer.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner)
:Super(owner)
{
    
}

void MeshComponent::Draw(class Renderer& render)
{
    if (mMesh)
    {
        render.DrawBasicMesh(mMesh->GetVertexArray(), mMesh->GetTexture(0),
                             mOwner.GetWorldTransform());
    }
}
