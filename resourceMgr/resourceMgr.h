//
//  resourceMgr.hpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/6.
//
//  管理游戏中所有的资源，比如动画，图片，声音，特效

#ifndef resourceMgr_h
#define resourceMgr_h

#include "cocos2d.h"
#include "DragonBonesHeaders.h"
#include <vector>
#include <string>
#include "tinyxml2/tinyxml2.h"

class ResourceMgr
{
    /**
     @description   这个类用于异步加载资源，同时通过外部的配置信息，快速的创建游戏中会用到的图片，声音，特效以及动画资源。所以，大部分的API都得根据这个要求来设计,我们使用这个类可以更方便的使用资源。资源的存储方式包括它的名字以及所在路径，我们会从文件中生成一个超级大的singleton对象，像使用ANDROID中的R类一样简单的调用资源。
     */
private:
    static ResourceMgr* _instance;
    ResourceMgr();
public:
    ~ResourceMgr();
    void release();
    

    /**
     @description   异步加载一张图集
     */
    void loadSpriteFrameAnsy(std::string& filepath) const;
    /**
     @description   异步加载一系列图集
     */
    void loadSpriteFramesAnsy(std::vector<std::string> &filepaths) const;
};

#endif /* resourceMgr_h */
