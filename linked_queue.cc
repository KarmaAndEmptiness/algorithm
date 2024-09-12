#include <iostream>
/* 链表节点结构体 */
struct Node
{
    /* data */
    int val;                               // 节点值
    Node *next;                            // 下一个节点的地址
    Node(int x) : val(x), next(nullptr) {} // 节点构造函数
};

/* 基于链表实现队列 */
class LinkedQueue
{
private:
    /* data */
    Node *front;       // 首节点
    Node *rear;        // 尾节点
    int queueSize = 0; // 队列长度
public:
    LinkedQueue();
    ~LinkedQueue();
    int size();
    void push(int val);
    int pop();
};

/* 构造函数 */
LinkedQueue::LinkedQueue() : front(nullptr), rear(nullptr)
{
}

/* 析构函数 */
LinkedQueue::~LinkedQueue()
{
    /* 删除所有节点 */
    Node *node = front;
    Node *temp; // 用来暂存下一个节点
    while (node != nullptr)
    {
        /* code */
        temp = node->next;
        delete node;
        node = temp;
        std::cout << "delete!" << " ";
    }
    std::cout << std::endl;
    std::cout << "delete finish!" << std::endl;
}

/* 获取队列长度 */
int LinkedQueue::size()
{
    return queueSize;
}

/* 入队 */
void LinkedQueue::push(int val)
{
    /* 第一个入队的元素为首节点 同时它也是最后一个节点  */
    if (front == nullptr)
    {
        front = new Node(val);
        rear = front;
    }

    /* 此后的每一个节点都加入到尾节点的后一个 并且将尾节点更新  */
    else
    {
        rear->next = new Node(val);
        rear = rear->next;
    }
    queueSize++;
}

/* 出队 */
int LinkedQueue::pop()
{
    // 队列为空
    if (queueSize == 0)
        return -1;

    // 队列不为空
    Node *temp = front->next;
    int res = front->val;
    delete front;
    front = temp;
    queueSize--;
    return res;
}

int main()
{
    LinkedQueue lq;
    for (int i = 0; i < 5; i++)
    {
        /* code */
        lq.push(i);
    }
    int size = lq.size();
    // for (int i = 0; i < size; i++)
    // {
    //     /* code */
    //     std::cout << lq.pop() << " ";
    // }
    // std::cout << std::endl;

    size -= 2;
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << lq.pop() << " ";
    }

    std::cout << std::endl;
    return 0;
}