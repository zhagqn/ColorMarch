//
//  PauseLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 12/24/14.
//
//

#include "PauseLayer.h"

bool PauseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    btn_pause = Sprite::createWithSpriteFrameName("btn_pause.png");
    auto size_pause = btn_pause->getContentSize();
    btn_pause->setPosition(visibleSize.width - size_pause.width - 10,
                           visibleSize.height - size_pause.height - 10);
    addChild(btn_pause);
    
    btn_home = Sprite::createWithSpriteFrameName("btn_home.png");
    btn_home->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btn_home->setPosition(visibleSize.width/6 + 40, visibleSize.height/2 - 50);
    addChild(btn_home, 2);
    
    btn_home_sd = Sprite::createWithSpriteFrameName("btn_sd.png");
    btn_home_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btn_home_sd->setPosition(visibleSize.width/6 + 40 + 4, visibleSize.height/2 - 50 - 6);
    addChild(btn_home_sd, 1);
    
    btn_reload = Sprite::createWithSpriteFrameName("btn_reload.png");
    btn_reload->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btn_reload->setPosition(visibleSize.width/2, visibleSize.height/2 - 50);
    addChild(btn_reload, 2);
    
    btn_reload_sd = Sprite::createWithSpriteFrameName("btn_sd.png");
    btn_reload_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btn_reload_sd->setPosition(visibleSize.width/2 + 4, visibleSize.height/2 - 50 - 6);
    addChild(btn_reload_sd, 1);
    
    btn_resume = Sprite::createWithSpriteFrameName("btn_resume.png");
    btn_resume->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btn_resume->setPosition(visibleSize.width*5/6 - 40, visibleSize.height/2 - 50);
    addChild(btn_resume, 2);
    
    btn_resume_sd = Sprite::createWithSpriteFrameName("btn_sd.png");
    btn_resume_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btn_resume_sd->setPosition(visibleSize.width*5/6 - 40 + 4, visibleSize.height/2 - 50 - 6);
    addChild(btn_resume_sd, 1);
    
    mask = LayerColor::create(Color4B(0, 0, 0, 126));
    addChild(mask, 0);
    mask_listener = EventListenerTouchOneByOne::create();
    mask_listener->onTouchBegan = [](Touch* t, Event* e) {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mask_listener, mask);
    mask_listener->setSwallowTouches(false);

    menu_avaliable = false;
    hideMenu();

    return true;
}


