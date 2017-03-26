//
//  ScoreLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 11/1/14.
//
//

#include "ScoreLayer.h"

ScoreLayer::ScoreLayer()
{
    score = 0;
}

ScoreLayer::~ScoreLayer()
{
}

void ScoreLayer::onEnter()
{
    Layer::onEnter();
    
    auto size = Director::getInstance()->getVisibleSize();
    
    scoreLabel = LabelAtlas::create("98639", "fonts/cm_font.png", 70, 70, '0');
    scoreLabel->setString(StringUtils::format("%d", score));
    scoreLabel->setScale(0.8);
//    scoreLabel = Label::createWithBMFont("fonts/cm_font.fnt", StringUtils::format("%d", score));
    scoreLabel->setPosition(size.width/2, size.height-100);
//    scoreLabel->setSystemFontName("fonts/Andale Mono.ttf");
    scoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scoreLabel->setOpacity(128);
    
    addChild(scoreLabel);
}

int ScoreLayer::updateScore()
{
    score++;
    auto action = Spawn::create(ScaleBy::create(0.1, 1.2), FadeOut::create(0.1), NULL);
    
    scoreLabel->runAction(Sequence::create(action,
                                           CallFunc::create([this]()
                                                            {
                                                                scoreLabel->setString(StringUtils::format("%d", score));
                                                            }),
                                           action->reverse(), NULL));
    scoreLabel->setString(StringUtils::format("%d", score));
    
    return score;
}

void ScoreLayer::removing(Action* action)
{
    scoreLabel->removeFromParent();
}