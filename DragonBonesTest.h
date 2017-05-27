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

class DragonBonesTest:public cocos2d::Layer
{
public:
    /**
     @description 初始化函数
     */
    virtual bool init();
    /**
     @description 创建一个龙骨的测试场景
     */
    static cocos2d::Scene* createTestScene();
};

#endif /* DragonBonesTest_h */
