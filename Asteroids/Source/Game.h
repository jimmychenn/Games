// Game.h
// Contains the core game functionality
// such as the game loop

#pragma once
#include "Renderer.h"
#include "FrameTimer.h"
#include "World.h"
#include "AssetCache.h"
#include "PhysWorld.h"
#include "Ship.h"
#include "Laser.h"
#include "InputManager.h"
#include "GameTimers.h"

class Game
{
public:
	Game();
	~Game();
	bool Init();
	void RunLoop();
	void Quit();

	Renderer& GetRenderer() { return mRenderer; }
	World& GetWorld() { return mWorld; }
	AssetCache& GetAssetCache() { return mAssetCache; }
	PhysWorld& GetPhysWorld() { return mPhysWorld; }
    InputManager& GetInput() { return mInput; }
    GameTimerManager& GetGameTimers() { return mGameTimer;}
    void AddInputMappings();
    
private:
	void StartGame();
	
	void ProcessInput();
	void HandleKeyPressed(int key);
	void HandleKeyReleased(int key);

	void Tick();
	void GenerateOutput();

	Renderer mRenderer;
    World mWorld;
	AssetCache mAssetCache;
	PhysWorld mPhysWorld;
    InputManager mInput;
    GameTimerManager mGameTimer;

    ShipPtr mShip;
    FrameTimer mTimer;    
    
	bool mShouldQuit;
};
