//
//  EnterScene.cpp
//  ColorMarch
//
//  Created by zhagqn on 11/3/14.
//
//

#include "EnterScene.h"
#include "BGLayer.h"
#include "StartButtonLayer.h"
#include "YoyoLayer.h"
#include "StartScoreLayer.h"
#include "GameScene.h"
#include "BGLayer.h"
#include "RecordLayer.h"
#include "CoverLayer.h"

StartButtonLayer* btnLayer;
YoyoLayer* yoyoLayer;
StartScoreLayer* startScoreLayer;
BGLayer* background;
bool showRecord;

Enter::Enter()
{
    btnLayer = NULL;
    yoyoLayer = NULL;
    startScoreLayer = NULL;
    background = NULL;
    showRecord = false;
}

Enter::~Enter()
{
    
}

Scene* Enter::createScene()
{
    auto s = Scene::create();
    auto l = Enter::create();
    
    s->addChild(l);
    return s;
}

void Enter::onEnter()
{
    Layer::onEnter();
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Schnappi_slow.mp3", 1);
    
    
    auto recordLayerListener = EventListenerCustom::create("show record", [this](EventCustom *e)
                                                           {
                                                               if (!showRecord) {
                                                                   auto recordLayer = RecordLayer::create(0);
                                                                   recordLayer->setTag(9999);
                                                                   this->addChild(recordLayer);
                                                                   showRecord = true;
                                                               } else {
                                                                   this->removeChildByTag(9999);
                                                                   showRecord = false;
                                                               }
                                                
                                                           });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(recordLayerListener, this);

    background = BGLayer::create(0);
    addChild(background);
    
    btnLayer = StartButtonLayer::create();
    addChild(btnLayer);
    
    yoyoLayer = YoyoLayer::create();
    addChild(yoyoLayer);
    
    startScoreLayer = StartScoreLayer::create();
    addChild(startScoreLayer);
}

void Enter::startGamePrepare()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
//    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fast.mp3");
    yoyoLayer->removingPrepare();
    btnLayer->removingPrepare();
    startScoreLayer->removingPrepare();
    background->appearing();
    this->scheduleOnce(schedule_selector(Enter::startGame), 1);
}

void Enter::startGame(float dt)
{
    Director::getInstance()->replaceScene(Game::createScene());
}

void Enter::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeCustomEventListeners("game over");
}