//
//  YoyoLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 11/9/14.
//
//

#include "YoyoLayer.h"
#include "math.h"

void YoyoLayer::onEnter()
{
    Layer::onEnter();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    title = Sprite::createWithSpriteFrameName("label_title.png");
    title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    title->setPosition(visibleSize.width/2, visibleSize.height);
    
    auto title_down = EaseBackOut::create(MoveBy::create(0.3, Vec2(0, -visibleSize.height/5)));
    title->runAction(title_down);
    addChild(title);
    
    yoyo_r = Sprite::createWithSpriteFrameName("ball_0.png");
    yoyo_r->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    yoyo_r->setPosition(Vec2(visibleSize.width/6, visibleSize.height*3/5 - 60));
    addChild(yoyo_r, 1);
    
    yoyo_r_sd = Sprite::createWithSpriteFrameName("ball_sd.png");
    yoyo_r_sd->setScale(0.95);
    yoyo_r_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    yoyo_r_sd->setPosition(Vec2(visibleSize.width/6, visibleSize.height*3/5 - 60) + Vec2(4, -6));
    addChild(yoyo_r_sd, 0);
    
    yoyo_b = Sprite::createWithSpriteFrameName("ball_1.png");
    yoyo_b->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    yoyo_b->setPosition(Vec2(visibleSize.width*3/6, visibleSize.height*3/5 + 100));
    addChild(yoyo_b, 1);
    
    yoyo_b_sd = Sprite::createWithSpriteFrameName("ball_sd.png");
    yoyo_b_sd->setScale(0.95);
    yoyo_b_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    yoyo_b_sd->setPosition(Vec2(visibleSize.width*3/6, visibleSize.height*3/5 + 100) + Vec2(4, -6));
    addChild(yoyo_b_sd, 0);
    
    yoyo_y = Sprite::createWithSpriteFrameName("ball_2.png");
    yoyo_y->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    yoyo_y->setPosition(Vec2(visibleSize.width*5/6, visibleSize.height*3/5));
    addChild(yoyo_y, 1);
    
    yoyo_y_sd = Sprite::createWithSpriteFrameName("ball_sd.png");
    yoyo_y_sd->setScale(0.95);
    yoyo_y_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    yoyo_y_sd->setPosition(Vec2(visibleSize.width*5/6, visibleSize.height*3/5) + Vec2(4, -6));
    addChild(yoyo_y_sd, 0);
    
    srand((int)time(NULL));
    
    schedule(schedule_selector(YoyoLayer::random_move), 2);
    
    yoyo_loc[0] = yoyo_r->getPosition();
    yoyo_loc[1] = yoyo_b->getPosition();
    yoyo_loc[2] = yoyo_y->getPosition();
    
    yoyos = new Vector<Sprite*>();
    yoyos->pushBack(yoyo_r);
    yoyos->pushBack(yoyo_b);
    yoyos->pushBack(yoyo_y);
    
    yoyos_sd = new Vector<Sprite*>();
    yoyos_sd->pushBack(yoyo_r_sd);
    yoyos_sd->pushBack(yoyo_b_sd);
    yoyos_sd->pushBack(yoyo_y_sd);
    
//    yoyo_r = Sprite::create("yoyo_r.png");
//    yoyo_r_l = Sprite::create("yoyo_r_l.png");
//    auto size_r = yoyo_r->getContentSize();
//    auto size_r_l = yoyo_r_l->getContentSize();
//    yoyo_r->setAnchorPoint(Vec2(59/size_r.width, 1 + 164 / size_r.height));
//    yoyo_r_l->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
//    auto pos_yoyo_r = Vec2(79, visibleSize.height);
//    yoyo_r->setPosition(pos_yoyo_r +Vec2(0, size_r.height + size_r_l.height));
//    yoyo_r_l->setPosition(pos_yoyo_r + Vec2(0, size_r.height + size_r_l.height));
//    
//    
//    yoyo_b = Sprite::create("yoyo_b.png");
//    yoyo_b_l = Sprite::create("yoyo_b_l.png");
//    auto size_b = yoyo_b->getContentSize();
//    auto size_b_l = yoyo_b_l->getContentSize();
//    yoyo_b->setAnchorPoint(Vec2(60/size_b.width, 1 + 58 / size_b.height));
//    yoyo_b_l->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
//    auto pos_yoyo_b = Vec2(79 + visibleSize.width/3, visibleSize.height);
//    yoyo_b->setPosition(pos_yoyo_b + Vec2(0, size_b.height + size_b_l.height));
//    yoyo_b_l->setPosition(pos_yoyo_b + Vec2(0, size_b.height + size_b_l.height));
//    
//    
//    yoyo_y = Sprite::create("yoyo_y.png");
//    yoyo_y_l = Sprite::create("yoyo_y_l.png");
//    auto size_y = yoyo_y->getContentSize();
//    auto size_y_l = yoyo_y_l->getContentSize();
//    yoyo_y->setAnchorPoint(Vec2(60/size_y.width, 1 + 112 / size_y.height));
//    yoyo_y_l->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
//    auto pos_yoyo_y = Vec2(79 + visibleSize.width/3*2, visibleSize.height);
//    yoyo_y->setPosition(pos_yoyo_y + Vec2(0, size_y.height + size_y_l.height));
//    yoyo_y_l->setPosition(pos_yoyo_y + Vec2(0, size_y.height + size_y_l.height));
//    
////    auto rotate = RepeatForever::create(Sequence::createWithTwoActions(RotateBy::create(0.1, 20), RotateBy::create(0.1, -20)));
//
//    
//    addChild(yoyo_r);
//    addChild(yoyo_r_l);
//    
//    addChild(yoyo_b);
//    addChild(yoyo_b_l);
//    
//    addChild(yoyo_y);
//    addChild(yoyo_y_l);
//    
//    float g = 720;
//    float t1 = sqrt((size_r.height + size_r_l.height)*2 / g);
//    float t2 = sqrt((size_b.height + size_b_l.height)*2 / g);
//    float t3 = sqrt((size_y.height + size_y_l.height)*2 / g);
//    
//    auto rotate = Repeat::create(Sequence::create(EaseOut::create(RotateBy::create(1, 1), 1.5),
//                                                  EaseIn::create(RotateBy::create(1, -1), 1.5),
//                                                  EaseOut::create(RotateBy::create(1, -1), 1.5),
//                                                  EaseIn::create(RotateBy::create(1, 1), 1.5), NULL), 99999);
//    rotate->setTag(1);
//    
//    auto ebo1 = EaseBounceOut::create(MoveBy::create(t1, Vec2(0, -(size_r.height + size_r_l.height))));
//    auto down_r = Sequence::create(ebo1, rotate, NULL);
//    yoyo_r->runAction(down_r);
//    yoyo_r_l->runAction(down_r->clone());
//    
//    auto ebo2 = EaseBounceOut::create(MoveBy::create(t2, Vec2(0, -(size_b.height + size_b_l.height))));
//    auto down_b = Sequence::create(ebo2, rotate->reverse(), NULL);
//    yoyo_b->runAction(down_b);
//    yoyo_b_l->runAction(down_b->clone());
//    
//    auto ebo3 = EaseBounceOut::create(MoveBy::create(t3, Vec2(0, -(size_y.height + size_y_l.height))));
//    auto down_y = Sequence::create(ebo3, rotate->clone(), NULL);
//    yoyo_y->runAction(down_y);
//    yoyo_y_l->runAction(down_y->clone());
}

