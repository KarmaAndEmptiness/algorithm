#include <iostream>
struct Node
{
    /* data */
    int val;
    Node *next;
    Node(int x) : val(x), next(nullptr) {}
};

/* 基于环形链表实现队列 */
class RingLinkedQueue
{
private:
    /* data */
    Node *front;
    Node *rear;
    int queueCapacity = 10;
    int queueSize = 0;

public:
    RingLinkedQueue();
    ~RingLinkedQueue();
    int size();
    int peek();
    int capacity();
    void push(int val);
    int pop();
};

RingLinkedQueue::RingLinkedQueue() : front(nullptr), rear(nullptr)
{
}

RingLinkedQueue::~RingLinkedQueue()
{
    Node *node = front;
    Node *temp;
    /* 删除环形链表中所有的节点 */
    if (front != nullptr)
    {
        Node *node = front;
        do
        {
            temp = node;
            node = node->next;
            delete temp;
        } while (node != front); // since it's circular, stop when back at the front
    }
}
int RingLinkedQueue::size()
{
    return queueSize;
}

int RingLinkedQueue::capacity()
{
    return queueCapacity;
}

int RingLinkedQueue::peek()
{
    if (front == nullptr)
        return -1;
    return front->val;
}

void RingLinkedQueue::push(int val)
{
    /* 如果队列已满，就将尾节点的下一个指向首节点,并将入队的元素覆盖首节点  */
    if (size() == capacity())
    {
        front->val = val;
        rear->next = front;
        rear = rear->next;
    }

    /* 如果队列还没有满，就继续创建新的节点 */
    if (size() < capacity())
    {
        /* 创建首节点，此时首节点就是尾节点 */
        if (front == nullptr)
        {
            front = new Node(val);
            rear = front;
        }

        /* 创建新的节点，并更新尾节点的地址 */
        else
        {
            rear->next = new Node(val);
            rear = rear->next;
        }
    }

    /* 如果队列的长度超过了链表容量，则将新加入的元素继续覆盖环形链表前面的元素  */
    if (size() > capacity())
    {
        /* 将入队的元素插入到尾节点的下一节点*/
        rear->next->val = val;
        rear = rear->next;
    }

    /* 更新队列长度 */
    queueSize++;
}

int RingLinkedQueue::pop()
{
    /* 获取队首元素 */
    int res = peek();

    /* 更新队首元素的索引，使它指向下一节点 */
    front = front->next;

    /* 更新队列长度 */
    queueSize--;

    return res;
}

int main()
{
    RingLinkedQueue rlq;
    int cap = rlq.capacity();
    for (int i = 0; i < cap; i++)
    {
        /* code */
        rlq.push(i);
    }
    int size = rlq.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << rlq.pop() << " ";
    }
    std::cout << std::endl;
    return 0;
}