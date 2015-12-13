#include "SpriteComponent.h"
#include "Actor.h"
#include <SDL/SDL.h>
#include "Renderer.h"

IMPL_COMPONENT(SpriteComponent, DrawComponent);

SpriteComponent::SpriteComponent(Actor& owner)
	:DrawComponent(owner)
{

}

void SpriteComponent::Draw(Renderer& render)
{
    if(mTexture){
        Matrix4 ScaleMatrix = Matrix4::CreateScale( mTexture->GetWidth(), mTexture->GetHeight(), 1);
        Matrix4 QuadWorldTransform = ScaleMatrix * mOwner.GetWorldTransform();
        render.DrawSprite(mTexture, QuadWorldTransform);
    }
}

