#include <iostream>
/* 基于数组实现栈 */
class ArrayStack
{
private:
    /* data */
    int *arr = nullptr;     // 用于存元素的数组
    int stackTop = -1;      // 栈顶
    int stackSize = 0;      // 栈的长度
    int stackCapacity = 10; // 容量
    int extendRatio = 2;    // 扩展倍数

public:
    ArrayStack();
    ~ArrayStack();
    int size();
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
    std::cout << "delete finish!" << std::endl;
}

/* 获取长度 */
int ArrayStack::size()
{
    return stackSize;
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
    if (stackTop < 0)
        return -1;
    int res = arr[stackTop--];
    stackSize--;
    return res;
}

/* 扩容 */
void ArrayStack::extendCapacity()
{
    int *temp = arr;
    stackCapacity *= extendRatio;
    arr = new int[stackCapacity];
    for (int i = 0; i < size(); i++)
    {
        /* code */
        arr[i] = temp[i];
    }
    delete[] temp;
}
int main()
{
    ArrayStack as;
    int size;
    for (int i = 0; i < 11; i++)
    {
        /* code */
        as.push(i + 3);
    }
    size = as.size();
    for (int i = 0; i < size; i++)
    {
        /* code */
        std::cout << as.pop() << " ";
    }
    std::cout << std::endl;
    return 0;
}