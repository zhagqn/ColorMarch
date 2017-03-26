//
//  NewRecordLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 2/4/15.
//
//

#include "NewRecordLayer.h"
#include <string.h>
#include <string>

std::string editBoxString;

bool NewRecordLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();

    auto mask = LayerColor::create(Color4B(0, 0, 0, 86));
    mask->setOpacity(0);
    mask->runAction(FadeTo::create(0.1, 86));
    addChild(mask, 0);
    auto mask_listener = EventListenerTouchOneByOne::create();
    mask_listener->onTouchBegan = [this](Touch* t, Event* e) {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mask_listener, mask);
    mask_listener->setSwallowTouches(true);
    
    this->setOpacity(0);
    this->runAction(FadeTo::create(0.1, 255));
    
    
    float offset_h = visibleSize.height*2/3-100;
    
    auto layer_nr = Sprite::createWithSpriteFrameName("layer_nr.png");
    layer_nr->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layer_nr->setPosition(Vec2(visibleSize.width/2, offset_h));
    addChild(layer_nr, 2);
    
    auto layer_nr_sd = Sprite::createWithSpriteFrameName("layer_nr_sd.png");
    layer_nr_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layer_nr_sd->setPosition(Vec2(visibleSize.width/2+10, offset_h-10));
    addChild(layer_nr_sd, 1);
    
    auto label_nr = Sprite::createWithSpriteFrameName("label_nr.png");
    label_nr->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    label_nr->setScale(0.9);
    label_nr->setPosition(Vec2(visibleSize.width/2, offset_h+100));
    addChild(label_nr, 2);
    
    auto label_id = Sprite::createWithSpriteFrameName("label_id.png");
    label_id->setPosition(Vec2(visibleSize.width/5 + 35, offset_h+15));
    addChild(label_id, 2);
    
    auto input_nr = Sprite::createWithSpriteFrameName("input_nr.png");
    input_nr->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    input_nr->setPosition(Vec2(visibleSize.width/2+20, offset_h+15));
    addChild(input_nr, 2);
    
    auto editBox = EditBox::create(Size(250, 55), Scale9Sprite::create());
    editBox->setPosition(Vec2(visibleSize.width/2+20, offset_h+12));
    editBox->setInputMode(EditBox::InputMode::ANY);
    editBox->setDelegate(this);
    editBox->setMaxLength(6);
    addChild(editBox, 3);
    
    
    
    auto btn_yes = Sprite::createWithSpriteFrameName("btn_yes.png");
    btn_yes->setPosition(Vec2(visibleSize.width/3+10, offset_h-78));
    addChild(btn_yes, 3);
  
    auto btn_yes_sd = Sprite::createWithSpriteFrameName("btn_nr_sd.png");
    btn_yes_sd->setPosition(Vec2(visibleSize.width/3+15, offset_h-83));
    addChild(btn_yes_sd, 2);
    
    auto yes_listener = EventListenerTouchOneByOne::create();
    yes_listener->onTouchBegan = [this](Touch* t, Event* e)
    {
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation())) {
            EventCustom e("game over");
            e.setUserData(&editBoxString);
            _eventDispatcher->dispatchEvent(&e);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(yes_listener, btn_yes);
    
    auto btn_no = Sprite::createWithSpriteFrameName("btn_no.png");
    btn_no->setPosition(Vec2(visibleSize.width*2/3-10, offset_h-78));
    addChild(btn_no, 3);
    
    auto btn_no_sd = Sprite::createWithSpriteFrameName("btn_nr_sd.png");
    btn_no_sd->setPosition(Vec2(visibleSize.width*2/3-5, offset_h-83));
    addChild(btn_no_sd, 2);
    
    auto no_listener = EventListenerTouchOneByOne::create();
    no_listener->onTouchBegan = [this](Touch* t, Event* e)
    {
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation())) {
            EventCustom e("game over");
            e.setUserData(nullptr);
            _eventDispatcher->dispatchEvent(&e);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(no_listener, btn_no);
    

    return true;
}

void NewRecordLayer::onExit()
{
    Layer::onExit();
}

void NewRecordLayer::editBoxEditingDidBegin(EditBox* editBox)
{
    
}

void NewRecordLayer::editBoxEditingDidEnd(EditBox* editBox)
{
    
}

void NewRecordLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    editBoxString = text;
}

void NewRecordLayer::editBoxReturn(EditBox* editBox)
{
    
}