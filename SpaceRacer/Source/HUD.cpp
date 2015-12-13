//  HUD.cpp
//
//  Created by Jimmy Chen on 10/7/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "HUD.h"
#include "Game.h"
#include "Font.h"
#include "Math.h"

IMPL_ACTOR(HUD,Actor);

HUD::HUD(Game& game) : Actor(game)
{
    mScore = 0;
    
    auto font = mGame.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");

    ScoreText = Actor::SpawnAttached(*this);
    ScoreFont = FontComponent::Create(*ScoreText);
    ScoreFont->SetFont(font);
    //Vector3 pos1 = mGame.GetRenderer().Unproject(Vector3(0.0f, 500.0f, 100.0f));
    Vector3 pos1(-100.0f, 250.0f, 00.0f);
    ScoreText->SetPosition(pos1);
    
    TimeText = Actor::SpawnAttached(*this);
    TimeRemainingFont = FontComponent::Create(*TimeText);
    TimeRemainingFont->SetFont(font);
    //Vector3 pos2 = mGame.GetRenderer().Unproject(Vector3(1000, 1000, 0));
    Vector3 pos2(-100.0f,300.0f,0.0f);
    TimeText->SetPosition(pos2);
    
    GameOverText = Actor::SpawnAttached(*this);
    GameOverFont = FontComponent::Create(*GameOverText);
    GameOverFont->SetFont(font);
    Vector3 pos3 = mGame.GetRenderer().Unproject(Vector3(0, 0, 0.0));
    GameOverText->SetPosition(pos3);
    
    ScoreText->AddComponent(ScoreFont);
    GameOverText->AddComponent(GameOverFont);
    TimeText->AddComponent(TimeRemainingFont);
}

HUD::~HUD()
{
    
}

void HUD::Tick(float deltaTime)
{

}

void HUD::UpdateTime(int timeuntil)
{
    mTime = timeuntil;
    stringparser << "Time: " << mTime;
    std::string time = stringparser.str();
    TimeRemainingFont->SetText(time, Color::Green, 52);
    stringparser.str("");
}


void HUD::UpdateScore(int score)
{
    mScore = score;
    stringparser << "Score: " << mScore;
    std::string scoreStr = stringparser.str();
    ScoreFont->SetText(scoreStr, Color::White, 52);
    stringparser.str("");

}


void HUD::GameOver()
{
    GameOverFont->SetText("Game Over", Color::Blue, 72);
}
