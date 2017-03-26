//
//  YoyoLayer.h
//  ColorMarch
//
//  Created by zhagqn on 11/9/14.
//
//

#ifndef __ColorMarch__YoyoLayer__
#define __ColorMarch__YoyoLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class YoyoLayer : public Layer
{
private:
    Size visibleSize;
    Sprite* title;
    Sprite* yoyo_r;
    Sprite* yoyo_r_sd;
    Sprite* yoyo_b;
    Sprite* yoyo_b_sd;
    Sprite* yoyo_y;
    Sprite* yoyo_y_sd;
    Vec2 yoyo_loc[3];
    Vector<Sprite*>* yoyos;
    Vector<Sprite*>* yoyos_sd;
    
public:
    CREATE_FUNC(YoyoLayer);
    virtual void onEnter();
    void random_move(float dt);
    
    void removingPrepare();
    void removing(float dt);
};

#endif /* defined(__ColorMarch__YoyoLayer__) */
