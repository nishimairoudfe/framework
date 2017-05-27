#include "BaseObject.h"
DRAGONBONES_NAMESPACE_BEGIN

std::size_t BaseObject::_hashCode = 0;//基类的hashcode是0，貌似没有什么问题
std::size_t BaseObject::_defaultMaxCount = 5000;//默认的最大数量
std::map<std::size_t, std::size_t> BaseObject::_maxCountMap;//每个类类型的对象的最大数量
std::map<std::size_t, std::vector<BaseObject*>> BaseObject::_poolsMap;//初始化对象池的集合为空，对象池的好处就是初始化的次数比较少，需要的时候拿出来用，不需要的时候直接还回去就行了

void BaseObject::_returnObject(BaseObject* object)//这个就是返回对象的函数了，当然他和我们的borrowObject是对应的。但是这种设计确实非常棒的。什么设计呢？如何让returnObject自动调用呢？这是个问题
{
    const auto classTypeIndex = object->getClassTypeIndex();//我们首先将这个对象的hashcode拿到手
    const auto maxCountIterator = _maxCountMap.find(classTypeIndex);//查询与这种hashcode相匹配的种类的对象的最大数量
    const auto maxCount = maxCountIterator != _maxCountMap.end() ? maxCountIterator->second : _defaultMaxCount;//如果与这个在maxCountMap都没有找到与这个hashcode相对应的信息，就返回_defaultMaxCount，否则返回查到的最大数量信息

    const auto iterator = _poolsMap.find(classTypeIndex);//找到装这个对象的池子
    if (iterator != _poolsMap.end())
    {
        auto& pool = iterator->second;//找到的话，取得这个池子
        if (pool.size() >= maxCount) {//如果池子的尺寸已经超过最大容量了
            delete object;//删除这个对象就可以了
            return;
        }

        if (std::find(pool.cbegin(), pool.cend(), object) == pool.cend())
        {
            pool.push_back(object);//如果池子里面有空的位置且这个对象并没有在池子中出现，那么将这个对象加入这个池子里
        }
        else
        {
            DRAGONBONES_ASSERT(false, "The object aleady in pool.");//如果对象已经在池子里，则终止程序的运行
        }
    }
    else
    {
        delete object;//如果没有找到装这种对象的池子，那么直接将这个对象释放掉就可以了
    }
}

void BaseObject::setMaxCount(std::size_t classTypeIndex, std::size_t maxCount)//设置某种对象池的最大容量
{
    if (classTypeIndex)//如果待设置对象不是基类对象
    {
        _maxCountMap[classTypeIndex] = maxCount;//设置容纳这种对象的池子的最大容量为maxCount
        const auto iterator = _poolsMap.find(classTypeIndex);//在池子集中寻找这种对象的池子
        if (iterator != _poolsMap.end())
        {
            auto& pool = iterator->second;//找到的话那么久取得这个池子
            if (pool.size() > maxCount)//如果池子的容量已经超过了设置的最大容量
            {
                for (auto i = maxCount, l = pool.size(); i < l; ++i)
                {
                    delete pool[i];//那么就将超出的对象释放掉
                }

                pool.resize(maxCount);//重新设置vector的大小，这个是严格的大小，capacity也是这里的maxCount
            }
        }
    }
    else
    {
        _defaultMaxCount = maxCount;
        for (auto& pair : _poolsMap)
        {
            if (_maxCountMap.find(pair.first) == _maxCountMap.end())
            {
                continue;
            }

            _maxCountMap[pair.first] = maxCount;

            auto& pool = pair.second;
            if (pool.size() > maxCount)
            {
                for (auto i = maxCount, l = pool.size(); i < l; ++i)
                {
                    delete pool[i];
                }

                pool.resize(maxCount);
            }
        }
    }
}

void BaseObject::clearPool(std::size_t classTypeIndex)
{
    if (classTypeIndex)
    {
        const auto iterator = _poolsMap.find(classTypeIndex);
        if (iterator != _poolsMap.end())
        {
            auto& pool = iterator->second;
            if (!pool.empty())
            {
                for (auto object : pool)
                {
                    delete object;
                }

                pool.clear();
            }
        }
    }
    else
    {
        for (auto& pair : _poolsMap)
        {
            auto& pool = pair.second;
            if (!pool.empty())
            {
                for (auto object : pool)
                {
                    delete object;
                }

                pool.clear();
            }
        }
    }
}

BaseObject::BaseObject() ://对于这里的这一手，我只能说是神来之笔
    hashCode(BaseObject::_hashCode++)
{}
BaseObject::~BaseObject(){}

void BaseObject::returnToPool()
{
    _onClear();
    _returnObject(this);
}

DRAGONBONES_NAMESPACE_END
