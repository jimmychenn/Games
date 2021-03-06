// Texture.h
// Texture asset

#pragma once
#include "Asset.h"
#include <GL/glew.h>

class Texture : public Asset
{
	DECL_ASSET(Texture, Asset);
public:
	Texture();
	virtual ~Texture();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void SetActive();

	// Helper to create a texture from an SDL surface --
	// This should only really be used by FontComponent
	// Note: It's assumed the surface is BGRA, since that's what
	// SDL_ttf creates
	static std::shared_ptr<Texture> CreateFromSurface(struct SDL_Surface* surface);
protected:
	bool Load(const char* fileName, class AssetCache* cache) override;
private:
	GLuint mTextureID;
	int mWidth;
	int mHeight;
};

DECL_PTR(Texture);
