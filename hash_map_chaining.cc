#include <iostream>
#include <vector>

// 定义一个双向链表节点结构体，用于存储键值对
struct Node
{
    int key;    // 键
    int val;    // 值
    Node *next; // 指向下一个节点的指针
    Node *prev; // 指向上一个节点的指针

    // 构造函数，初始化键值对并设置指针为 nullptr
    Node(int a, int b) : key(a), val(b), next(nullptr), prev(nullptr) {}
};

// 定义一个桶（双向链表）的类，用于存储节点
class Bucket
{
private:
    Node *front;    // 链表的头节点
    Node *rear;     // 链表的尾节点
    int bucketSize; // 当前桶的大小

public:
    // 构造函数，初始化头尾节点为 nullptr，并设置桶的大小为 0
    Bucket();
    // 析构函数，负责释放链表节点的内存
    ~Bucket();
    // 返回当前桶的大小
    int size();
    // 向桶中添加一个节点（键值对）
    void add(int key, int val);
    // 从桶中移除指定键的节点
    void remove(int key);
    // 获取指定键对应的值，若不存在返回 -1
    int get(int key);
    // 返回桶中第一个节点
    Node *peekNode();
};

// 构造函数实现
Bucket::Bucket() : front(nullptr), rear(nullptr), bucketSize(0) {}

// 析构函数实现，释放链表中的所有节点内存
Bucket::~Bucket()
{
    Node *temp = front;
    Node *node = nullptr;
    while (temp != nullptr)
    {
        std::cout << "delete node! key: " << temp->key << " val: " << temp->val << std::endl;
        node = temp->next;
        delete temp;
        temp = node;
    }
    std::cout << "delete nodes finish!" << std::endl;
}

// 返回桶的大小
int Bucket::size()
{
    return bucketSize;
}

// 向链表尾部添加新的节点（键值对）
void Bucket::add(int key, int val)
{
    Node *temp = new Node(key, val);
    if (rear == nullptr)
    {
        rear = temp;
        front = rear;
    }
    else
    {
        rear->next = temp;
        temp->prev = rear;
        rear = rear->next;
    }
    bucketSize++;
}

