#include <iostream>
/* 基于环形数组实现双向队列 */
class RingArrayDeque
{
private:
    /* data */
    int *arr;          // 存储队列的数组
    int front;         // 队列首节点的索引
    int rear;          // 队列尾节点的索引
    int dequeSize;     // 队列长度
    int dequeCapacity; // 数组容量

public:
    RingArrayDeque(int capacity);
    ~RingArrayDeque();
    int size();
    int capacity();
    int index(int idx);
    int peek();
    int bottom();
    void push_first(int val);
    void push_last(int val);
    int pop_first();
    int pop_last();
};

/* 构造函数 */
RingArrayDeque::RingArrayDeque(int capacity) : arr(new int[capacity]), dequeCapacity(capacity), front(0), rear(0), dequeSize(0)
{
}

/* 析构函数 */
RingArrayDeque::~RingArrayDeque()
{
    delete[] arr;
}

/* 获取队列长度*/
int RingArrayDeque::size()
{
    return dequeSize;
}

/* 获取数组容量 */
int RingArrayDeque::capacity()
{
    return dequeCapacity;
}

/* 获取队列头节点的值 */
int RingArrayDeque::peek()
{
    if (size() == 0)
        return -1;
    return arr[front];
}

/* 获取队列尾节点的值 */
int RingArrayDeque::bottom()
{
    if (size() == 0)
        return -1;
    return arr[rear];
}

/* 从队列前面入队 */
void RingArrayDeque::push_first(int val)
{
    if (size() == capacity())
        return;
    /* arr[0]如果是被尾节点占用了，front就从arr[capacity()-1]开始，如果没有，则从arr[0]开始*/
    front = (capacity() - (size() - rear)) % capacity();
    arr[front] = val;
    dequeSize++;
}

/* 从队列后面入队 */
void RingArrayDeque::push_last(int val)
{
    if (size() == capacity())
        return;

    /* arr[0]如果被头节点占用了，rear就从arr[1]开始，如果没有，则从arr[0]开始*/
    rear = (front + size()) % capacity();
    arr[rear] = val;
    dequeSize++;
}

/* 从队列前面出队 */
int RingArrayDeque::pop_first()
{
    int res = peek();
    front = index(front + 1);

    // or
    //     front = (front + 1) % capacity();

    dequeSize--;
    return res;
}

/* 从队列后面出队 */
int RingArrayDeque::pop_last()
{
    int res = bottom();

    rear = index(rear - 1);
    /* 当rear是0的时候，下一个位置是rear-1=-1，而-1在环形数组中是capacity()-1，所以应该把-1转换成capacity()-1*/
    // rear = (capacity() - (1 - rear)) % capacity();
    dequeSize--;
    return res;
}

/* 还有一种更简单的转换索引的方法 */
int RingArrayDeque::index(int idx)
{
    return (capacity() + idx) % capacity();
}

int main()
{
    RingArrayDeque rad(10);
    int cap = rad.capacity();
    for (int i = 0; i < cap - 2; i++)
    {
        /* code */
        rad.push_first(i);
    }
    int size = rad.size();
    for (int i = 0; i < cap - size; i++)
    {
        /* code */
        rad.push_last(size + i);
    }

    size = rad.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << rad.pop_first() << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cap; i++)
    {
        /* code */
        rad.push_first(i);
    }

    size = rad.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << rad.pop_first() << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cap; i++)
    {
        /* code */
        rad.push_last(i);
    }

    size = rad.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << rad.pop_first() << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cap; i++)
    {
        /* code */
        rad.push_first(i);
    }
    size = rad.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << rad.pop_last() << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < cap; i++)
    {
        /* code */
        rad.push_last(i);
    }
    size = rad.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << rad.pop_last() << " ";
    }
    std::cout << std::endl;
    return 0;
}