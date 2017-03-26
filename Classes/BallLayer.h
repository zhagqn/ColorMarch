//
//  BallLayer.h
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#ifndef __ColorMarch__BallLayer__
#define __ColorMarch__BallLayer__

#include <stdio.h>
#include <cocos2d.h>
#include "GameScene.h"

USING_NS_CC;

class BallLayer : public Layer
{
private:
    Game* _gameScene;
    Size visibleSize;
    float race;
    float step;
    bool isOver;
    
public:
    CREATE_FUNC(BallLayer);
    
    BallLayer();
    ~BallLayer();
    
    virtual bool init();
    
    virtual void onEnter();
    void onExit();
    
    void addBall(float dt);
    
    int checkTouch(int idx);
    
    void updateRace();
    
    void gameOver();
    
    void removing(Action* action);
};

#endif /* defined(__ColorMarch__BallLayer__) */
