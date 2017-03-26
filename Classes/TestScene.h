//
//  TestScene.h
//  ColorMarch
//
//  Created by zhagqn on 11/10/14.
//
//

#ifndef __ColorMarch__TestScene__
#define __ColorMarch__TestScene__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class Test : public Layer
{
public:
    CREATE_FUNC(Test);
    static Scene* createScene();
    
    virtual bool init();
};

#endif /* defined(__ColorMarch__TestScene__) */
