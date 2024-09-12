#include <iostream>
/* 基于数组实现队列 */
class ArrayQueue
{
private:
    /* data */
    int *arr;
    int queueSize = 0;
    int queueCapacity = 5;
    int extendRatio = 2;

public:
    ArrayQueue();
    ~ArrayQueue();
    int size();
    int capacity();
    int peek();
    void push(int val);
    int pop();
    void extendCapacity();
};

/* 构造函数 */
ArrayQueue::ArrayQueue()
    : arr(new int[queueCapacity])
{
}

/* 析构函数 */
ArrayQueue::~ArrayQueue()
{
    delete[] arr;
}

/* 获取队列长度 */
int ArrayQueue::size()
{
    return queueSize;
}

/* 获取队首元素 */
int ArrayQueue::peek()
{
    return arr[0];
}
/* 获取容量*/
int ArrayQueue::capacity()
{
    return queueCapacity;
}
/* 入队 */
void ArrayQueue::push(int val)
{
    if (queueSize == queueCapacity)
        extendCapacity();
    arr[size()] = val;
    queueSize++;
}

/* 出队 */
int ArrayQueue::pop()
{
    if (queueSize == 0)
        return -1;
    int res = peek();

    for (int i = 1; i < size(); i++)
    {
        arr[i - 1] = arr[i];
    }
    queueSize--;
    return res;
}

/* 扩容 */
void ArrayQueue::extendCapacity()
{
    int *temp = arr;
    queueCapacity *= extendRatio;
    arr = new int[queueCapacity];
    for (int i = 0; i < size(); i++)
    {
        /* code */
        arr[i] = temp[i];
    }
    delete[] temp;
}
int main()
{
    ArrayQueue aq;
    int cap = aq.capacity() + 3;
    for (int i = 0; i < cap; i++)
    {
        /* code */
        aq.push(i);
    }
    int len = aq.size();
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        std::cout << aq.pop() << " ";
    }
    std::cout << std::endl;
    return 0;
}