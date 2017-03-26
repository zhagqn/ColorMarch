//
//  CoverLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 2/9/15.
//
//

#include "CoverLayer.h"


bool CoverLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 128));
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto stencil = Sprite::create();
    stencil->setTextureRect(Rect(0, 0, visibleSize.width/3, visibleSize.height/8.2));
    stencil->setContentSize(Size(visibleSize.width/3, visibleSize.height/8.5));
    stencil->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    
    auto clipper = ClippingNode::create();
    clipper->setStencil(stencil);
    clipper->setInverted(true);
    clipper->addChild(bg, -1);
    clipper->setAlphaThreshold(0.5f);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* t, Event* e)
    {
        _eventDispatcher->dispatchCustomEvent("resume game");
        this->removeFromParent();
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, stencil);
    
    auto coverListener = EventListenerCustom::create("set cover", [this, stencil](EventCustom *e)
                                                     {
                                                         int re = *(int*)(e->getUserData());
//                                                         stencil->addChild(s);
                                                         int offset = re/10;
                                                         stencil->setPosition(visibleSize.width/6+visibleSize.width/3 * offset,
                                                                                    visibleSize.height/20);
                                                     });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(coverListener, this);
    
    addChild(clipper);
    
    auto tip = Label::createWithTTF("点击相应颜色踏板摧毁最快掉落的小球", "fonts/cm.ttf", 32);
    tip->setColor(Color3B(255, 255, 255));
    tip->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tip->setPosition(visibleSize.width/2, visibleSize.height/4);
    addChild(tip);
    return true;
}