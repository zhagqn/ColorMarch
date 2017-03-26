//
//  PauseLayer.h
//  ColorMarch
//
//  Created by zhagqn on 12/24/14.
//
//

#ifndef __ColorMarch__PauseLayer__
#define __ColorMarch__PauseLayer__

#include <stdio.h>
#include <cocos2d.h>
USING_NS_CC;

class PauseLayer : public Layer
{
private:
    Size visibleSize;
    Sprite* btn_pause;
    LayerColor* mask;
    Sprite* btn_home;
    Sprite* btn_reload;
    Sprite* btn_resume;
    Sprite* btn_home_sd;
    Sprite* btn_reload_sd;
    Sprite* btn_resume_sd;
    bool menu_avaliable;
    EventListenerTouchOneByOne* mask_listener;
 
public:
    CREATE_FUNC(PauseLayer);
    bool init();
    void onEnter();
    void showMenu();
    void hideMenu();
    void onExit();
};

#endif /* defined(__ColorMarch__PauseLayer__) */
