//  HUD.h
//
//  Created by Jimmy Chen on 10/7/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "FontComponent.h"
#include <sstream>

class HUD : public Actor
{
    DECL_ACTOR(HUD,Actor);
public:
    HUD(Game& game);
    ~HUD();
    void Tick(float deltaTime) override;
    void SetHealth(int health){ mHealth = health; }
    void SetMoney(int money){ mMoney = money; }
    void NotEnoughMoney();
    void UpdateTime(int timeuntilnextwave /*, int numberofenemies*/);
    void PathIsBlocked();
    void GameOver();
    void SetTextInvisible();
    
private:
    ActorPtr HealthText;
    ActorPtr GoldText;
    ActorPtr NotEnoughGoldText;
    ActorPtr PathIsBlockedText;
    ActorPtr GameOverText;
    ActorPtr TimeText;
    
    FontComponentPtr HealthFont;
    FontComponentPtr GoldFont;
    FontComponentPtr NotEnoughGoldFont;
    FontComponentPtr PathIsBlockedFont;
    FontComponentPtr GameOverFont;
    FontComponentPtr TimeUntilNextWaveFont;
    
    int mHealth;
    int mMoney;
    
    std::ostringstream stringparser;

};

DECL_PTR(HUD);