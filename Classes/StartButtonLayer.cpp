//
//  StartButtonLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 11/3/14.
//
//

#include "StartButtonLayer.h"

float btnDuration = 0.2;

Vec2 originsBtn[6];

StartButtonLayer::StartButtonLayer()
{
    _gameScene = nullptr;
}

StartButtonLayer::~StartButtonLayer()
{
    _gameScene = nullptr;
}

bool StartButtonLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    // button tag
    // start : 0 | start_sd : 1
    // rate  : 2 | rate_sd  : 3
    // rank  : 4 | rank_sd  : 5
    
    // start button and shadow
    btnStart = Sprite::createWithSpriteFrameName("btnStart.png");
    btnStart->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnStart->setPosition(-btnStart->getContentSize().width, visibleSize.height/2);
    auto origin_start = btnStart->getPosition();
    auto actionStart = MoveTo::create(btnDuration, Vec2(visibleSize.width/2, visibleSize.height*2/5));
    btnStart->setTag(0);
    addChild(btnStart, 2);
    btnStart->runAction(EaseIn::create(actionStart, 2));
    
    btnStart_sd = Sprite::createWithSpriteFrameName("btnStart_sd.png");
    btnStart_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnStart_sd->setPosition(btnStart->getPosition() + Vec2(8, -10));
    auto origin_start_sd = btnStart_sd->getPosition();
    auto actionStart_sd = MoveTo::create(btnDuration, Vec2(visibleSize.width/2, visibleSize.height*2/5) + Vec2(8, -10));
    btnStart_sd->runAction(EaseIn::create(actionStart_sd, 2));
    btnStart_sd->setTag(1);
    addChild(btnStart_sd, 1);
    
    // rate button and shadow
    btnRate = Sprite::createWithSpriteFrameName("btnRate.png");
    btnRate->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnRate->setPosition(-btnRate->getContentSize().width, -btnRate->getContentSize().height);
    auto origin_rate = btnRate->getPosition();
    auto actionRate = MoveTo::create(btnDuration, Vec2(29 + btnRate->getContentSize().width/2,
                                                       37 + btnRate->getContentSize().height/2));
    btnRate->runAction(EaseIn::create(actionRate, 2));
    btnRate->setTag(2);
    addChild(btnRate, 2);
    
    btnRate_sd = Sprite::createWithSpriteFrameName("btnRate_sd.png");
    btnRate_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnRate_sd->setPosition(btnRate->getPosition() + Vec2(8, -10));
    auto origin_rate_sd = btnRate_sd->getPosition();
    auto actionRate_sd = MoveTo::create(btnDuration, Vec2(29 + btnRate->getContentSize().width/2 + 8,
                                                          37 + btnRate->getContentSize().height/2 - 10));
    btnRate_sd->runAction(EaseIn::create(actionRate_sd, 2));
    btnRate_sd->setTag(3);
    addChild(btnRate_sd, 1);
    
    // rank button and shadow
    btnRank = Sprite::createWithSpriteFrameName("btnRank.png");
    btnRank->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnRank->setPosition(visibleSize.width + btnRank->getContentSize().width, -btnRank->getContentSize().height);
    auto origin_rank = btnRank->getPosition();
    auto actionRank = MoveTo::create(btnDuration, Vec2(visibleSize.width - btnRank->getContentSize().width/2 - 29,
                                                       37 + btnRank->getContentSize().height/2));
    btnRank->runAction(EaseIn::create(actionRank, 2));
    btnRank->setTag(4);
    addChild(btnRank, 2);
    
    btnRank_sd = Sprite::createWithSpriteFrameName("btnRank_sd.png");
    btnRank_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnRank_sd->setPosition(btnRank->getPosition() + Vec2(8, -10));
    auto origin_rank_sd = btnRank_sd->getPosition();
    auto actionRank_sd = MoveTo::create(btnDuration, Vec2(visibleSize.width - btnRank->getContentSize().width/2 - 29 + 8,
                                                          37 + btnRank->getContentSize().height/2 - 10));
    btnRank_sd->runAction(EaseIn::create(actionRank_sd, 2));
    btnRank_sd->setTag(5);
    addChild(btnRank_sd, 1);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t, Event* e)
    {
        auto btn = e->getCurrentTarget();
        if (btn->getBoundingBox().containsPoint(t->getLocation()))
        {
            auto btn_sd = this->getChildByTag(btn->getTag() + 1);
            btn->setPosition(btn->getPosition() + Vec2(4, -5));
            btn_sd->setPosition(btn_sd->getPosition() + Vec2(-4, 5));
        }
        return true;
    };
    
    listener->onTouchEnded = [this](Touch* t, Event* e)
    {
        auto btn = e->getCurrentTarget();
        if (btn->getBoundingBox().containsPoint(t->getStartLocation()))
        {
            auto btn_sd = this->getChildByTag(btn->getTag() + 1);
            btn->setPosition(btn->getPosition() + Vec2(-4, 5));
            btn_sd->setPosition(btn_sd->getPosition() + Vec2(4, -5));
            int tag = btn->getTag();
            switch (tag)
            {
                case 0:
                {
                    this->enterGame();
                    break;
                }
                case 1:
                {
                    
                }
                default:
                    break;
            }

        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), btnStart);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), btnRate);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), btnRank);
    
    originsBtn[0] = origin_start;
    originsBtn[1] = origin_start_sd;
    originsBtn[2] = origin_rate;
    originsBtn[3] = origin_rate_sd;
    originsBtn[4] = origin_rank;
    originsBtn[5] = origin_rank_sd;
    
    return true;
}

void StartButtonLayer::onEnter()
{
    Layer::onEnter();
    _gameScene = dynamic_cast<Enter*>(this->getParent());
}

void StartButtonLayer::enterGame()
{
    _gameScene->startGamePrepare();
}

void StartButtonLayer::removingPrepare()
{
    btnStart->runAction(EaseOut::create(MoveTo::create(btnDuration, originsBtn[0]),1));
    btnStart_sd->runAction(EaseOut::create(MoveTo::create(btnDuration, originsBtn[1]),1));
    
    btnRate->runAction(EaseOut::create(MoveTo::create(btnDuration, originsBtn[2]),1));
    btnRate_sd->runAction(EaseOut::create(MoveTo::create(btnDuration, originsBtn[3]),1));
    
    btnRank->runAction(EaseOut::create(MoveTo::create(btnDuration, originsBtn[4]),1));
    btnRank_sd->runAction(EaseOut::create(MoveTo::create(btnDuration, originsBtn[5]),1));
}