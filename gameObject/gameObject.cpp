//
//  gameObject.cpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/6.
//
//

#include "gameObject.h"

USING_GAME_FRAMEWORK;

bool gameObject::init()
{
    if (!cocos2d::Node::init()) {
        return false;
    }
    
    return true;
}
