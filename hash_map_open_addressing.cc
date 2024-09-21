#include <iostream>
#include <vector>

struct Pair
{
    int key; // 键
    int val; // 值
    // 构造函数，接收键值对并进行初始化
    Pair(int _key, int _val) : key(_key), val(_val) {}
    // 析构函数，用于释放内存并在删除时输出信息
    ~Pair()
    {
        std::cout << "delete Pair! key: " << key << " val:" << val << std::endl;
    }
};

class HashMapOpenAddressing
{
private:
    std::vector<Pair *> buckets; // 用于存储键值对的桶
    int mapSize;                 // 哈希表中的元素数量
    int mapCapacity;             // 哈希表的容量
    int extendRatio;             // 容量扩展比例
    double loadThres;            // 负载因子阈值
    Pair *TOMBSTONE;             // 用于表示已删除元素的墓碑标记
    int hash(int key);           // 哈希函数，用于计算哈希值
    int hashFunc(int key);       // 计算哈希桶的索引
    double loadFactor();         // 计算负载因子

public:
    HashMapOpenAddressing(int capacity); // 构造函数
    ~HashMapOpenAddressing();            // 析构函数
    int size();                          // 返回哈希表中的元素数量
    int capacity();                      // 返回哈希表的容量
    void put(int key, int val);          // 插入或更新键值对
    int get(int key);                    // 根据键获取值
    void remove(int key);                // 根据键删除键值对
    void extendCapacity();               // 扩展容量
    void print();                        // 打印哈希表中的内容
    int findBucket(int key);             // 查找键所在的桶
};

// 构造函数，初始化哈希表
HashMapOpenAddressing::HashMapOpenAddressing(int capacity) : buckets(std::vector<Pair *>(capacity, nullptr)), mapSize(0), extendRatio(2), loadThres(2.0 / 3.0), mapCapacity(capacity), TOMBSTONE(new Pair(-1, -1))
{
}

// 析构函数，释放所有桶中的键值对并清理内存
HashMapOpenAddressing::~HashMapOpenAddressing()
{
    for (const auto &bucket : buckets)
    {
        if (bucket == TOMBSTONE) // 跳过墓碑
            continue;
        std::cout << "delete bucket!" << std::endl;
        delete bucket; // 删除实际存储的键值对
    }
    buckets.clear(); // 清空桶数组
    std::cout << "delete buckets finish!" << std::endl;
    if (TOMBSTONE != nullptr)
    {
        std::cout << "delete TOMBSTONE" << std::endl;
        delete TOMBSTONE; // 删除墓碑对象
        TOMBSTONE = nullptr;
    }
    std::cout << "delete TOMBSTONE finish!" << std::endl;
}

// 返回哈希表中的元素数量
int HashMapOpenAddressing::size()
{
    return mapSize;
}

// 返回哈希表的容量
int HashMapOpenAddressing::capacity()
{
    return mapCapacity;
}

// 简单哈希函数，返回输入键本身（可以根据需要改进）
int HashMapOpenAddressing::hash(int key)
{
    return key;
}

// 根据哈希值计算桶索引
int HashMapOpenAddressing::hashFunc(int key)
{
    return hash(key) % capacity();
}

// 计算负载因子（已存元素数量与总容量的比值）
double HashMapOpenAddressing::loadFactor()
{
    return (double)size() / (double)capacity();
}

// 扩展哈希表的容量并重新分配元素
void HashMapOpenAddressing::extendCapacity()
{
    std::cout << "extend capacity!" << std::endl;
    std::vector<Pair *> temp = buckets;                  // 临时保存当前桶
    mapCapacity *= extendRatio;                          // 扩大容量
    buckets = std::vector<Pair *>(mapCapacity, nullptr); // 创建新的桶数组

    int len = size();
    mapSize = 0;
    for (int i = 0; i < len; i++)
    {
        if (temp[i] == nullptr || temp[i] == TOMBSTONE)
            continue;
        /*
        以下方式不可行，原因：
        假设一个容量为3的数组：
           第一次key为2，第二次key为92，buckets[0]->key==92，buckets[2]->key==2
           调用remove(2)后，buckets[2]==TOMBSTONE
        */
        // if(temp[i]==TOMBSTONE)
        // {
        // buckets[i]=TOMBSTONE;
        // continue;
        // }
        std::cout << "copy Pair!  key: " << temp[i]->key << " val: " << temp[i]->val << std::endl;
        put(temp[i]->key, temp[i]->val); // 重新插入到新的桶中
        delete temp[i];                  // 删除原桶中的元素
    }
    temp.clear(); // 清空临时桶
}

// 查找键所在的桶索引，使用线性探测解决冲突
int HashMapOpenAddressing::findBucket(int key)
{
    int idx = hashFunc(key);
    int firstTombstone = -1, count = 0; // 记录第一个遇到的墓碑索引
    while (buckets[idx] != nullptr && count < capacity())
    {
        if (buckets[idx]->key == key) // 找到匹配的键
        {
            if (firstTombstone != -1)
            {
                // 若找到墓碑，则将该键值对移动到墓碑位置
                buckets[firstTombstone] = buckets[idx];
                buckets[idx] = TOMBSTONE;
                return firstTombstone;
            }
            return idx;
        }
        if (buckets[idx] == TOMBSTONE && firstTombstone == -1)
            firstTombstone = idx;     // 记录第一个墓碑位置
        idx = (idx + 1) % capacity(); // 线性探测下一个桶
        count++;
    }
    return firstTombstone == -1 ? idx : firstTombstone; // 返回空桶或墓碑索引
}

// 插入或更新键值对
void HashMapOpenAddressing::put(int key, int val)
{
    if (loadFactor() >= loadThres) // 检查是否需要扩展容量
        extendCapacity();
    int idx = findBucket(key);
    if (buckets[idx] != nullptr && buckets[idx] != TOMBSTONE)
    {
        buckets[idx]->val = val; // 更新现有值
        return;
    }
    buckets[idx] = new Pair(key, val); // 插入新键值对
    mapSize++;
}

// 根据键获取值，若键不存在则返回-1
int HashMapOpenAddressing::get(int key)
{
    int idx = findBucket(key);
    if (buckets[idx] != nullptr && buckets[idx] != TOMBSTONE)
        return buckets[idx]->val;
    return -1;
}

// 根据键删除键值对，将该位置标记为墓碑
void HashMapOpenAddressing::remove(int key)
{
    int idx = findBucket(key);
    if (buckets[idx] == nullptr || buckets[idx] == TOMBSTONE)
        return;
    buckets[idx] = TOMBSTONE; // 标记为墓碑
    mapSize--;
}

// 打印哈希表中的所有键值对
void HashMapOpenAddressing::print()
{
    for (int i = 0; i < capacity(); i++)
    {
        if (buckets[i] == nullptr)
            continue;
        std::cout << i << ":  key: " << buckets[i]->key << " val: " << buckets[i]->val << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    HashMapOpenAddressing hmoa(4); // 初始化容量为4的哈希表
    int cap = hmoa.capacity();

    /* 构造一个全是墓碑的数组 */
    for (int i = 0; i < cap; i++)
    {
        /* code */
        hmoa.put(i, i);
        hmoa.remove(i);
    }
    std::cout << "capacity: " << hmoa.capacity() << std::endl;
    hmoa.put(0, 0);
    hmoa.put(4, 4);
    hmoa.print();
    std::cout << "capacity: " << hmoa.capacity() << std::endl;
    return 0;
}