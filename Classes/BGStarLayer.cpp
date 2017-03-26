//
//  BGStarLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 12/20/14.
//
//

#include "BGStarLayer.h"
#include "math.h"

BGStarLayer* BGStarLayer::create(int i)
{
    auto l = new BGStarLayer();
    if (l && l->init(i)) {
        l->autorelease();
        return l;
    }
    delete l;
    l = nullptr;
    return nullptr;
}

bool BGStarLayer::init(int i)
{
    if (!Layer::init()) {
        return false;
    }
    
    srand((int)time(nullptr));
    mode = i;
    
    stars = new Vector<Sprite*>();
    
    if (i == 0)
    {
        auto s1 = Sprite::createWithSpriteFrameName("star_s1.png");
        auto s2 = Sprite::createWithSpriteFrameName("star_s1.png");
        auto s3 = Sprite::createWithSpriteFrameName("star_s2.png");
        auto s4 = Sprite::createWithSpriteFrameName("star_s3.png");
        auto s5 = Sprite::createWithSpriteFrameName("star.png");
        auto s6 = Sprite::createWithSpriteFrameName("star.png");
        auto s7 = Sprite::createWithSpriteFrameName("star.png");
        auto s8 = Sprite::createWithSpriteFrameName("star.png");
        stars->pushBack(s1);
        stars->pushBack(s2);
        stars->pushBack(s3);
        stars->pushBack(s4);
        stars->pushBack(s5);
        stars->pushBack(s6);
        stars->pushBack(s7);
        stars->pushBack(s8);
    }
    else
    {
        auto s1 = Sprite::createWithSpriteFrameName("star_s1.png");
        auto s2 = Sprite::createWithSpriteFrameName("star_s1.png");
        auto s3 = Sprite::createWithSpriteFrameName("star_s2.png");
        auto s4 = Sprite::createWithSpriteFrameName("star_s2.png");
        stars->pushBack(s1);
        stars->pushBack(s2);
        stars->pushBack(s3);
        stars->pushBack(s4);
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    return true;
}

void BGStarLayer::onEnter()
{
    Layer::onEnter();
    if (mode == 0)
    {
        Vec2 star_postions[8] = {
            Vec2(visibleSize.width/3, visibleSize.height*2/3),
            Vec2(visibleSize.width/7, visibleSize.height*4/5),
            Vec2(visibleSize.width/12, visibleSize.height*3/5),
            Vec2(visibleSize.width/2+30, visibleSize.height/2+50),
            Vec2(visibleSize.width/2+20, visibleSize.height*4/5),
            Vec2(visibleSize.width-100, visibleSize.height*2/3),
            Vec2(visibleSize.width/2-100, 70),
            Vec2(visibleSize.width-50, 200)
        };
        for ( int i = 0; i < 8; i++)
        {
            auto star = stars->at(i);
            star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            star->setOpacity(128);
            star->setPosition(visibleSize.width, visibleSize.height);
            addChild(star);
            int x = rand()%(int)(visibleSize.width - 200) + 100;
            int y = rand()%(int)(visibleSize.height - 200) + 100;
            int rotate = rand()%180+90;
            float dt = (sqrt(x^2 + y^2))/16;
            log("%f", dt);
            star->runAction(Spawn::create(MoveTo::create(dt, star_postions[i]),RotateBy::create(dt, rotate), NULL));
        }
        schedule(schedule_selector(BGStarLayer::random_move), 3);
    }
    else
    {
        for (auto star : *stars)
        {
            star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            star->setOpacity(128);
            addChild(star);
            int x = rand()%(int)(visibleSize.width - 200) + 100;
            int y = rand()%(int)(visibleSize.height - 200) + 100;
            star->setPosition(x, y);
            int rotate = rand()%180+90;
            star->setRotation(rotate);
            star->runAction(Sequence::create(MoveBy::create(6, Vec2(0, 1136)), CallFunc::create([star](){
                star->removeFromParent();
            }), NULL));
        }
        schedule(schedule_selector(BGStarLayer::addStar), 2);
//        _eventDispatcher->addCustomEventListener("turn_star", [this](EventCustom* e)
//                                                 {
//                                                     auto ball = (Sprite*)e->getUserData();
//                                                     auto star = Sprite::create("star.png");
//                                                     star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//                                                     star->setPosition(ball->getPosition());
//                                                     star->setRotation(ball->getRotation());
//                                                     star->setOpacity(120);
//                                                     star->runAction(Sequence::create(MoveBy::create(6, Vec2(0, 1136)), CallFunc::create([star](){
//                                                         star->removeFromParent();
//                                                     }), NULL));
//
//                                                     this->addChild(star);
//                                                 });
    }
}

void BGStarLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeCustomEventListeners("turn_star");
}

void BGStarLayer::addStar(float dt)
{
    int size = rand()%2+1;
    auto star = Sprite::createWithSpriteFrameName(StringUtils::format("star_s%d.png", size));
    addChild(star);
    star->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    star->setPosition(rand()%600, 0);
    star->setRotation(rand()%90);
    star->setOpacity(120);
    // rate = 1136/6 px/s;
    star->runAction(Sequence::create(MoveBy::create(6, Vec2(0, 1136)), CallFunc::create([star](){
        star->removeFromParent();
    }), NULL));
}

void BGStarLayer::random_move(float dt)
{
    for (auto star : *stars)
    {
        int x = rand()%10 - 5;
        int y = rand()%10 - 5;
        int z = rand()%30 - 15;
        auto move = Sequence::create(MoveBy::create(2, Vec2(x, y)), NULL);
        auto rotate = RotateBy::create(2, z);
        star->runAction(Spawn::create(move, rotate, NULL));
    }
}