// 从链表中移除指定键的节点
void Bucket::remove(int key)
{
    Node *temp = front;
    Node *prev = temp->prev;
    for (int i = 0; i < size(); i++)
    {
        if (temp->key == key)
        {
            // 链接节点的前驱和后继节点，删除中间节点
            if (prev != nullptr)
            {
                prev->next = temp->next;
                if (temp->next != nullptr)
                    temp->next->prev = prev;
                temp->next = nullptr;
                temp->prev = nullptr;
            }
            else
            {
                // 处理头节点的情况
                front = front->next;
                if (front != nullptr)
                    front->prev = nullptr;
            }
            // 处理尾节点的情况
            if (temp == rear)
                rear = rear->prev;
            delete temp;
            bucketSize--;
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
}

// 返回指定键对应的值，如果键不存在，返回 -1
int Bucket::get(int key)
{
    Node *temp = front;
    for (int i = 0; i < size(); i++)
    {
        if (temp->key == key)
            return temp->val;
        else
            temp = temp->next;
    }
    return -1;
}

// 返回链表的头节点
Node *Bucket::peekNode()
{
    return front;
}

// 定义一个哈希表类，使用链地址法处理冲突
class HashMapChaining
{
private:
    std::vector<Bucket *> buckets; // 用于存储多个桶（链表）
    int mapSize;                   // 当前哈希表中的键值对数量
    int mapCapacity;               // 当前哈希表的容量
    double loadThres;              // 负载因子阈值，超过时扩容
    int extendRatio;               // 扩容倍率
    // 简单的哈希函数，将键值返回原值
    int hash(int key);
    // 哈希函数，将键映射到桶的索引
    int hashFunc(int key);

public:
    // 构造函数，初始化哈希表的容量、负载因子等
    HashMapChaining();
    // 析构函数，释放所有桶的内存
    ~HashMapChaining();
    // 返回当前哈希表的大小
    int size();
    // 返回当前哈希表的容量
    int capacity();
    // 返回当前负载因子
    double loadFactor();
    // 扩展哈希表的容量
    void extendCapacity();
    // 获取指定键的值
    int get(int key);
    // 插入一个键值对
    void put(int key, int val);
    // 删除一个键值对
    void remove(int key);
    // 获取键对应的桶
    Bucket *getBucket(int key);
};

// 构造函数实现
HashMapChaining::HashMapChaining() : buckets(std::vector<Bucket *>(4)), mapSize(0), mapCapacity(4), loadThres(2.0 / 3.0), extendRatio(2)
{
    for (int i = 0; i < mapCapacity; i++)
    {
        buckets[i] = nullptr;
    }
}

// 析构函数实现，释放所有桶的内存
HashMapChaining::~HashMapChaining()
{
    for (const auto *bucket : buckets)
    {
        if (bucket == nullptr)
            continue;
        delete bucket;
        std::cout << "delete bucket!" << std::endl;
    }
    std::cout << "delete buckets finish!" << std::endl;
    buckets.clear();
}

// 返回当前哈希表的大小
int HashMapChaining::size()
{
    return mapSize;
}

// 返回当前哈希表的容量
int HashMapChaining::capacity()
{
    return mapCapacity;
}

// 计算负载因子
double HashMapChaining::loadFactor()
{
    return (double)(size() / capacity());
}

// 简单哈希函数，直接返回键值
int HashMapChaining::hash(int key)
{
    return key;
}

// 计算哈希桶的索引
int HashMapChaining::hashFunc(int key)
{
    return hash(key) % capacity();
}

// 当负载因子超过阈值时，扩展哈希表容量
void HashMapChaining::extendCapacity()
{
    std::cout << "------------" << std::endl;
    std::cout << "extend capacity!" << std::endl;
    std::vector<Bucket *> temp = buckets;
    mapCapacity *= extendRatio;
    buckets = std::vector<Bucket *>(mapCapacity);
    Node *tempNode = nullptr;
    for (int i = 0; i < capacity(); i++)
    {
        buckets[i] = nullptr;
    }

    for (int i = 0; i < size(); i++)
    {
        if (temp[i] == nullptr)
            continue;
        tempNode = temp[i]->peekNode();
        while (tempNode != nullptr)
        {
            int idx = hashFunc(tempNode->key);
            if (buckets[idx] == nullptr)
                buckets[idx] = new Bucket();
            buckets[idx]->add(tempNode->key, tempNode->val);
            tempNode = tempNode->next;
        }
        delete temp[i];
        std::cout << "delete bucket!" << std::endl;
    }
    temp.clear();
    std::cout << "delete buckets finish!" << std::endl;
    std::cout << "------------" << std::endl;
}

// 获取指定键的值
int HashMapChaining::get(int key)
{
    int idx = hashFunc(key);
    if (buckets[idx] == nullptr)
        return -1;
    return buckets[idx]->get(key);
}

// 插入一个键值对，如果负载因子超限则扩容
void HashMapChaining::put(int key, int val)
{
    if (loadFactor() >= loadThres)
        extendCapacity();
    Bucket *target = buckets[hashFunc(key)];
    if (target == nullptr)
    {
        buckets[hashFunc(key)] = new Bucket();
        target = buckets[hashFunc(key)];
        mapSize++;
    }
    target->add(key, val);
}

// 删除指定键的键值对
void HashMapChaining::remove(int key)
{
    Bucket *target = buckets[hashFunc(key)];
    if (target == nullptr)
        return;
    if (target->size() == 1)
    {
        delete target;
        buckets[hashFunc(key)] = nullptr;
        mapSize--;
        return;
    }
    target->remove(key);
}

// 返回键对应的桶
Bucket *HashMapChaining::getBucket(int key)
{
    int idx = hashFunc(key);
    return buckets[idx];
}

int main()
{
    HashMapChaining hmc;
    int cap = hmc.capacity();

    // 插入 cap-1 个键值对
    for (int i = 0; i < cap - 1; i++)
    {
        hmc.put(i, i);
    }

    std::cout << "------------" << std::endl;
    std::cout << "capacity: " << hmc.capacity() << " size: " << hmc.size() << std::endl;

    // 输出哈希表中的键值对
    int size = hmc.size();
    Node *temp = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (hmc.getBucket(i) == nullptr)
            continue;
        temp = hmc.getBucket(i)->peekNode();
        std::cout << i << ":";
        while (temp != nullptr)
        {
            std::cout << "  key: " << temp->key << " val: " << temp->val << "  ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    std::cout << "------------" << std::endl;

    // 插入 7 个新的键值对
    for (int i = 1000; i < 1000 + 7; i++)
    {
        hmc.put(i, i);
    }

    std::cout << "------------" << std::endl;
    std::cout << "capacity: " << hmc.capacity() << " size: " << hmc.size() << std::endl;

    // 再次输出哈希表中的键值对
    size = hmc.size();
    for (int i = 0; i < size; i++)
    {
        if (hmc.getBucket(i) == nullptr)
            continue;
        temp = hmc.getBucket(i)->peekNode();
        std::cout << i << ":";
        while (temp != nullptr)
        {
            std::cout << "  key: " << temp->key << " val: " << temp->val << "  ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    std::cout << "key:1001 val:" << hmc.get(1001) << std::endl;
    std::cout << "------------" << std::endl;

    hmc.remove(1003);

    std::cout << "------------" << std::endl;
    std::cout << "capacity: " << hmc.capacity() << " size: " << hmc.size() << std::endl;

    // 再次输出哈希表中的键值对
    size = hmc.size();
    for (int i = 0; i < size; i++)
    {
        if (hmc.getBucket(i) == nullptr)
            continue;
        temp = hmc.getBucket(i)->peekNode();
        std::cout << i << ":";
        while (temp != nullptr)
        {
            std::cout << "  key: " << temp->key << " val: " << temp->val << "  ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    std::cout << "------------" << std::endl;

    hmc.put(1003, 1002);
    hmc.remove(0);
    std::cout << "------------" << std::endl;
    std::cout << "capacity: " << hmc.capacity() << " size: " << hmc.size() << std::endl;

    // 再次输出哈希表中的键值对
    size = hmc.size();
    for (int i = 0; i < size; i++)
    {
        if (hmc.getBucket(i) == nullptr)
            continue;
        temp = hmc.getBucket(i)->peekNode();
        std::cout << i << ":";
        while (temp != nullptr)
        {
            std::cout << "  key: " << temp->key << " val: " << temp->val << "  ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    std::cout << "------------" << std::endl;
    return 0;
}