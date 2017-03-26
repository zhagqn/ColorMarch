//
//  BGLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#include "BGLayer.h"
#include "BGStarLayer.h"

BGLayer* bgLayer;
int m_color = -1;

Color4B colors[3] = {
    Color4B(140, 196, 184, 255),
    Color4B(149, 140, 196, 255),
    Color4B(160, 196, 140, 255)
};

//BGLayer* BGLayer::createBGLayer()
//{
//    if (bgLayer == nullptr) {
//        bgLayer = BGLayer::create();
//    }
//    return bgLayer;
//}

BGLayer* BGLayer::create(int flag)
{
    auto l = new BGLayer();
    if (l&&l->init(flag)) {
        l->autorelease();
        return l;
    }
    else
    {
        delete l;
        l = nullptr;
        return nullptr;
    }
}

bool BGLayer::init(int flag)
{
    srand((unsigned)time(NULL));
    if (m_color == -1) {
        int rd_c = rand()%3;
        m_color = rd_c;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
    }
    
    addChild(LayerColor::create(colors[m_color]));
    
    cover = Sprite::createWithSpriteFrameName("bg_cover.png");
    cover->setAnchorPoint(Vec2::ZERO);
    this->setScale(1.1);
    addChild(cover);
    
    cover2 = Sprite::createWithSpriteFrameName("bg_cover.png");
    cover2->setAnchorPoint(Vec2::ZERO);
    this->setScale(1.1);
    addChild(cover2);
    
    if (flag == 0)
    {
        cover2->setPosition(Vec2(0, -visibleSize.height));
        cover->addChild(BGStarLayer::create(0));
    }
    else if (flag == 1)
    {
        cover2->setPosition(Vec2(0, visibleSize.height));
        auto s1 = Sprite::createWithSpriteFrameName("star.png");
        s1->setPosition(visibleSize.width/2-100, visibleSize.height-70);
        s1->setOpacity(120);
        auto s2 = Sprite::createWithSpriteFrameName("star.png");
        s2->setPosition(visibleSize.width-50, visibleSize.height-200);
        s2->setOpacity(120);
        cover2->addChild(s1);
        cover2->addChild(s2);
        cover->addChild(BGStarLayer::create(1));
    }
    
    
    return true;
}

void BGLayer::removing(Action* action)
{
    cover->runAction(action->clone());
    cover2->runAction(action->clone());
}

void BGLayer::appearing()
{
    cover->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0, visibleSize.height)), NULL));
    cover2->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0, visibleSize.height)), NULL));
}