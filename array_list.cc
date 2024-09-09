#include <iostream>
/* 基于数组实现列表*/
class MyArrayList
{
private:
    /* data */
    int *arr;             // 数组
    int arrCapacity = 10; // 列表容量
    int arrSize = 0;      // 列表长度
    int extendRatio = 2;  // 扩容倍数
    void extendCapacity();

public:
    MyArrayList();
    ~MyArrayList();
    int size();
    int capacity();
    int get(int idx);
    void set(int idx, int val);
    void add(int val);
    void insert(int idx, int val);
    int remove(int idx);
    int *toArray();
};

/* 构造函数 */
MyArrayList::MyArrayList()
    : arr(new int[arrCapacity])
{
}

/* 析构函数 */
MyArrayList::~MyArrayList()
{
    delete[] arr;
}

/* 获取长度*/
int MyArrayList::size()
{
    return arrSize;
}

/* 获取容量 */
int MyArrayList::capacity()
{
    return arrCapacity;
}

/* 获取指定元素*/
int MyArrayList::get(int idx)
{
    if (idx < 0 || idx > size() - 1)
        return -1;
    return arr[idx];
}

/* 更新元素*/
void MyArrayList::set(int idx, int val)
{
    if (idx < 0 || idx > size() - 1)
        return;
    arr[idx] = val;
}

/* 添加元素*/
void MyArrayList::add(int val)
{

    if (size() + 1 > capacity())
        extendCapacity();
    arr[size()] = val;
    arrSize++;
}

/* 插入元素*/
void MyArrayList::insert(int idx, int val)
{
    if (idx < 0 || idx > size() - 1)
        return;
    if (size() + 1 > capacity())
        extendCapacity();
    for (int i = size() - 1; i >= idx; i--)
    {
        /* code */
        arr[i + 1] = arr[i];
    }
    arr[idx] = val;
    arrSize++;
}

/* 删除元素 */
int MyArrayList::remove(int idx)
{
    if (idx < 0 || idx > size() - 1)
        return -1;
    int res = arr[idx];
    for (int i = idx; i < size(); i++)
    {
        /* code */
        arr[i] = arr[i + 1];
    }
    arrSize--;
    return res;
}

/* 扩容 */
void MyArrayList::extendCapacity()
{
    int *temp = arr;

    arrCapacity *= extendRatio;
    arr = new int[arrCapacity];

    for (int i = 0; i < size(); i++)
    {
        /* code */
        arr[i] = temp[i];
    }

    delete[] temp;
}

/* 转为数组方便打印*/
int *MyArrayList::toArray()
{
    return arr;
}

int main()
{
    MyArrayList m_array_list;
    int *arr;
    /* 初始化列表 */
    for (int i = 0; i < 15; i++)
    {
        /* code */
        m_array_list.add(i);
    }

    /*插入一个元素*/
    m_array_list.insert(1, 3);

    /* 删除一个元素 */
    m_array_list.remove(m_array_list.size() - 1);

    /* 获取并打印第一个元素 */
    std::cout << m_array_list.get(0) << std::endl;

    /* 更新第一个元素 */
    m_array_list.set(0, 1);

    /* 获取元素的个数和列表的容量 */
    std::cout << m_array_list.size() << " " << m_array_list.capacity() << std::endl;

    /* 将列表转为数组并打印 */
    arr = m_array_list.toArray();
    for (int i = 0; i < m_array_list.size(); i++)
    {
        /* code */

        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}