#include <iostream>
#include <vector>

struct Pair
{
    /* 键值对数据结构 */
    int key;
    int val;
    Pair(int _key, int _val) : key(_key), val(_val) {}
    ~Pair()
    {
        std::cout << "delete Pair! key: " << key << " val:" << val << std::endl;
    }
};

class HashMapOpenAddressing
{
private:
    /* 数据 */
    std::vector<Pair *> buckets; // 哈希表的桶
    int mapSize;                 // 当前大小
    int mapCapacity;             // 当前容量
    int extendRatio;             // 扩展比例
    Pair *TOMBSTONE;             // 墓碑标记
    int hash(int key);           // 哈希函数
    int hashFunc(int key);       // 哈希函数，返回哈希值

public:
    HashMapOpenAddressing(int capacity); // 构造函数
    ~HashMapOpenAddressing();            // 析构函数
    int size();                          // 获取当前大小
    int capacity();                      // 获取当前容量
    void put(int key, int val);          // 插入键值对
    int get(int key);                    // 获取键对应的值
    void remove(int key);                // 删除键值对
    void extendCapacity();               // 扩展容量
    int findEmpty();                     // 查找空桶
    void print();                        // 打印哈希表
};

HashMapOpenAddressing::HashMapOpenAddressing(int capacity) : buckets(std::vector<Pair *>(capacity)), mapSize(0), extendRatio(2), mapCapacity(capacity), TOMBSTONE(new Pair(-1, -1))
{
}

HashMapOpenAddressing::~HashMapOpenAddressing()
{
    for (const auto &bucket : buckets)
    {
        /* 遍历桶并删除非墓碑标记的键值对 */
        if (bucket == TOMBSTONE)
            continue;
        std::cout << "delete bucket!" << std::endl;
        delete bucket;
    }
    buckets.clear();
    std::cout << "delete buckets finish!" << std::endl;
    if (TOMBSTONE != nullptr)
    {
        std::cout << "delete TOMBSTONE" << std::endl;
        delete TOMBSTONE;
        TOMBSTONE = nullptr;
    }
    std::cout << "delete TOMBSTONE finish!" << std::endl;
}

int HashMapOpenAddressing::size()
{
    return mapSize;
}

int HashMapOpenAddressing::capacity()
{
    return mapCapacity;
}

int HashMapOpenAddressing::hash(int key)
{
    return key;
}

int HashMapOpenAddressing::hashFunc(int key)
{
    return hash(key) % capacity();
}

void HashMapOpenAddressing::extendCapacity()
{
    std::cout << "extend capacity!" << std::endl;
    std::vector<Pair *> temp = buckets;         // 暂存当前的桶
    mapCapacity *= extendRatio;                 // 扩展容量
    buckets = std::vector<Pair *>(mapCapacity); // 重新分配桶
    for (int i = 0; i < capacity(); i++)
        buckets[i] = nullptr; // 初始化新桶
    int len = size();
    for (int i = 0; i < len; i++)
    {
        /* 重新散列并复制键值对 */
        std::cout << "copy! key: " << temp[i]->key << " val: " << temp[i]->val << std::endl;
        if (temp[i] == TOMBSTONE)
        {
            buckets[i] = TOMBSTONE;
            temp[i] = nullptr;
            continue;
        }
        int idx = hashFunc(temp[i]->key);
        if (buckets[idx] == nullptr || buckets[idx] == TOMBSTONE)
            buckets[idx] = temp[i];
        else
        {
            /* 查找空桶并插入 */
            idx = findEmpty();
            if (idx != -1)
                buckets[idx] = temp[i];
        }
        temp[i] = nullptr;
    }
    temp.clear(); // 清空暂存的桶
}

int HashMapOpenAddressing::findEmpty()
{
    for (int i = 0; i < capacity(); i++)
    {
        /* 查找空桶或墓碑标记的位置 */
        if (buckets[i] == nullptr || buckets[i] == TOMBSTONE)
            return i;
    }
    return -1; // 未找到空桶
}

void HashMapOpenAddressing::put(int key, int val)
{
    if (size() == capacity())
        extendCapacity(); // 如果容量已满，则扩展容量
    int idx = hashFunc(key);
    Pair *temp = new Pair(key, val);
    if (buckets[idx] != nullptr && buckets[idx] != TOMBSTONE)
    {
        idx = findEmpty();
        if (idx == -1)
            return; // 未找到空桶
    }
    buckets[idx] = temp; // 插入键值对
    mapSize++;
}

int HashMapOpenAddressing::get(int key)
{
    int idx = hashFunc(key);
    if (buckets[idx] == nullptr)
        return -1; // 未找到键
    if (buckets[idx]->key == key)
        return buckets[idx]->val; // 找到键值对
    int tempIndex = -1;
    for (int i = 0; i < size(); i++)
    {
        /* 遍历查找键 */
        if (buckets[i] == nullptr)
            continue;
        if (buckets[i]->key == key)
        {
            int res = buckets[i]->val;

            /* 将目标元素与找到的第一个TOMBSTONE交换位置 */
            if (tempIndex != -1)
            {
                Pair *temp = buckets[i];
                buckets[i] = buckets[tempIndex];
                buckets[tempIndex] = temp;
            }
            return res; // 返回键对应的值
        }
        if (buckets[i] == TOMBSTONE && tempIndex != -1)
            tempIndex = i;
    }
    return -1; // 未找到键
}

void HashMapOpenAddressing::remove(int key)
{
    int idx = hashFunc(key);
    for (int i = 0; i < size(); i++)
    {
        /* 遍历查找键并删除 */
        if (buckets[i] == nullptr)
            continue;
        if (buckets[i]->key == key)
        {
            delete buckets[i];
            buckets[i] = TOMBSTONE;
            mapSize--;
            break;
        }
    }
}

void HashMapOpenAddressing::print()
{
    for (int i = 0; i < capacity(); i++)
    {
        /* 打印哈希表 */
        if (buckets[i] == nullptr)
            continue;
        std::cout << i << ":  key: " << buckets[i]->key << " val: " << buckets[i]->val << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    HashMapOpenAddressing hmoa(5); // 创建一个初始容量为5的哈希表
    int cap = hmoa.capacity();
    for (int i = 0; i < cap; i++)
        hmoa.put(i, i); // 插入键值对
    hmoa.remove(2);     // 删除键为2的键值对
    hmoa.put(10, 10);   // 插入新的键值对
    hmoa.put(9, 9);
    hmoa.put(11, 11);
    std::cout << "capacity: " << hmoa.capacity() << " size: " << hmoa.size() << std::endl;
    hmoa.print(); // 打印哈希表
    return 0;
}