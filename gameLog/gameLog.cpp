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
    std::ofstream file(_errorlogpath,std::ios::app);
    if (file) {
        file<<"(ERROR)"<<__FILE__<<":"<<__LINE__<<":"<<msg<<std::endl;
        file.close();
    }
    else{
        cocos2d::log("%s","Failed to init gamelog!");
    }
    
}

void gameLog::logDebug(const char* msg) const
{
    std::ofstream file(_debuglogpath,std::ios::app);
    if (file) {
        file<<"(DEBUG)"<<msg<<std::endl;
        file.close();
    }
    else{
        cocos2d::log("%s","Failed to init gamelog!");
    }
}

void gameLog::cleanErrorLog() const
{
    std::ofstream file(_errorlogpath);
    if (file) {
        file.close();
    }
    else{
        cocos2d::log("%s","Failed to clean error log.");
    }
}

void gameLog::cleanDebugLog() const
{
    std::ofstream file(_debuglogpath);
    if (file) {
        file.close();
    }
    else{
        cocos2d::log("%s","Failed to clean debug log.");
    }
}

void gameLog::cleanAllLog() const
{
    cleanErrorLog();
    cleanDebugLog();
}

std::string gameLog::getErrorLogString() const
{
    auto result = cocos2d::FileUtils::getInstance()->getStringFromFile(_errorlogpath);
    return std::move(result);
}

std::string gameLog::getDebugLogString() const
{
    auto result = cocos2d::FileUtils::getInstance()->getStringFromFile(_debuglogpath);
    return std::move(result);
}
