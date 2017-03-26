//
//  GameScene.h
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#ifndef __ColorMarch__GameScene__
#define __ColorMarch__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "BGLayer.h"
#include "PauseLayer.h"
USING_NS_CC;

class Game : public Layer
{
private:
    bool isFirst;
    int score;
    int recordBreaking;
    BGLayer* bgLayer;
    PauseLayer* pauseLayer;
    
public:
    CREATE_FUNC(Game);
    
    static Scene* createScene();
    
    void onEnter();
    
    void onExit();
    
    void checkTouch(int idx);
    
    void updateScore();
    
    void gameOverPrepare();
    
    void gameOver(float dt);
    
    void addCover(float dt);
};

#endif /* defined(__ColorMarch__GameScene__) */
