//
//  BGStarLayer.h
//  ColorMarch
//
//  Created by zhagqn on 12/20/14.
//
//

#ifndef __ColorMarch__BGStarLayer__
#define __ColorMarch__BGStarLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class BGStarLayer : public Layer
{
private:
    Vector<Sprite*>* stars;
    Size visibleSize;
    int mode;
    
public:
    static BGStarLayer* create(int i);
    bool init(int i);
    void onEnter();
    void onExit();
    
    void addStar(float dt);
    void random_move(float dt);
};

#endif /* defined(__ColorMarch__BGStarLayer__) */
