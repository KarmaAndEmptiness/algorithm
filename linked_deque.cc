#include <iostream>
/* 双向链表节点结构体 */
struct Node
{
    int val;                                              // 节点值
    Node *next;                                           // 下个节点的地址
    Node *prev;                                           // 上个节点的地址
    Node(int x) : val(x), next(nullptr), prev(nullptr) {} // 构造函数
};

/* 基于双向链表实现双向队列 */
class LinkedDeque
{
private:
    /* data */
    Node *front;   // 头节点
    Node *rear;    // 尾节点
    int dequeSize; // 队列长度

public:
    LinkedDeque();
    ~LinkedDeque();
    int size();
    int peek();
    int bottom();
    void push_first(int val);
    void push_last(int val);
    int pop_first();
    int pop_last();
};

/* 构造函数 */
LinkedDeque::LinkedDeque() : front(nullptr), rear(nullptr), dequeSize(0)
{
}

/* 析构函数 */
LinkedDeque::~LinkedDeque()
{
    Node *temp = front;
    Node *node;
    while (temp != rear->next)
    {
        /* code */
        node = temp->next;
        delete temp;
        temp = node;
        std::cout << "delete!" << " ";
    }
    std::cout << "delete finish!" << std::endl;
}

/* 获取队列的长度 */
int LinkedDeque::size()
{
    return dequeSize;
}

/* 获取队列首节点的值 */
int LinkedDeque::peek()
{
    if (size() == 0)
        return -1;
    return front->val;
}

/* 获取队列尾节点的值 */
int LinkedDeque::bottom()
{
    if (size() == 0)
        return -1;
    return rear->val;
}

/* 从队列尾部入队 */
void LinkedDeque::push_last(int val)
{
    if (front == nullptr)
    {
        front = new Node(val);
        rear = front;
    }
    else
    {
        /* code */
        rear->next = new Node(val);
        rear->next->prev = rear;
        rear = rear->next;
    }
    dequeSize++;
}

/* 从队列头部入队 */
void LinkedDeque::push_first(int val)
{
    if (rear == nullptr)
    {
        rear = new Node(val);
        front = rear;
    }
    else
    {
        /* code */
        front->prev = new Node(val);
        front->prev->next = front;
        front = front->prev;
    }
    dequeSize++;
}

/* 从头部出队 */
int LinkedDeque::pop_first()
{
    int res = peek();
    Node *temp = front;
    front = front->next;
    delete temp;
    dequeSize--;
    return res;
}

/* 从尾部出队 */
int LinkedDeque::pop_last()
{
    int res = bottom();
    Node *temp = rear;
    rear = rear->prev;
    delete temp;
    dequeSize--;
    return res;
}

int main()
{
    LinkedDeque ld;

    /* 0-2 从头部入队,得到 2 1 0 */
    for (int i = 0; i < 3; i++)
    {
        /* code */
        ld.push_first(i);
    }
    std::cout << "peek:" << ld.peek() << " bottom:" << ld.bottom() << std::endl;

    /* 3-8 从尾部入队,得到 2 1 0 3 4 5 6 7 8*/
    for (int i = 3; i < 9; i++)
    {
        /* code */
        ld.push_last(i);
    }
    std::cout << "peek:" << ld.peek() << " bottom:" << ld.bottom() << std::endl;

    /* 留下4个元素，其它的从前面出队,输出 2 1 0 3 4,剩余 5 6 7 8*/
    int size = ld.size();
    for (int i = 0; i < size - 4; i++)
    {
        /* code */
        std::cout << ld.pop_first() << " ";
    }
    std::cout << std::endl;
    std::cout << "peek:" << ld.peek() << " bottom:" << ld.bottom() << std::endl;

    /* 留下2个元素，其它的从后面出队,输出 8 7,剩余 5 6*/
    size = ld.size();
    for (int i = 0; i < size - 2; i++)
    {
        /* code */
        std::cout << ld.pop_last() << " ";
    }
    std::cout << std::endl;
    std::cout << "peek:" << ld.peek() << " bottom:" << ld.bottom() << std::endl;
    return 0;
}