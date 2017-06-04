//
//  TestScene.h
//  gameframework
//
//  Created by 杨吉 on 2017/6/5.
//
//

#ifndef TestScene_h
#define TestScene_h

#include "cocos2d.h"
#include "gMacros.h"

NAMESPACE_BEGIN

class TestScene:public cocos2d::Layer
{
public:
    CREATE_FUNC(TestScene);
    virtual bool init();
    static cocos2d::Scene* createScene();
    
    virtual void onEnter();
    virtual void onExit();
};

NAMESPACE_END
#endif /* TestScene_h */
