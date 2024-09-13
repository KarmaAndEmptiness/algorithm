#include <iostream>
class RingArrayQueue
{
private:
    /* data */
    int *arr;          // 存储队列的数组
    int front;         // 队列首元素的索引
    int rear = 0;      // 入队元素将要插入的位置索引
    int queueSize;     // 队列长度
    int queueCapacity; // 数组容量

public:
    RingArrayQueue(int capacity);
    ~RingArrayQueue();
    int size();
    int capacity();
    int peek();
    void push(int val);
    int pop();
};

/* 构造函数 */
RingArrayQueue::RingArrayQueue(int capacity) : arr(new int[queueCapacity]), queueSize(0), front(0), queueCapacity(capacity)
{
}

/* 析构函数 */
RingArrayQueue::~RingArrayQueue()
{
    delete[] arr;
}
/* 获取列表长度 */
int RingArrayQueue::size()
{
    return queueSize;
}

/* 获取列表长度 */
int RingArrayQueue::capacity()
{
    return queueCapacity;
}

/* 入队 */
void RingArrayQueue::push(int val)
{
    /* 队列满了之后，再入队的元素直接丢弃 */
    if (size() == capacity())
        return;
    /* 将元素添加至队尾 */
    arr[rear] = val;
    /* 当rear指向队列的最后一个元素的下一个元素时，将rear重置为0*/
    rear = (rear + 1) % capacity();
    queueSize++;
}

/* 出队 */
int RingArrayQueue::pop()
{
    if (queueSize == 0)
        return -1;
    /* 将队列中的首元素返回*/
    int res = arr[front];
    /* 当front指向最后一个元素的下一个元素时，将front重置为0*/
    front = (front + 1) % capacity();
    queueSize--;
    return res;
}
int main()
{
    RingArrayQueue raq(6);

    /* 将队列加满 */
    int cap = raq.capacity();
    for (int i = 0; i < cap; i++)
    {
        /* code */
        raq.push(i);
    }

    /* 除了最后3个，其它的全部出队 */
    int size = raq.size() - 3;
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << raq.pop() << " ";
    }
    std::cout << std::endl;

    /* 100入队 */
    raq.push(100);

    /* 队列中剩余元素全部出队 */
    size = raq.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << raq.pop() << " ";
    }
    std::cout << std::endl;

    /* 将队列加满 */
    for (int i = 0; i < cap; i++)
    {
        /* code */
        raq.push(i + 9);
    }

    /* 队列中的元素全部出队 */
    size = raq.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << raq.pop() << " ";
    }
    std::cout << std::endl;
    return 0;
}