//
//  gameObject.hpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/6.
//
//  游戏中的所有具有逻辑的对象

#ifndef gameObject_h
#define gameObject_h

#include "gMacros.h"
#include "cocos2d.h"

NAMESPACE_BEGIN

class gameObject:public cocos2d::Node
{
public:
    CREATE_FUNC(gameObject);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
};

NAMESPACE_END


#endif /* gameObject_h */
