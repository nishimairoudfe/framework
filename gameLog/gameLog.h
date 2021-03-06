//
//  gameLog.h
//  gameframework
//
//  Created by 杨吉 on 2017/6/4.
//
//

#ifndef gameLog_h
#define gameLog_h

#include "gMacros.h"
#include "cocos2d.h"


NAMESPACE_BEGIN
class  gameLog
{
private:
    static gameLog* _instance;
    std::string _errorlogpath;//errorlog文件的路径
    std::string _debuglogpath;//debuglog文件的路径
    
    gameLog();
public:
    ~gameLog();
    void release();
    
    static gameLog* getInstance();
    
    
    /**
     @description  输出error日志
     */
    
    void logError(const char *msg) const;
    /**
     @description  输出debug日志
     */
    
    void logDebug(const char* msg) const;
    
    /**
     @description  清空error日志
     */
    void cleanErrorLog() const;
    
    /**
     @description  清空debug日志
     */
    void cleanDebugLog() const;
    
    /**
     @description  清空所有日志
     */
    
    void cleanAllLog() const;
    
    /**
     @description  获取errorlog中的内容
     */
    std::string getErrorLogString() const;
    
    /**
     @description  获取debuglog中的内容
     */
    std::string getDebugLogString() const;
};

NAMESPACE_END
#endif /* gameLog_h */
