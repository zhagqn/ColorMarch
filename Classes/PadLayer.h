//
//  PadLayer.h
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#ifndef __ColorMarch__PadLayer__
#define __ColorMarch__PadLayer__

#include <stdio.h>
#include <cocos2d.h>
//#include "GameScene.h"

USING_NS_CC;

class PadLayer : public Layer
{
private:
//    Game* _gameScene;
    Size visibleSize;
    bool enableTouch;
    
public:
    CREATE_FUNC(PadLayer);
    
    PadLayer();
    
    ~PadLayer();
    
    bool init();
    
    void onEnter();
    
//    void touchPad(int idx);
    
    void removing(Action* action);
};

#endif /* defined(__ColorMarch__PadLayer__) */
