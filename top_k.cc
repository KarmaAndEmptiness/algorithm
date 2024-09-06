#include <iostream>
#include <vector>

// 获取父节点
int getParent(int childIdx)
{
    // 根节点没有父节点
    if (childIdx == 0)
        return -1;
    return (childIdx - 1) / 2; // 向下取整
}
// 获取左子节点
int getLeftChild(int parentIdx)
{
    return 2 * parentIdx + 1;
}
// 获取右子节点
int getRightChild(int parentIdx)
{
    return 2 * parentIdx + 2;
}

// 获取堆顶值
int peek(std::vector<int> heap)
{
    if (heap.size() == 0)
        return 0;
    return heap[0];
}
// 交换节点
void swap(int *a, int *b)
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}

// 大顶堆自底向顶堆化
void maxHeapifyUp(std::vector<int> *heap, int idx)
{
    int p = -1;
    while (true)
    {
        /* code */
        p = getParent(idx);
        if (p < 0 || (*heap)[idx] <= (*heap)[p])
            break;
        if ((*heap)[idx] > (*heap)[p])
        {
            swap(&(*heap)[idx], &(*heap)[p]);
            idx = p;
        }
    }
}
// 大顶堆自顶向底堆化
void maxHeapifyDown(std::vector<int> *heap, int idx)
{
    if (heap->size() == 0)
        return;
    int l = -1, r = -1, max = idx;
    while (true)
    {
        /* code */
        l = getLeftChild(idx);
        r = getRightChild(idx);
        if (l < heap->size() && (*heap)[l] > (*heap)[max])
        {
            max = l;
        }
        if (r < heap->size() && (*heap)[r] > (*heap)[max])
        {
            max = r;
        }
        if (max == idx)
            break;
        swap(&(*heap)[idx], &(*heap)[max]);
        idx = max;
    }
}

// 入堆
void push(std::vector<int> *heap, int val)
{
    heap->push_back(val);
    maxHeapifyUp(heap, heap->size() - 1);
}

// 出堆
int pop(std::vector<int> *heap)
{
    int res = peek(*heap); // 获取堆顶值
    swap(&(*heap)[0], &(*heap)[heap->size() - 1]);
    heap->pop_back();
    maxHeapifyDown(heap, 0);
    return res;
}

// 基于堆实现查找数组中最小的前k个元素
void top_k(std::vector<int> arr, int k, std::vector<int> *res)
{
    std::vector<int> maxHeap;
    std::vector<int> temp;
    // 前k项入堆
    for (int i = 0; i < k; i++)
    {
        /* code */
        push(&maxHeap, arr[i]);
    }

    // 从第k+1项开始
    for (int i = k; i < arr.size(); i++)
    {
        // 如果节点小于堆顶值 则堆顶出堆 该节点入堆
        if (arr[i] < peek(maxHeap))
        {
            pop(&maxHeap);
            push(&maxHeap, arr[i]);
        }
    }

    // 倒序
    for (int i = 0; i < k; i++)
    {
        /* code */
        temp.push_back(pop(&maxHeap));
    }
    for (int i = k - 1; i >= 0; i--)
    {
        res->push_back(temp[i]);
    }
}
int main()
{
    // 大顶堆
    std::vector<int> maxHeap;
    std::vector<int> res;
    for (int i = 0; i < 1000; i++)
    {
        push(&maxHeap, i);
    }
    top_k(maxHeap, 5, &res);
    for (int i = 0; i < 5; i++)
    {
        /* code */
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}