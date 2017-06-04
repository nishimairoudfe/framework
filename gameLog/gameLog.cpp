//
//  gameLog.cpp
//  gameframework
//
//  Created by 杨吉 on 2017/6/4.
//
//

#include "gameLog.h"
#include <string>
#include <fstream>

USING_GAME_FRAMEWORK;

gameLog* gameLog::_instance = nullptr;

gameLog::gameLog()
{
    auto writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    _errorlogpath = writablePath + "errorlog";
    _debuglogpath = writablePath + "debuglog";
}

gameLog::~gameLog()
{
    if (_instance) {
        delete _instance;
    }
    
    _instance = nullptr;
}

void gameLog::release()
{
    if (_instance) {
        delete _instance;
    }
    
    _instance = nullptr;
}

gameLog* gameLog::getInstance()
{
    if (_instance == nullptr) {
        _instance = new gameLog();
    }
    
    return _instance;
}

void gameLog::logError(const char* msg) const
{
    std::ofstream file(_errorlogpath);
    if (file) {
        file<<__FILE__<<":"<<__LINE__<<":"<<msg<<std::endl;
    }
    else{
        cocos2d::log("%s","Failed to init gamelog!");
    }
    
}


