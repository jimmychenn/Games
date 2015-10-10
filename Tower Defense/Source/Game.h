// Game.h
// Contains the core game functionality
// such as the game loop

#pragma once
#include "Renderer.h"
#include "FrameTimer.h"
#include "World.h"
#include "AssetCache.h"
#include "PhysWorld.h"
#include "InputManager.h"
#include "GameTimers.h"
#include "GameMode.h"
#include "NavWorld.h"
//#include "Spawner.h"

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
    GameModePtr& GetGameMode(){ return mGameMode; }
    NavWorld& GetNavWorld(){ return mNavWorld; }
    void AddInputMappings();
    
    void SetGameOver(){ mGameOver = true;}
    bool IsGameOver(){ return mGameOver;}
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
    GameModePtr mGameMode;
    NavWorld mNavWorld;
    
    FrameTimer mTimer;    
    
	bool mShouldQuit;
    bool mGameOver;
};
