//
//  DragonBonesTest.h
//  geeframework
//
//  Created by 杨吉 on 2017/5/24.
//
//

#ifndef DragonBonesTest_h
#define DragonBonesTest_h
#include "cocos2d.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"



class DragonBonesTest:public cocos2d::Layer
{
public:
    CREATE_FUNC(DragonBonesTest);
    
    virtual void onEnter();
    virtual void onExit();
    /**
     @description 初始化函数
     */
    virtual bool init();
    /**
     @description 创建一个龙骨的测试场景
     */
    static cocos2d::Scene* createTestScene();
    
    /**
     @description 更改当前加载进来的骨架
     */
    void changeArmature();
    /**
     @description 更改当前骨架上的动画
     */
    void changeAnimation();
    
    
    
private:
    dragonBones::CCFactory _factory;
    dragonBones::DragonBonesData* _bonesData;
    dragonBones::Armature* _armature;
    dragonBones::CCArmatureDisplay* _armatureDisplay;
    
    std::size_t  _armatureIndex;
    std::size_t  _animationIndex;
};

#endif /* DragonBonesTest_h */