void YoyoLayer::random_move(float dt)
{
    for (int i=0; i<3; i++)
    {
        int x = rand()%10-5;
        int y = rand()%10-5;
        
        auto loc = yoyos->at(i)->getPosition();
        
        
        auto move = Sequence::create(MoveBy::create(1, Vec2(x, y)),
                                                        MoveBy::create(1, Vec2(-x, -y)), NULL);
        yoyos->at(i)->runAction(move);
        yoyos_sd->at(i)->runAction(move->clone());
    }
}

void YoyoLayer::removingPrepare()
{
//    yoyo_r->stopAllActions();
//    yoyo_b->stopAllActions();
//    yoyo_y->stopAllActions();
//    
//    yoyo_r->setRotation(0);
//    yoyo_b->setRotation(0);
//    yoyo_y->setRotation(0);
//    
//    yoyo_r_l->stopAllActions();
//    yoyo_b_l->stopAllActions();
//    yoyo_y_l->stopAllActions();
//    
//    yoyo_r_l->setRotation(0);
//    yoyo_b_l->setRotation(0);
//    yoyo_y_l->setRotation(0);
//    
//    auto moveDown = EaseIn::create(MoveBy::create(3, Vec2(0, -visibleSize.height)), 2);
//    yoyo_r->runAction(moveDown->clone());
//    yoyo_b->runAction(moveDown->clone());
//    yoyo_y->runAction(moveDown->clone());
    
    scheduleOnce(schedule_selector(YoyoLayer::removing), 0);
}

void YoyoLayer::removing(float dt)
{
    this->runAction(MoveBy::create(1, Vec2(0, visibleSize.height)));
}