//
//  UIBase.cpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/6.
//
//

#include "UIBase.h"

USING_GAME_FRAMEWORK;

bool UIBase::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

void UIBase::onEnter()
{
    Node::onEnter();
}

void UIBase::onExit()
{
    Node::onExit();
}
