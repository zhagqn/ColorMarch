//
//  GameScene.cpp
//  ColorMarch
//
//  Created by zhagqn on 10/28/14.
//
//

#include "GameScene.h"
#include "PadLayer.h"
#include "BGLayer.h"
#include "BallLayer.h"
#include "ScoreLayer.h"
#include "EnterScene.h"
#include "EnterScene.h"
#include "RecordLayer.h"
#include "NewRecordLayer.h"
#include "CoverLayer.h"


PadLayer* padLayer;
BallLayer* ballLayer;
ScoreLayer* scoreLayer;


Scene* Game::createScene()
{
    auto scene = Scene::create();
    auto layer = Game::create();
    
    scene->addChild(layer);
    return scene;
}

void Game::onEnter()
{
    Layer::onEnter();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Schnappi.mp3", 1);
    
    isFirst = UserDefault::getInstance()->getBoolForKey("isFirst", true);
    if (isFirst) {
        scheduleOnce(schedule_selector(Game::addCover), 1.5);
        UserDefault::getInstance()->setBoolForKey("isFirst", false);
    }
    
    score = 0;
    
    bgLayer = BGLayer::create(1);
    
    addChild(bgLayer, 0);
    
    padLayer = PadLayer::create();
    
    addChild(padLayer, 2);
    
    pauseLayer = PauseLayer::create();
    addChild(pauseLayer, 2);
    
    ballLayer = BallLayer::create();
    
    addChild(ballLayer, 1);
    
    scoreLayer = ScoreLayer::create();
    
    addChild(scoreLayer, 0);

    
    auto pauseListener = EventListenerCustom::create("pause game", [this](EventCustom *e)
    {
        Director::getInstance()->pause();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pauseListener, this);
    
    auto homeListener = EventListenerCustom::create("home game", [this](EventCustom *e)
                                                     {
                                                         Director::getInstance()->replaceScene(Enter::createScene());
                                                     });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(homeListener, this);
    
    auto reloadListener = EventListenerCustom::create("reload game", [this](EventCustom *e)
                                                    {
                                                        Director::getInstance()->replaceScene(Game::createScene());
                                                    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(reloadListener, this);
    
    auto resumeListener = EventListenerCustom::create("resume game", [this](EventCustom *e)
                                                      {
                                                          CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
                                                          Director::getInstance()->resume();
                                                      });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(resumeListener, this);
    
    auto checkListener = EventListenerCustom::create("touch check", [this](EventCustom *e)
                                                     {
                                                         int re = *(int*)(e->getUserData());
                                                         this->checkTouch(re);
                                                     });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(checkListener, this);
}

void Game::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeCustomEventListeners("touch check");
    _eventDispatcher->removeCustomEventListeners("pause game");
    _eventDispatcher->removeCustomEventListeners("home game");
    _eventDispatcher->removeCustomEventListeners("reload game");
    _eventDispatcher->removeCustomEventListeners("resume game");
    _eventDispatcher->removeCustomEventListeners("game over");
}

void Game::checkTouch(int idx)
{
    switch (idx)
    {
        case 0:
            gameOverPrepare();
            break;
        case 1:
            updateScore();
            break;
        default:
            break;
    }
}

void Game::updateScore()
{
    score = scoreLayer->updateScore();
    if (score % 10 == 0)
    {
        ballLayer->updateRace();
    }
}

std::string recordNames[8];
int record_scores[8];

void Game::gameOverPrepare()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("slow.mp3");
    int best = UserDefault::getInstance()->getIntegerForKey("best_score");
    UserDefault::getInstance()->setIntegerForKey("last_score", score);
    if (score > best)
    {
        best = score;
        UserDefault::getInstance()->setIntegerForKey("best_score", score);
    }
    
    auto action = EaseIn::create(MoveBy::create(0.7, Vec2(0, -Director::getInstance()->getVisibleSize().height)), 1);
    
    bgLayer->removing(action->clone());
    scoreLayer->removing(action->clone());
    padLayer->removing(action->clone());
    ballLayer->removing(action->clone());
    
    for (int i=0; i<8; i++)
    {
        auto record = UserDefault::getInstance()->getStringForKey(StringUtils::format("%d_record_name", i).c_str(), "player");
        recordNames[i] = record;
    }
    
    for (int i=0; i<8; i++)
    {
        auto record = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%d_record", i).c_str(), 0);
        record_scores[i] = record;
    }
    
    recordBreaking = -1;
    for (int i=0; i<8; i++)
    {
        if (score>record_scores[i])
        {
            recordBreaking = i;
            log("%d", i);
            break;
        }
    }
    
    scheduleOnce(schedule_selector(Game::gameOver), .5);
}

std::string *newRecordName;

void Game::gameOver(float dt)
{
    removeChild(pauseLayer);
    auto newRL = NewRecordLayer::create();
    auto RL = RecordLayer::create(1);
    if (recordBreaking == -1)
    {
        addChild(RL);
    } else
    {
        addChild(RL);
        addChild(newRL);
    }
    
    auto gameOver_listener = EventListenerCustom::create("game over", [this, newRL,RL](EventCustom* e)
    {
        if (recordBreaking != -1) {
            if ( e->getUserData()!=nullptr) {
                newRecordName = (std::string*)(e->getUserData());
                std::string s = *newRecordName;
                for (int i=7; i>recordBreaking; i--) {
                    record_scores[i] = record_scores[i-1];
                    recordNames[i] = recordNames[i-1];
                }
                recordNames[recordBreaking] = s;
                record_scores[recordBreaking] = score;
                for (int i=0; i<8; i++) {
                    UserDefault::getInstance()->setStringForKey(StringUtils::format("%d_record_name", i).c_str(), recordNames[i]);
                }
                
                for (int i=0; i<8; i++) {
                    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%d_record", i).c_str(), record_scores[i]);
                }
            }
            else
            {
                std::string s = "player";
                for (int i=7; i>recordBreaking; i--) {
                    record_scores[i] = record_scores[i-1];
                    recordNames[i] = recordNames[i-1];
                }
                recordNames[recordBreaking] = s;
                record_scores[recordBreaking] = score;
                for (int i=0; i<8; i++) {
                    UserDefault::getInstance()->setStringForKey(StringUtils::format("%d_record_name", i).c_str(), recordNames[i]);
                }
                
                for (int i=0; i<8; i++) {
                    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%d_record", i).c_str(), record_scores[i]);
                }
            }
            this->removeChild(newRL);
            this->removeChild(RL);
            this->addChild(RecordLayer::create(1));
            recordBreaking = -1;
        }
        else
        {
            Director::getInstance()->replaceScene(Enter::createScene());
        }
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(gameOver_listener, this);
//    Director::getInstance()->replaceScene(Enter::createScene());
}

void Game::addCover(float dt)
{
    EventCustom e("pause game");
    _eventDispatcher->dispatchEvent(&e);
    addChild(CoverLayer::create(), 999);
    _eventDispatcher->dispatchCustomEvent("cover return");
}
