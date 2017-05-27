#ifndef DRAGONBONES_BASE_OBJECT_H
#define DRAGONBONES_BASE_OBJECT_H

#include "DragonBones.h"

//让我见识了真正的大师级套路，每个类的hashcode其实就是一个整数索引罢了，难道在我们手动创建一个类的时候还要自己去加一下hashcode的数量吗？目前看来是这样的，我们自己加就可以了。这个宏的目的就是返回hashcode。
#define BIND_CLASS_TYPE(CLASS) \
public:\
static std::size_t getTypeIndex()\
{\
    static const auto typeIndex = typeid(CLASS).hash_code();\
    return typeIndex;\
}\
virtual std::size_t getClassTypeIndex() const override\
{\
    return CLASS::getTypeIndex();\
}\

DRAGONBONES_NAMESPACE_BEGIN//命名空间的开始

class BaseObject
{
private:
    static std::size_t _hashCode;//哈希码
    static std::size_t _defaultMaxCount;//每种类类型的对象的最大数量
    static std::map<std::size_t, std::size_t> _maxCountMap;//前者是类的标志符，后者是这个类的对象的个数
    static std::map<std::size_t, std::vector<BaseObject*>> _poolsMap;//前者是类的标志符，后者是保存于这个标志符对应的类的对象的一个池

    static void _returnObject(BaseObject *object);//目前还不知道这个是何作用，不过看样子应该是属于内存管理的东西

public:
    static void setMaxCount(std::size_t classTypeIndex, std::size_t maxCount);//设置classtypeindex对应的类的对象的最大数量
    static void clearPool(std::size_t classTypeIndex);//根据输入的类的标志符，清空这个类类型的池中的所有对象

    template<typename T>//模版函数的精妙用法：编译器多态让我们免去了自己写代码时的运行期多态的书写，very good！这种套路要学者点啊。
    static T* borrowObject() //从这个名字我们就知道这个函数的目的就是从池子里面拿一个对象出来用
    {
        const auto classTypeIndex = T::getTypeIndex();//返回这个类的hashcode标记
        const auto iterator = _poolsMap.find(classTypeIndex);//返回的是一个pair的迭代器，迭代器的类型应该是std::map<std::size_t,std::vector<BaseObject*>>::iterator.
        if (iterator != _poolsMap.end())//如果iterator不是_poolsMap.end()说明我们确实找到了这个索引对应的对象池
        {
            auto& pool = iterator->second;//这个池子就是iterator的second元素，它是一个std::vector<BaseObject*>
            if (!pool.empty())//虽然我们找到了这个池子，但是如果这个池子不是空的
            {
                const auto object = dynamic_cast<T*>(pool.back());//我们就从这个池子里面取出一个对象的引用
                pool.pop_back();//将池子的大小减少1，调用pop_back()不会调用这个被pop对象的析构函数吗？

                return object;//返回取出的这个对象
            }
        }

        return new (std::nothrow) T();//如果按照这个类的索引并没有查找到对应的池子，那么我们可以直接简单的创建一个对象并返回它，也就是说这个对象并没有经过内存管理就放出去了，这是不是很危险的呢？
    }

public:
    const std::size_t hashCode;//每个对象都有自己的hashcode

public:
    /** @private */
    BaseObject();
    /** @private */
    virtual ~BaseObject() = 0;

protected:
    virtual void _onClear() = 0;//不知道拿来干嘛

public:
    /** @private */
    virtual std::size_t getClassTypeIndex() const = 0;//获取这个类的hashcode
    
    void returnToPool();//返回给池
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_BASE_OBJECT_H
