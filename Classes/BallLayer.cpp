//
//  BallLayer.cpp
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#include "BallLayer.h"

Vector<Sprite*>* balls;
Vector<Sprite*>* balls_sd;

int last_c_l;

BallLayer::BallLayer()
{
    last_c_l = -1;
    step = 0.7;
    race = 5;
    isOver = false;
}

BallLayer::~BallLayer()
{

}

bool BallLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    srand((unsigned)time(nullptr));
    
    balls = new Vector<Sprite*>();
    balls_sd = new Vector<Sprite*>();
    
    auto touchedListener = EventListenerCustom::create("touch pad", [this](EventCustom *e)
                                                       {
                                                           int tag = ((Sprite*)(e->getUserData()))->getTag();
                                                           int re = this->checkTouch(tag);
                                                           
                                                           EventCustom event("touch check");
                                                           event.setUserData(&re);
                                                           _eventDispatcher->dispatchEvent(&event);
                                                       });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchedListener, this);
    
    auto coverListener = EventListenerCustom::create("cover return", [this](EventCustom *e)
                                                     {
                                                         EventCustom event("set cover");
                                                         int re = ((Sprite*)(balls->at(0)))->getTag();
                                                         event.setUserData(&re);
                                                         _eventDispatcher->dispatchEvent(&event);
                                                     });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(coverListener, this);
    
    return true;
}

void BallLayer::onEnter()
{
    Layer::onEnter();
    
    _gameScene = dynamic_cast<Game*>(this->getParent());
    
    schedule(schedule_selector(BallLayer::addBall), step);
}

void BallLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeCustomEventListeners("touch pad");
    _eventDispatcher->removeCustomEventListeners("cover return");
}

void BallLayer::addBall(float dt)
{
    auto actionDrop = MoveBy::create(race, Vec2(0, -visibleSize.height));
    
    int rd_c = rand()%3;
    int rd_l = rand()%3;
    
    if (last_c_l != -1)
    {
        while (rd_c == last_c_l / 10 || rd_l == last_c_l % 10)
        {
            rd_c = rand()%3;
            rd_l = rand()%3;
        }
    }
    
    auto ball = Sprite::createWithSpriteFrameName(StringUtils::format("ball_%d.png", rd_c));
    ball->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    ball->setTag(rd_c * 10 + rd_l);
    last_c_l = rd_c * 10 + rd_l;
    float bar_w = visibleSize.width/3;
    ball->setPosition(bar_w/2 + bar_w * rd_l, visibleSize.height + ball->getContentSize().height/2);
    ball->runAction(Sequence::create(actionDrop, CallFunc::create([ball, this]()
                                                                  {
                                                                      ball->removeFromParent();
                                                                      balls->eraseObject(ball);
                                                                      if (!isOver) {
                                                                          this->gameOver();
                                                                      }
                                                                  }),NULL));
    addChild(ball, 1);
    balls->pushBack(ball);
    
    auto ball_sd = Sprite::createWithSpriteFrameName("ball_sd.png");
    ball_sd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    ball_sd->setPosition(ball->getPosition() + Vec2(4, -6));
    ball_sd->runAction(Sequence::create(actionDrop->clone(), CallFunc::create([ball_sd]()
                                                                     {
                                                                         ball_sd->removeFromParent();
                                                                         balls_sd->eraseObject(ball_sd);
                                                                     }), NULL));
    addChild(ball_sd, 0);
    balls_sd->pushBack(ball_sd);
}

int BallLayer::checkTouch(int idx)
{
    if (!balls->empty()) {
        auto ball = balls->at(0);
        auto ball_sd = balls_sd->at(0);
        
        int c_ball = ball->getTag() / 10;
        if (c_ball == idx)
        {
            ball->stopAllActions();
            ball_sd->stopAllActions();
            
            balls->eraseObject(ball);
            balls_sd->eraseObject(ball_sd);
            
            // when balls be touched correctly, they rotate twice
            float rotateDua = 0.25;
            auto rotateby = RotateBy::create(rotateDua, Vec3(0, 90, 0));
            auto ac_ball =Sequence::create(rotateby,
                                           CallFunc::create([ball]()
                                                            {
                                                                ball->setTexture("star.png");
                                                                ball->setOpacity(120);
                                                            }),
                                           rotateby->clone(),
                                           MoveBy::create(0.5, Vec2(2, -3)),
                                           MoveBy::create(6, Vec2(6, 1136)),
                                           CallFunc::create([ball]()
                                                            {
//                                                                EventCustom e("turn_star");
//                                                                e.setUserData(ball);
//                                                                _eventDispatcher->dispatchEvent(&e);
                                                                ball->removeFromParent();
                                                            }), NULL);
            
            auto ac_ball_sd = Sequence::create(rotateby->clone(),
                                               CallFunc::create([ball_sd]()
                                                                {
                                                                    ball_sd->setTexture("star.png");
                                                                    ball_sd->setOpacity(40);
                                                                }),
                                               rotateby->clone(),
                                               Spawn::create(FadeOut::create(0.5), MoveBy::create(0.5, Vec2(-2, 3)), NULL),
                                               CallFunc::create([ball_sd]()
                                                                {
                                                                    ball_sd->removeFromParent();
                                                                }), NULL);
            
            ball->runAction(ac_ball);
            ball_sd->runAction(ac_ball_sd);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 2;
}

void BallLayer::gameOver()
{
    _gameScene->gameOverPrepare();
}

void BallLayer::updateRace()
{
    log("%f", step);
    if (step > 0.6)
    {
        step *= 0.8;
    }
    else if (step > 0.5)
    {
        step *= 0.9;
    }
    else if (step > 0.4)
    {
        step *= 0.94;
    }
    
    if (race > 4)
    {
        race *= 0.8;
    }
    else if (race > 3)
    {
        race *= 0.85;
    }
    else if (race > 2)
    {
        race *= 0.9;
    }
    else if (race > 1)
    {
        race *= 0.95;
    }
    
    if (isScheduled(schedule_selector(BallLayer::addBall)))
    {
        unschedule(schedule_selector(BallLayer::addBall));
        schedule(schedule_selector(BallLayer::addBall), step);
    }
}

void BallLayer::removing(Action* action)
{
    isOver = true;
    
    unschedule(schedule_selector(BallLayer::addBall));
    
    this->runAction(action);
    
//    for (auto ball : *balls)
//    {
//        float offset = ball->getPosition().y + ball->getContentSize().height/2;
//        ball->stopAllActions();
//        ball->runAction(MoveBy::create(2.0 * offset / visibleSize.height, Vec2(0, -offset)));
//    }
//    
//    for (auto ball_sd : *balls_sd)
//    {
//        float offset = ball_sd->getPosition().y + ball_sd->getContentSize().height/2;
//        ball_sd->stopAllActions();
//        ball_sd->runAction(MoveBy::create(2.0 * offset / visibleSize.height, Vec2(0, -offset)));
//    }
}