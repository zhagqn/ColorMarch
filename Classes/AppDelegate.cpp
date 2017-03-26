#include "AppDelegate.h"
#include "GameScene.h"
#include "EnterScene.h"
#include "TestScene.h"

using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::FIXED_WIDTH);
    
    director->setProjection(cocos2d::DisplayLinkDirector::Projection::_2D);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cm.plist");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Schnappi_slow.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Schnappi.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("slow.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("fast.mp3");
    
    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = Enter::createScene();

    // run
    director->runWithScene(scene);

//    auto scene = Test::createScene();
//    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
