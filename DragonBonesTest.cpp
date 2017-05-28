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
    
    _bonesData = nullptr;
    _armature = nullptr;
    _armatureDisplay = nullptr;
    
    _armatureIndex = 0;
    _animationIndex = 0;
    
    _bonesData = _factory.loadDragonBonesData("Animations/Sheep_Ani_ske.json");
    _factory.loadTextureAtlasData("Animations/Sheep_Ani_tex.json");
    
    if (_bonesData) {
        const auto& names = _bonesData->getArmatureNames();
        
        for (const auto& t : names) {
            auto name = Label::create();
            name->setString(t.c_str());
            name->setAlignment(cocos2d::TextHAlignment::CENTER);
            name->setSystemFontSize(50);
            addChild(name,1);
        }
    }
    else
    {
        assert(false);
    }
    
    //Rect rc = {1000,1000,2000,0};
    auto bg = Sprite::create("pictures/pic005.jpeg");
    addChild(bg,0);
    
    changeArmature();
    changeAnimation();
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [&](Touch* touch,Event* evt)->bool {
        auto touPoint = touch->getLocation();
        auto target = dynamic_cast<Sprite*>(evt->getCurrentTarget());
        auto size = target->getContentSize();
        Rect rc = {0,0,size.width,size.height};
        auto posInNode = target->convertToNodeSpace(touPoint);
        if (rc.containsPoint(posInNode)) {
            auto ac1 = ScaleTo::create(0.2,1.1);
            target->runAction(ac1);
            return true;
        }
        
        return false;
        
    };
    
    listener1->onTouchEnded = [&](Touch* t,Event *evt)->void {
        auto ac1 = ScaleTo::create(0.2,1.0);
        auto target = dynamic_cast<Sprite*>(evt->getCurrentTarget());
        target->runAction(ac1);
        this->changeAnimation();
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, bg);
    
    return true;
}

Scene* DragonBonesTest::createTestScene()
{
    auto layer = DragonBonesTest::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    
    return scene;
}

void DragonBonesTest::changeArmature()
{
    //首先我们必须要知道这个加载进来的bonedata里面是否有我们需要的骨架的数据
    const auto& armatureNames = _bonesData->getArmatureNames();
    if (armatureNames.empty()) {
        return;
    }
    
    //如果当前已经有骨架数据加载到armature里面，那么为了能够切换骨架数据，我们必须将之前的骨架数据释放掉，也就是将之前的骨架数据放到池子里面去
    if (_armature) {
        _armature->dispose();
        
        this->removeChild(_armatureDisplay);
    }
    
    //切换到下一个骨骼
    _armatureIndex++;
    if (_armatureIndex >= armatureNames.size()) {
        _armatureIndex = 0;
    }
    
    const auto& armatureName = armatureNames[_armatureIndex];
    
    _armatureDisplay = _factory.buildArmatureDisplay(armatureName);
    
    _armature = _armatureDisplay->getArmature();
    
    //add armature display
    auto size = Director::getInstance()->getVisibleSize();
    _armatureDisplay->setPosition(size.width*0.5,size.height*0.5);
    addChild(_armatureDisplay,2);
}

void DragonBonesTest::changeAnimation()
{
    const auto& animationNames = _armatureDisplay->getAnimation().getAnimationNames();
    if (animationNames.empty()) {
        return;
    }
    
    _animationIndex++;
    
    if (_animationIndex >= animationNames.size()) {
        _animationIndex = 0;
    }
    const auto& animationName = animationNames[_animationIndex];
    
    if (_armature) {
        _armature->getAnimation().play(animationName);
    }
}

void DragonBonesTest::onEnter()
{
    Layer::onEnter();
}

void DragonBonesTest::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    Layer::onExit();
}
