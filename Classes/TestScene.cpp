//
//  TestScene.cpp
//  ColorMarch
//
//  Created by zhagqn on 11/10/14.
//
//

#include "TestScene.h"
#include "YoyoLayer.h"
#include "StartButtonLayer.h"

Scene* Test::createScene()
{
    auto s = Scene::create();
    auto l = Test::create();
    s->addChild(l);
    
    return s;
}

bool Test::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto yoyo = StartButtonLayer::create();
    addChild(yoyo);
    
    return true;
}