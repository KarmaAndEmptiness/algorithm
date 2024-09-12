#include <iostream>
/* 基于数组实现栈 */
class ArrayStack
{
private:
    /* data */
    int *arr;              // 用于存元素的数组
    int stackTop = -1;     // 栈顶
    int stackCapacity = 5; // 容量
    int extendRatio = 2;   // 扩展倍数

public:
    int stackSize = 0; // 栈的长度
    ArrayStack();
    ~ArrayStack();
    // int size();
    // int mySize();
    int capacity();
    void push(int val);
    int pop();
    void extendCapacity();
};

/* 构造函数 */
ArrayStack::ArrayStack() : arr(new int[stackCapacity])
{
}

/* 析构函数 */
ArrayStack::~ArrayStack()
{
    delete[] arr;
}

/* 获取长度 */
// int ArrayStack::size()
// {
//     return stackSize;
// }

// int ArrayStack::mySize()
// {
//     return stackSize;
// }

/* 获取容量 */
int ArrayStack::capacity()
{
    return stackCapacity;
}
/* 入栈 */
void ArrayStack::push(int val)
{
    if (stackSize == stackCapacity)
        extendCapacity();
    arr[++stackTop] = val;
    stackSize++;
}

/* 出栈 */
int ArrayStack::pop()
{
    if (stackSize == 0)
        return -1;
    stackSize--;
    return arr[stackTop--];
}

/* 扩容 */
void ArrayStack::extendCapacity()
{
    int *temp = arr;
    stackCapacity *= extendRatio;
    arr = new int[stackCapacity];
    for (int i = 0; i < stackSize; i++)
    {
        /* code */
        arr[i] = temp[i];
    }
    delete[] temp;
}
int main()
{
    ArrayStack as;
    int cap = as.capacity() + 2;
    for (int i = 0; i < cap; i++)
    {
        /* code */
        as.push(i + 3);
    }
    /*
            以下方式会报错：terminate called after throwing an instance of 'std::bad_array_new_length'
            what():  std::bad_array_new_length
            Aborted
        */
    // int size=as.size();

    /* 改名后也一样 */
    // int size = as.mySize();

    /* 这种方式不会报错 */
    int size = as.stackSize;

    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << as.pop() << std::endl;
    }

    return 0;
}