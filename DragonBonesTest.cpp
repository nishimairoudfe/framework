//
//  DragonBonesTest.cpp
//  geeframework
//
//  Created by 杨吉 on 2017/5/24.
//
//

#include "DragonBonesTest.h"

USING_NS_CC;

bool DragonBonesTest::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}

Scene* DragonBonesTest::createTestScene()
{
    auto layer = DragonBonesTest::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    
    return scene;
}