void PauseLayer::onEnter()
{
    Layer::onEnter();
    
    EventListenerTouchOneByOne* homeListener;
    EventListenerTouchOneByOne* reloadListener;
    EventListenerTouchOneByOne* resumeListener;
    
    // pause button listener
    auto pauseListener = EventListenerTouchOneByOne::create();
    pauseListener->onTouchBegan = [](Touch* t, Event* e)
    {
        Sprite* btn = (Sprite*)e->getCurrentTarget();
        if (btn->getBoundingBox().containsPoint(t->getLocation()))
        {
            btn->setScale(1.2);
        }
        return true;
    };
    pauseListener->onTouchEnded = [this](Touch* t, Event* e)
    {
        Sprite* btn = (Sprite*)e->getCurrentTarget();
        if (btn->getBoundingBox().containsPoint(t->getLocation()))
        {
            btn->setScale(1/1.2);
            EventCustom e("pause game");
            _eventDispatcher->dispatchEvent(&e);
            showMenu();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pauseListener, btn_pause);
    
    // home button listener
    homeListener = EventListenerTouchOneByOne::create();
    homeListener->onTouchBegan = [this](Touch* t, Event* e)
    {
        if(menu_avaliable)
        {
            Sprite* btn = (Sprite*)e->getCurrentTarget();
            if (btn->getBoundingBox().containsPoint(t->getLocation()))
            {
                btn->setPosition(btn->getPosition() + Vec2(2, -3));
                btn_home_sd->setPosition(btn_home_sd->getPosition() + Vec2(-2, 3));
            }
        }
        return true;
    };
    homeListener->onTouchEnded = [this](Touch* t, Event* e)
    {
        if(menu_avaliable)
        {
            Sprite* btn = (Sprite*)e->getCurrentTarget();
            if (btn->getBoundingBox().containsPoint(t->getStartLocation()))
            {
                btn->setPosition(btn->getPosition() + Vec2(-2, 3));
                btn_home_sd->setPosition(btn_home_sd->getPosition() + Vec2(2, -3));
            
                EventCustom e2("resume game");
                _eventDispatcher->dispatchEvent(&e2);
                EventCustom e("home game");
                _eventDispatcher->dispatchEvent(&e);
                hideMenu();
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(homeListener, btn_home);
    
    // reload button listener
    reloadListener = EventListenerTouchOneByOne::create();
    reloadListener->onTouchBegan = [this](Touch* t, Event* e)
    {
        if(menu_avaliable)
        {
            Sprite* btn = (Sprite*)e->getCurrentTarget();
            if (btn->getBoundingBox().containsPoint(t->getLocation()))
            {
                btn->setPosition(btn->getPosition() + Vec2(2, -3));
                btn_reload_sd->setPosition(btn_reload_sd->getPosition() + Vec2(-2, 3));
            }
        }
        return true;
    };
    reloadListener->onTouchEnded = [this](Touch* t, Event* e)
    {
        if(menu_avaliable)
        {
            Sprite* btn = (Sprite*)e->getCurrentTarget();
            if (btn->getBoundingBox().containsPoint(t->getStartLocation()))
            {
                btn->setPosition(btn->getPosition() + Vec2(-2, 3));
                btn_reload_sd->setPosition(btn_reload_sd->getPosition() + Vec2(2, -3));
                
                EventCustom e2("resume game");
                _eventDispatcher->dispatchEvent(&e2);
                EventCustom e("reload game");
                _eventDispatcher->dispatchEvent(&e);
                hideMenu();
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(reloadListener, btn_reload);
    
    // resume button listener
    resumeListener = EventListenerTouchOneByOne::create();
    resumeListener->onTouchBegan = [this](Touch* t, Event* e)
    {
        if(menu_avaliable)
        {
            Sprite* btn = (Sprite*)e->getCurrentTarget();
            if (btn->getBoundingBox().containsPoint(t->getLocation())) {
                btn->setPosition(btn->getPosition() + Vec2(2, -3));
                btn_resume_sd->setPosition(btn_resume_sd->getPosition() + Vec2(-2, 3));
            }
        }
        return true;
    };
    resumeListener->onTouchEnded = [this](Touch* t, Event* e)
    {
        if(menu_avaliable)
        {
            Sprite* btn = (Sprite*)e->getCurrentTarget();
            if (btn->getBoundingBox().containsPoint(t->getStartLocation())) {
                btn->setPosition(btn->getPosition() + Vec2(-2, 3));
                btn_resume_sd->setPosition(btn_resume_sd->getPosition() + Vec2(2, -3));
            
                EventCustom e("resume game");
                _eventDispatcher->dispatchEvent(&e);
                hideMenu();
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(resumeListener, btn_resume);
    

}

void PauseLayer::showMenu()
{
    btn_home->setVisible(true);
    btn_reload->setVisible(true);
    btn_resume->setVisible(true);
    btn_home_sd->setVisible(true);
    btn_reload_sd->setVisible(true);
    btn_resume_sd->setVisible(true);
    mask->setVisible(true);
    mask_listener->setSwallowTouches(true);
    menu_avaliable = true;
    
}

void PauseLayer::hideMenu()
{
    btn_home->setVisible(false);
    btn_reload->setVisible(false);
    btn_resume->setVisible(false);
    btn_home_sd->setVisible(false);
    btn_reload_sd->setVisible(false);
    btn_resume_sd->setVisible(false);
    mask->setVisible(false);
    if (mask_listener->isSwallowTouches()) {
        mask_listener->setSwallowTouches(false);
    }
    menu_avaliable = false;

}

void PauseLayer::onExit()
{
    Layer::onExit();
}