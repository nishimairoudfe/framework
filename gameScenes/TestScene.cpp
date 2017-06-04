//
//  TestScene.cpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/5.
//
//


#include "TestScene.h"
#include "gameLog.h"

USING_GAME_FRAMEWORK;

cocos2d::Scene* TestScene::createScene()
{
    auto layer = TestScene::create();
    auto scn = cocos2d::Scene::create();
    scn->addChild(layer,0);
    
    return scn;
}

bool TestScene::init()
{
    if(!Layer::init()){
        return false;
    }
    
    auto gamelog = gameLog::getInstance();
    //测试代码在此
    gamelog->cleanAllLog();
    gamelog->logDebug("Hello world");
    //gamelog->logError("Failed to load Sprite xxx.png.");
    //gamelog->logError("Failed to load Sprite xxx.png.");
    //gamelog->logError("Failed to load Sprite xxx.png.");
    //gamelog->logError("Failed to load Sprite xxx.png.");
    
    auto text = gamelog->getErrorLogString();
    cocos2d::log("%s\n",text.c_str());
    
    return true;
}

void TestScene::onEnter()
{
    cocos2d::Layer::onEnter();
}

void TestScene::onExit()
{
    cocos2d::Layer::onExit();
}
