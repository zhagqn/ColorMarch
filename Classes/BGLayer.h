//
//  BGLayer.h
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#ifndef __ColorMarch__BGLayer__
#define __ColorMarch__BGLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class BGLayer : public LayerColor
{
private:
    Size visibleSize;
    Sprite* cover;
    Sprite* cover2;
public:
    static BGLayer* create(int flag);
    bool init(int flag);
//    static BGLayer* createBGLayer();
    
    // for game scene
    void removing(Action* action);
    
    // for enter scene
    void appearing();
};


#endif /* defined(__ColorMarch__BGLayer__) */
