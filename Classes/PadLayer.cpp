//
//  PadLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#include "PadLayer.h"

Vector<Sprite*>* pads;
Vector<Sprite*>* pads_sd;

PadLayer::PadLayer()
{
//    _gameScene = nullptr;
    pads = nullptr;
    pads_sd = nullptr;
}

PadLayer::~PadLayer()
{
//    _gameScene = nullptr;
    pads = nullptr;
    pads_sd = nullptr;
}

bool PadLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    return true;
}

void PadLayer::onEnter()
{
    Layer::onEnter();
    enableTouch = true;
    // init
//    _gameScene = dynamic_cast<Game*>(this->getParent());
    pads = new Vector<Sprite*>();
    pads_sd = new Vector<Sprite*>();
    
    // listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t, Event* e)
    {
        auto p = (Sprite*)e->getCurrentTarget();
        if (enableTouch && p->getBoundingBox().containsPoint(t->getLocation()))
        {
            p->setOpacity(200);
            auto pos = p->getPosition();
            p->setPosition(pos.x + 3, pos.y - 4);
            
            auto p_sd = pads_sd->at(p->getTag());
            auto pos_sd = p_sd->getPosition();
            p_sd->setPosition(pos_sd.x - 3, pos_sd.y + 4);
        }
        return true;
    };
    listener->onTouchEnded = [this](Touch* t, Event* e)
    {
        auto p = (Sprite*)e->getCurrentTarget();
        p->setOpacity(255);
        if (enableTouch && p->getBoundingBox().containsPoint(t->getStartLocation()))
        {
            auto pos = p->getPosition();
            p->setPosition(pos.x - 3, pos.y + 4);
            
            auto p_sd = pads_sd->at(p->getTag());
            auto pos_sd = p_sd->getPosition();
            p_sd->setPosition(pos_sd.x + 3, pos_sd.y - 4);

            // invoke parent's touchPad()
//            this->touchPad(p->getTag());
            
            EventCustom event("touch pad");
            event.setUserData(p);
            _eventDispatcher->dispatchEvent(&event);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
        }
    };
    
    // add pads and shadows
    for (int i = 0; i < 3; i++)
    {
        // pads
        auto pad = Sprite::createWithSpriteFrameName(StringUtils::format("pad_%d.png", i));
        pad->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        auto size = pad->getContentSize();
        float height = size.height;
        pad->setPosition(visibleSize.width/3 * i + visibleSize.width/6, -height/2);
        pad->runAction(MoveBy::create(0.3, Vec2(0, height + 8)));
        pad->setTag(i);
        addChild(pad, 1);
        
        pads->pushBack(pad);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), pad);
        
        // shadows
        auto pad_sd = Sprite::createWithSpriteFrameName("pad_sd.png");
        pad_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        auto size_sd = pad_sd->getContentSize();
        float height_sd = pad_sd->getContentSize().height;
        pad_sd->setPosition(pad->getPosition() + Vec2(6, 8));
        pad_sd->runAction(MoveBy::create(0.3, Vec2(0, height_sd-8)));
        addChild(pad_sd, 0);
        
        pads_sd->pushBack(pad_sd);
    }
}

//void PadLayer::touchPad(int idx)
//{
//    _gameScene->touchPad(idx);
//}

void PadLayer::removing(Action* action)
{
    enableTouch = false;
    this->runAction(action);
    
    //    for (int i = 0; i < 3; i++) {
//        auto pad = pads->at(i);
//        float height = pad->getContentSize().height;
//        pad->runAction(MoveBy::create(0.3, Vec2(0, -height - 9)));
//        
//        auto pad_sd = pads_sd->at(i);
//        float height_sd = pad_sd->getContentSize().height;
//        pad_sd->runAction(MoveBy::create(0.3, Vec2(0, -height_sd)));
//    }
}