//
//  RecordLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 2/3/15.
//
//

#include "RecordLayer.h"

int records[8];
std::string recordName[8];
Sprite* top_bg;

RecordLayer::RecordLayer()
{
    top_bg = nullptr;
}

RecordLayer::~RecordLayer()
{
    top_bg = nullptr;
}

RecordLayer* RecordLayer::create(int mode)
{
    auto l = new RecordLayer();
    if (l&&l->init(mode)) {
        l->autorelease();
        return l;
    } else
    {
        delete l;
        l = nullptr;
        return nullptr;
    }
}

bool RecordLayer::init(int m)
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//    this->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    this->setOpacity(0);
    this->runAction(FadeTo::create(0.1, 255));
    
    mode = m;
    
    auto mask = LayerColor::create(Color4B(0, 0, 0, 86));
    mask->setOpacity(0);
    mask->runAction(FadeTo::create(0.1, 86));
    addChild(mask, 0);
    auto mask_listener = EventListenerTouchOneByOne::create();
    mask_listener->onTouchBegan = [this](Touch* t, Event* e) {
        if (mode == 0) {
            this->scheduleOnce(schedule_selector(RecordLayer::hideMask), 0.1);
        } else {
            EventCustom e("game over");
            _eventDispatcher->dispatchEvent(&e);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mask_listener, mask);
    mask_listener->setSwallowTouches(true);
    
    top_bg = Sprite::createWithSpriteFrameName("top_bg.png");
    top_bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    top_bg->setPosition(visibleSize.width/2, visibleSize.height/2+10);
    addChild(top_bg, 2);
    
    auto top_bg_sd = Sprite::createWithSpriteFrameName("top_bg_sd.png");
    top_bg_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    top_bg_sd->setPosition(visibleSize.width/2 + 8, visibleSize.height/2);
    addChild(top_bg_sd, 1);
    
    auto label_top = Sprite::createWithSpriteFrameName("label_top.png");
    label_top->setPosition(Vec2(top_bg->getContentSize().width/2, 540));
    label_top->setScale(0.8);
    top_bg->addChild(label_top, 2);
    
    auto label_top_sd = Sprite::createWithSpriteFrameName("label_top_sd.png");
    label_top_sd->setPosition(Vec2(Vec2(top_bg->getContentSize().width/2+5, 535)));
    label_top_sd->setScale(0.8);
    top_bg->addChild(label_top_sd, 1);
    
    for (int i=0; i<8; i++)
    {
        auto record = UserDefault::getInstance()->getStringForKey(StringUtils::format("%d_record_name", i).c_str(), "player");
        recordName[i] = record;
    }
    
    for (int i=0; i<8; i++)
    {
        auto record = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%d_record", i).c_str(), 0);
        records[i] = record;
    }
    
    addRecord();
    
    return true;
}

void RecordLayer::addRecord()
{
    for (int i=0; i<8; i++) {
        auto record_r = Label::createWithTTF(StringUtils::format("%d", i+1), "fonts/cm.ttf", 32);
        record_r->setPosition(60, 450 - i*55);
        record_r->setColor(Color3B(134, 134, 134));
        record_r->setTag(i);
        
        auto record_n = Label::createWithTTF(recordName[i], "fonts/cm.ttf", 32);
        record_n->setPosition(170, 450 - i*55);
        record_n->setColor(Color3B(134, 134, 134));
        record_n->setTag(i+8);
        
        auto record = Label::createWithTTF(StringUtils::format("%d", records[i]), "fonts/cm.ttf", 32);
        record->setPosition(400, 450 - i*55);
        record->setColor(Color3B(134, 134, 134));
        record->setTag(i+16);
        
        top_bg->addChild(record_r);
        top_bg->addChild(record_n);
        top_bg->addChild(record);
    }
    top_bg->getChildByTag(0)->setColor(Color3B(223, 128, 128));
    top_bg->getChildByTag(1)->setColor(Color3B(225, 216, 131));
    top_bg->getChildByTag(2)->setColor(Color3B(128, 181, 223));
    
    top_bg->getChildByTag(8)->setColor(Color3B(223, 128, 128));
    top_bg->getChildByTag(9)->setColor(Color3B(225, 216, 131));
    top_bg->getChildByTag(10)->setColor(Color3B(128, 181, 223));
    
    top_bg->getChildByTag(16)->setColor(Color3B(223, 128, 128));
    top_bg->getChildByTag(17)->setColor(Color3B(225, 216, 131));
    top_bg->getChildByTag(18)->setColor(Color3B(128, 181, 223));
}

void RecordLayer::hideMask(float dt)
{
    EventCustom e2("show record");
    _eventDispatcher->dispatchEvent(&e2);
}