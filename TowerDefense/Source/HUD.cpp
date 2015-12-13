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
    auto font = mGame.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");
    
    
    HealthText = Actor::SpawnAttached(*this);
    HealthFont = FontComponent::Create(*HealthText);
    Vector3 pos1(-400.0f, 300.0f, 0.0f);
    HealthText->SetPosition(pos1);
    HealthFont->SetFont(font);
    
    GoldText = Actor::SpawnAttached(*this);
    GoldFont = FontComponent::Create(*GoldText);
    GoldFont->SetFont(font);
    Vector3 pos2(-400.0f, 275.0f, 0.0f);
    GoldText->SetPosition(pos2);
    
    NotEnoughGoldText = Actor::SpawnAttached(*this);
    NotEnoughGoldFont = FontComponent::Create(*NotEnoughGoldText);
    NotEnoughGoldFont->SetFont(font);
    Vector3 pos3(-200.0f, 0.0f, 0.0f);
    NotEnoughGoldText->SetPosition(pos3);
    
    PathIsBlockedText = Actor::SpawnAttached(*this);
    PathIsBlockedFont = FontComponent::Create(*PathIsBlockedText);
    PathIsBlockedFont->SetFont(font);
    Vector3 pos4(-200.0f, 40.0f, 0.0f);
    PathIsBlockedText->SetPosition(pos4);

    GameOverText = Actor::SpawnAttached(*this);
    GameOverFont = FontComponent::Create(*GameOverText);
    GameOverFont->SetFont(font);
    Vector3 pos5(-180.0f, 40.0f, 0.0f);
    GameOverText->SetPosition(pos5);
    
    TimeText = Actor::SpawnAttached(*this);
    TimeUntilNextWaveFont = FontComponent::Create(*TimeText);
    TimeUntilNextWaveFont->SetFont(font);
    Vector3 pos6(0.0f, 275.0f, 0.0f);
    TimeText->SetPosition(pos6);
    
    
    HealthText->AddComponent(HealthFont);
    GoldText->AddComponent(GoldFont);
    NotEnoughGoldText->AddComponent(NotEnoughGoldFont);
    PathIsBlockedText->AddComponent(PathIsBlockedFont);
    GameOverText->AddComponent(GameOverFont);
    TimeText->AddComponent(TimeUntilNextWaveFont);
}

HUD::~HUD()
{
    
}

void HUD::Tick(float deltaTime)
{
    if(mHealth != mGame.GetGameMode()->GetHealth())
    {
        mHealth = mGame.GetGameMode()->GetHealth();
        stringparser << "Base Health: " << mHealth;
        std::string healthstr = stringparser.str();
        HealthFont->SetText(healthstr, Color::White);
        stringparser.str("");
    }
    if(mMoney != mGame.GetGameMode()->GetMoney())
    {
        mMoney = mGame.GetGameMode()->GetMoney();
        stringparser << "Money: $" << mMoney;
        std::string moneystr = stringparser.str();
        GoldFont->SetText(moneystr, Color::Green);
        stringparser.str("");
    }
    
}

void HUD::UpdateTime(int timeuntilnextwave /*, int numberofenemies*/)
{
    stringparser << "Time Until Next Wave: " << timeuntilnextwave << "s";
    std::string timestring = stringparser.str();
    stringparser.str("");
    TimeUntilNextWaveFont->SetText(timestring, Color::LightBlue);
}

void HUD::PathIsBlocked()
{
    PathIsBlockedFont->SetText("You cannot build there", Color::Red, 48);
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &HUD::SetTextInvisible, 3.0f);
}

void HUD::GameOver()
{
    GameOverFont->SetText("Game Over", Color::Blue, 72);
}

void HUD::NotEnoughMoney()
{
    NotEnoughGoldFont->SetText("You must acquire more minerals", Color::Red, 48);
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &HUD::SetTextInvisible, 3.0f);
}

void HUD::SetTextInvisible()
{
    PathIsBlockedFont->SetText("", Color::White);
    NotEnoughGoldFont->SetText("", Color::White);
}