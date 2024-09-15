#include <iostream>
#include <string>
#include <vector>

/* 定义一个桶结构体，用于存储键值对 */
struct Bucket
{
    int key; // 键
    int val; // 值
    // 构造函数，初始化键和值
    Bucket(int a, int b) : key(a), val(b) {}
};

/*  定义一个基于数组实现的哈希映射类 */
class ArrayHashMap
{
private:
    std::vector<Bucket *> buckets; // 存储桶指针的数组
    int mapSize;                   // 当前映射中元素的数量
    int mapCapacity;               // 映射的最大容量
    int hash(int key);             // 计算哈希值的函数
    int hashFunc(int key);         // 基于哈希值计算索引的函数

public:
    ArrayHashMap(int capacity); // 构造函数
    ~ArrayHashMap();            // 析构函数
    int size();                 // 获取当前映射中元素的数量
    int capacity();             // 获取映射的容量
    void push(Bucket *bucket);  // 添加新的键值对
    int get(int key);           // 获取指定键对应的值
    int operator[](int key);    // 重载操作符，通过键获取值
};

/* 构造函数，初始化容量和大小，创建空的桶数组 */
ArrayHashMap::ArrayHashMap(int capacity) : buckets(std::vector<Bucket *>(capacity)), mapCapacity(capacity), mapSize(0)
{
}

/*  析构函数，释放桶数组中的内存并清空数组 */
ArrayHashMap::~ArrayHashMap()
{
    for (const auto &bucket : buckets)
    {
        delete bucket; // 释放每个桶的内存
    }
    buckets.clear(); // 清空数组
}

/* 返回当前映射中的元素数量 */
int ArrayHashMap::size()
{
    return mapSize;
}

/* 返回映射的容量 */
int ArrayHashMap::capacity()
{
    return mapCapacity;
}

/* 简单的哈希函数，直接返回键本身 */
int ArrayHashMap::hash(int key)
{
    return key;
}

/* 基于哈希值计算索引，使用模运算确保索引在有效范围内 */
int ArrayHashMap::hashFunc(int key)
{
    return hash(key) % capacity();
}

/* 向映射中添加新的键值对 */
void ArrayHashMap::push(Bucket *bucket)
{
    // 如果映射已满，则直接返回
    if (size() == capacity())
        return;
    // 将新的键值对插入到下一个空位置
    buckets[size()] = bucket;
    mapSize++; // 更新元素数量
}

/* 通过键获取对应的值，使用哈希函数计算索引 */
int ArrayHashMap::get(int key)
{
    return buckets[hashFunc(key)]->val;
}

/* 重载[]操作符，允许通过键直接访问值 */
int ArrayHashMap::operator[](int key)
{
    return buckets[hashFunc(key)]->val;
}

int main()
{
    ArrayHashMap ahm(10);     // 创建一个容量为10的哈希映射
    int cap = ahm.capacity(); // 获取映射的容量
    Bucket *temp = nullptr;   // 临时指针，用于创建桶
    /* 插入若干键值对，键从100开始 */
    for (int i = 0 + 100; i < cap + 100; i++)
    {
        temp = new Bucket(i, (i - 100)); // 创建新的键值对
        ahm.push(temp);                  // 将键值对插入到哈希映射中
    }
    int size = ahm.size(); // 获取映射中的元素数量
    /* 输出每个键对应的值 */
    for (int i = 0 + 100; i < size + 100; i++)
    {
        std::cout << ahm.get(i) << " "; // 打印键对应的值
    }
    std::cout << std::endl;

    /* 输出键为108和107对应的值 */
    std::cout << ahm.get(100 + 8) << std::endl;
    std::cout << ahm[100 + 7] << std::endl;
    return 0;
}