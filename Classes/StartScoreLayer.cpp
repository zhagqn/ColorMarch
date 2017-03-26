//
//  StartScoreLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 11/12/14.
//
//

#include "StartScoreLayer.h"

void StartScoreLayer::onEnter()
{
    Layer::onEnter();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    int s_last = UserDefault::getInstance()->getIntegerForKey("last_score");
    int s_best = UserDefault::getInstance()->getIntegerForKey("best_score");
    
    last = Sprite::createWithSpriteFrameName("label_last.png");
    last->setAnchorPoint(Vec2::ZERO);
    auto l_last = LabelAtlas::create("", "fonts/cm_font.png", 70, 70, '0');
    l_last->setString(StringUtils::format("%d", s_last));
//    auto l_last = LabelBMFont::create(StringUtils::format("%d", s_last),  "fonts/cm_font.fnt");
    l_last->setOpacity(160);
    l_last->setScale(0.7);
    l_last->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    l_last->setPosition(last->getContentSize().width/2, -l_last->getContentSize().height/2);
    last->addChild(l_last);
    last->setPosition(180, 240);
    addChild(last);
    
    best = Sprite::createWithSpriteFrameName("label_best.png");
    best->setAnchorPoint(Vec2::ZERO);
    auto l_best = LabelAtlas::create("", "fonts/cm_font.png", 70, 70, '0');
    l_best->setString(StringUtils::format("%d", s_best));
//    auto l_best = Label::createWithBMFont("fonts/cm_font.fnt", StringUtils::format("%d", s_best));
    l_best->setOpacity(160);
    l_best->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    l_best->setScale(0.7);
    l_best->setPosition(best->getContentSize().width/2, -l_best->getContentSize().height/2);
    best->addChild(l_best);
    best->setPosition(visibleSize.width - 180 - best->getContentSize().width, 240);
    addChild(best);
    
    l_best->runAction(RepeatForever::create(Sequence::create(ScaleBy::create(0.5, 1.1), ScaleBy::create(0.5, 1/1.1), NULL)));
    
    auto rank_listener = EventListenerTouchOneByOne::create();
    rank_listener->onTouchBegan = [this](Touch* t, Event* e) {
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation())) {
            EventCustom e("show record");
            _eventDispatcher->dispatchEvent(&e);
        }
        return true;
    };
    rank_listener->onTouchEnded = [](Touch* t, Event* e) {
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(rank_listener, best);
}

void StartScoreLayer::removingPrepare()
{
    this->runAction(Sequence::create(MoveBy::create(1, Vec2(0, visibleSize.height)), NULL));
}