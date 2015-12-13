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
    void UpdateTime(int timeuntil);
    void UpdateScore(int score);
    void GameOver();
    
private:
    int mScore;
    int mTime;
    
    ActorPtr ScoreText;
    ActorPtr GameOverText;
    ActorPtr TimeText;
    
    FontComponentPtr ScoreFont;
    FontComponentPtr GameOverFont;
    FontComponentPtr TimeRemainingFont;
    
    std::ostringstream stringparser;

};

DECL_PTR(HUD);