#include <iostream>
class RingArrayQueue
{
private:
    /* data */
    int *arr;
    int front;
    // int rear=0;//用这种方式定义rear,调用push打印的时候size()有问题
    int queueSize;
    int queueCapacity;

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
    if (size() == capacity())
        return;
    // 用这种方式定义rear打印size()就没有问题
    int rear = (front + size()) % capacity();
    arr[rear] = val;
    queueSize++;
}

/* 出队 */
int RingArrayQueue::pop()
{
    // if (queueSize == 0)
    //     return -1;
    int res = arr[front];
    front = (front + 1) % capacity();
    queueSize--;
    return res;
}
int main()
{
    RingArrayQueue raq(10);

    int cap = raq.capacity();
    for (int i = 0; i < cap; i++)
    {
        /* code */
        raq.push(i);
    }
    int size = raq.size() - 3;
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << raq.pop() << " ";
    }
    std::cout << std::endl;
    raq.push(100);
    size = raq.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << raq.pop() << " ";
    }
    std::cout << std::endl;

    return 0;
}