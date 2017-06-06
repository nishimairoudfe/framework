//
//  UIBase.hpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/6.
//
//  所有UI元素的基类

#ifndef UIBase_h
#define UIBase_h

#include "gMacros.h"
#include "cocos2d.h"

NAMESPACE_BEGIN

class UIBase:public cocos2d::Node
{
public:
    CREATE_FUNC(UIBase);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
};

NAMESPACE_END


#endif /* UIBase_h */
