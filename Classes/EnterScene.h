//
//  EnterScene.h
//  ColorMarch
//
//  Created by zhagqn on 11/3/14.
//
//

#ifndef __ColorMarch__EnterScene__
#define __ColorMarch__EnterScene__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;


class Enter : public Layer
{
private:
public:
    Enter();
    ~Enter();
    CREATE_FUNC(Enter);
    
    static Scene* createScene();
    virtual void onEnter();
    virtual void onExit();
    void startGamePrepare();
    
    void startGame(float dt);
};

#endif /* defined(__ColorMarch__EnterScene__) */
