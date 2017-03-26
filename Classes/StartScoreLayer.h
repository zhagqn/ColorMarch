//
//  StartScoreLayer.h
//  ColorMarch
//
//  Created by zhagqn on 11/12/14.
//
//

#ifndef __ColorMarch__StartScoreLayer__
#define __ColorMarch__StartScoreLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class StartScoreLayer : public Layer
{
private:
    Sprite* last;
    Sprite* best;
    Size visibleSize;
    
public:
    CREATE_FUNC(StartScoreLayer);
    virtual void onEnter();
  
    void removingPrepare();
};

#endif /* defined(__ColorMarch__StartScoreLayer__) */
