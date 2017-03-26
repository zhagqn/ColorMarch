//
//  StartButtonLayer.h
//  ColorMarch
//
//  Created by zhagqn on 11/3/14.
//
//

#ifndef __ColorMarch__StartButtonLayer__
#define __ColorMarch__StartButtonLayer__

#include <stdio.h>
#include <cocos2d.h>
#include "EnterScene.h"
USING_NS_CC;

class StartButtonLayer : public Layer
{
private:
    Sprite* btnStart;
    Sprite* btnStart_sd;
    Sprite* btnRate;
    Sprite* btnRate_sd;
    Sprite* btnRank;
    Sprite* btnRank_sd;
    Size visibleSize;
    Enter* _gameScene;
    
public:
    StartButtonLayer();
    ~StartButtonLayer();
    
    CREATE_FUNC(StartButtonLayer);
    virtual bool init();
    virtual void onEnter();
    
    void enterGame();
    
    void removingPrepare();
//    void enterRate();
//    void enterRank();
};

#endif /* defined(__ColorMarch__StartButtonLayer__) */
