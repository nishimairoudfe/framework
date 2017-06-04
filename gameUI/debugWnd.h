//
//  debugWnd.h
//  gameframework
//
//  Created by 杨吉 on 2017/6/4.
//
//

//  Description  这个类是用来输出文件中的log信息的，这个窗口具有过滤的搜索功能，支持正则表达式的搜索方式，方便我们定位问题

#ifndef debugWnd_h
#define debugWnd_h
#include "gMacros.h"
#include "cocos2d.h"

NAMESPACE_BEGIN

class DebugWnd:public cocos2d::Layer
{
public:
    CREATE_FUNC(DebugWnd);
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    /**
     @description  显示debug窗口
     */
    void show();
    /**
     @description  隐藏debug窗口
     */
    void hide();
    
    /**
     @description  清空debug窗口
     */
    void clear();
protected:
    char *_begin;//指向待显示文件的开始处
    char *_end;//指向待显示文件的结尾处
    std::size_t _dataSize;//待显示文件的字节大小
    
};
NAMESPACE_END

#endif /* debugWnd_h */
