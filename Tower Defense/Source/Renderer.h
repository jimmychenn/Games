// Render.h
// Tracks all the active draw components and renders
// the scene

#pragma once
#include <SDL/SDL.h>
#include <unordered_set>
#include "DrawComponent.h"
#include <GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

class Renderer
{
public:
	Renderer(class Game& game);
	~Renderer();

	bool Init(int width, int height);

	void RenderFrame();

	void AddComponent(DrawComponentPtr component);
	void RemoveComponent(DrawComponentPtr component);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void DrawSprite(TexturePtr texture, const Matrix4& worldTransform);
	void DrawVertexArray(VertexArrayPtr vertArray);
    
    void DrawBasicMesh(VertexArrayPtr vertArray, TexturePtr texture, const Matrix4& worldTransform);
private:
	void Clear();
	void DrawComponents();
	void Present();

	bool InitFrameBuffer();
	bool InitShaders();
	bool InitSpriteVerts();

    //3D Components
	std::unordered_set<DrawComponentPtr> mDrawComponents;
    //2D Components
    std::unordered_set<DrawComponentPtr> mComponents2D;

    Matrix4 mViewProj;
    ShaderPtr mBasicMeshShader;

    
    // View-projection matrix
	Matrix4 mSpriteViewProj;

	SDL_GLContext mContext;

	SDL_Window* mWindow;

	ShaderPtr mSpriteShader;
	VertexArrayPtr mSpriteVerts;

	class Game& mGame;

	int mWidth;
	int mHeight;
};
