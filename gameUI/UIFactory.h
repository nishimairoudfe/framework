//
//  UIFactory.hpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/6.
//
//

#ifndef UIFactory_h
#define UIFactory_h

#include "UIBase.h"

class UIData;

NAMESPACE_BEGIN

class UIFactory
{
public:
    /**
     @description   从文件中加载UI信息
     @param         filepath保存的是UI文件的路径
     */
    UIData *loadUIFromFile(std::string &filepath) const;
};

NAMESPACE_END
#endif /* UIFactory_h */
