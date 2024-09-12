#include <iostream>
struct Node
{
    int val;
    Node *next;
    Node(int x) : val(x), next(nullptr) {}
};
/* 基于单向链表实现列表 */
class MyLinkedList
{
private:
    /* data */
    Node *firstNode;
    Node *lastNode;
    int *arr;
    int listSize = 1; // 初始化的时候至少存在首节点

public:
    MyLinkedList(int val);
    ~MyLinkedList();
    int size();
    Node const *start();
    Node const *end();
    void push_back(int val);
    int remove(int idx);
    void set(int idx, int val);
    int get(int idx);
    void insert(int idx, int val);
    int const *toArray();
};
/* 构造函数 初始化node的值 */
MyLinkedList::MyLinkedList(int val) : firstNode(new Node(val)), lastNode(firstNode)
{
}

/* 析构函数 */
MyLinkedList::~MyLinkedList()
{
    Node *temp;
    Node const *node = firstNode;
    while (node != nullptr)
    {
        /* code */
        temp = node->next;
        delete node;
        node = temp;
    }
    delete[] arr;
    std::cout << "delete finish!" << std::endl;
}

/* 获取列表的长度 */
int MyLinkedList::size()
{
    return listSize;
}
/* 获取首节点 */
Node const *MyLinkedList::start()
{
    return firstNode;
}

/* 获取最后一个节点 */
Node const *MyLinkedList::end()
{
    return lastNode;
}

/* 增加元素 */
void MyLinkedList::push_back(int val)
{
    Node *node = firstNode;
    Node *temp = new Node(val);
    if (end() != start())
    {
        lastNode->next = temp;
    }
    else
        node->next = temp;
    lastNode = temp;
    listSize++;
}

/* 删除指定的元素(以该元素的索引为key) */
int MyLinkedList::remove(int idx)
{
    if (idx < 0 || idx >= size())
        return -1;
    Node *target = firstNode;
    Node *temp;
    int count = 0, res;

    if (idx == 0)
    {
        res = target->val;
        temp = target->next;
        delete target;
        firstNode = temp;
        listSize--;
        return res;
    }
    /* 找到目标节点的前一个节点 */
    while (count < idx - 1)
    {
        target = target->next;
        count++;
    }

    res = target->next->val;
    /* 删除目标节点 */
    temp = target->next->next;
    delete target->next;
    target->next = temp;

    /* 如果删除的元素是最后一个，那么需要更新lastNode */
    if (idx == size() - 1)
        lastNode = target;
    listSize--;
    return res;
}

/* 插入节点(用索引指定位置) */
void MyLinkedList::insert(int idx, int val)
{
    if (idx < 0 || idx > size())
        return;
    Node *target = firstNode;
    Node *temp = new Node(val);
    int count = 0;

    if (idx == 0)
    {
        temp->next = target;
        firstNode = temp;
        listSize++;
        return;
    }

    /* 找到目标节点的前一个节点 */
    while (count < idx - 1)
    {
        target = target->next;
        count++;
    }

    /* 插入节点 */
    temp->next = target->next;
    target->next = temp;

    /* 如果插入的位置是最后，那么需要将lastNode更新为插入的节点*/
    if (idx == size())
        lastNode = temp;
    listSize++;
}

/* 更新元素 */
void MyLinkedList::set(int idx, int val)
{
    if (idx < 0 || idx >= size())
        return;
    Node *target = firstNode;
    int count = 0;

    /* 找到目标节点 */
    while (count < idx)
    {
        target = target->next;
        count++;
    }

    /* 更新目标节点值 */
    target->val = val;
}

/* 根据索引值查找指定的元素 */
int MyLinkedList::get(int idx)
{
    if (idx < 0 || idx >= size())
        return -1;
    Node *target = firstNode;
    int count = 0;

    /* 找到目标节点 */
    while (count < idx)
    {
        target = target->next;
        count++;
    }
    return target->val;
}

/* 将列表转化为数组方便打印 */
int const *MyLinkedList::toArray()
{
    Node *node = firstNode;
    arr = new int[size()];
    int i = 0;
    while (node != nullptr)
    {
        /* code */
        arr[i] = node->val;
        node = node->next;
        i++;
    }
    return arr;
}
int main()
{
    /* 初始化列表 */
    MyLinkedList ml(1);
    for (int i = 2; i < 15; i++)
    {
        /* code */
        ml.push_back(i);
    }
    std::cout << "原列表:" << std::endl;

    /*用链表的方式遍历 */
    Node const *temp = ml.start();
    while (true)
    {
        /* code */
        std::cout << temp->val << " ";
        if (temp == ml.end())
            break;
        temp = temp->next;
    }
    std::cout << std::endl;

    /* 将元素插入到索引为4的位置 */
    ml.insert(4, 30);

    /* 将元素插入到最后*/
    ml.insert(ml.size(), 50);

    std::cout << "插入元素后: " << std::endl;
    /*用链表的方式遍历 */
    temp = ml.start();
    while (true)
    {
        /* code */
        std::cout << temp->val << " ";
        if (temp == ml.end())
            break;
        temp = temp->next;
    }
    std::cout << std::endl;

    /* 删除索引为0的元素*/
    ml.remove(0);

    /* 删除最后一个元素 */
    ml.remove(ml.size() - 1);

    std::cout << "删除后:" << std::endl;
    /*用链表的方式遍历 */
    temp = ml.start();
    while (true)
    {
        /* code */
        std::cout << temp->val << " ";
        if (temp == ml.end())
            break;
        temp = temp->next;
    }
    std::cout << std::endl;

    /* 更新索引值为2的元素 */
    ml.set(2, 100);

    /* 更新最后一个元素的值 */
    ml.set(ml.size() - 1, 25);

    std::cout << "更新后:" << std::endl;

    /* 获取索引值为2的元素 */
    std::cout << ml.get(2) << std::endl;

    /* 转化为数组并打印 */
    int const *arr = ml.toArray();

    for (int i = 0; i < ml.size(); i++)
    {
        /* code */
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}