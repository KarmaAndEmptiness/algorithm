#include <iostream>
/* 基于环形数组实现队列 */
class RingArrayQueue
{
private:
    /* data */
    int *arr;               // 环形数组地址
    int front = 0;          // 首元素的索引
    int rear = 0;           // 元素插入处的索引
    int queueSize = 0;      // 队列长度
    int queueCapacity = 10; // 环形数组容量
public:
    RingArrayQueue();
    ~RingArrayQueue();
    int size();
    int capacity();
    int peek();
    void push(int val);
    int pop();
};

/* 构造函数 */
RingArrayQueue::RingArrayQueue()
    : arr(new int[queueCapacity])
{
}

RingArrayQueue::~RingArrayQueue()
{
    delete[] arr;
}

/* 获取队列长度 */
int RingArrayQueue::size()
{
    return queueSize;
}

/* 获取环形数组容量 */
int RingArrayQueue::capacity()
{
    return queueCapacity;
}

/* 获取队首元素 */
int RingArrayQueue::peek()
{
    // 队列为空
    if (size() == 0)
        return -1;
    return arr[front];
}

/* 入队 */
void RingArrayQueue::push(int val)
{
    /*因为是环形数组,所以如果队列满了,那么将会重置到索引为0处开始插入 */
    if (size() == capacity())
    {
        std::cout << "队列已满！" << std::endl;
        rear = (front + size()) % capacity();
    }
    arr[rear] = val;
    rear++;
    queueSize++;
}

/* 出队 */
int RingArrayQueue::pop()
{
    if (size() == 0)
        return -1;
    int res = peek();

    /* 获取完最后一个元素后,重置索引到0*/
    front = (front + 1) % capacity();
    queueSize--;
    return res;
}

int main()
{
    RingArrayQueue raq;
    int cap = raq.capacity() * 2;
    for (int i = 0; i < cap; i++)
    {
        /* code */
        raq.push(i);
    }
    int size = raq.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << raq.pop() << " ";
    }
    std::cout << std::endl;
    return 0;
}