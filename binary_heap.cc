#include <iostream>
#include <vector>
std::vector<int> minHeap;

// 获取堆顶值
int peek()
{
    return minHeap[0];
}
// 获取左子节点
int left(int idx)
{
    return 2 * idx + 1;
}
// 获取右子节点
int right(int idx)
{
    return 2 * idx + 2;
}
// 获取父节点
int parent(int idx)
{
    return (idx - 1) / 2; // 向下取整
}
// 节点交换
void swap(int *i, int *j)
{
    int temp = 0;
    temp = *i;
    *i = *j;
    *j = temp;
}
// 从底至顶堆化
void shiftUp(std::vector<int> *heap, int idx)
{
    while (true)
    {
        int p = parent(idx);
        // 如果是根节点 或者是当前节点大于父节点则返回
        if (idx == 0 || (*heap)[idx] > (*heap)[p])
            break;
        swap(&(*heap)[idx], &(*heap)[p]);
        idx = p;
    }
}
// 从顶至底堆化
void shiftDown(std::vector<int> *minHeap, int idx)
{
    if (minHeap->size() == 0)
        return;
    int l, r, min = idx;
    while (true)
    {
        l = left(idx);
        r = right(idx);
        if (l <= minHeap->size() - 1 && (*minHeap)[l] < (*minHeap)[min])
        {
            min = l;
        }
        if (r <= minHeap->size() - 1 && (*minHeap)[r] < (*minHeap)[min])
        {
            min = r;
        }
        if (min == idx)
            break;
        swap(&(*minHeap)[idx], &(*minHeap)[min]);
        idx = min;
    }
}
// 入堆
void push(std::vector<int> *res, int val)
{
    res->push_back(val);
    shiftUp(res, res->size() - 1);
}
// 出堆
int pop(std::vector<int> *minHeap)
{
    int res;
    if (minHeap->empty())
        return -1;
    res = (*minHeap)[0];
    // 交换堆顶和堆底的节点
    swap(&(*minHeap)[0], &(*minHeap)[minHeap->size() - 1]);

    // 删除堆底的节点
    minHeap->pop_back();
    shiftDown(minHeap, 0);
    return res;
}

// 建堆
void buildMinHeap(/**std::vector<int> arr,**/ std::vector<int> *res)
{
    // 用入堆的方式建堆
    // for (int i = 0; i < arr.size(); i++)
    // {
    //     /* code */
    //     push(res, arr[i]);
    // }

    // 通过遍历堆化实现
    for (int i = parent(res->size() - 1); i >= 0; i--)
    {
        /* code */
        shiftDown(res, i);
    }
}
// 层序遍历
void levelOrder(std::vector<int> heap)
{
    for (int i = 0; i < heap.size(); i++)
    {
        /* code */
        std::cout << heap[i] << " ";
    }
    std::cout << std::endl;
}
// 前序遍历
void preOrder(std::vector<int> arr, int idx)
{
    if (idx > arr.size() - 1)
        return;
    std::cout << arr[idx] << " ";
    preOrder(arr, left(idx));
    preOrder(arr, right(idx));
}
int main()
{
    // for (int i = 10; i > 0; i--)
    // {
    //     /* code */
    //     push(minHeap, i);
    // }
    // pop();
    // std::cout << peek() << std::endl;
    // levelOrder(minHeap);
    // preOrder(minHeap, 0);
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> res;
    // buildMinHeap(arr, &res);
    res = arr;
    buildMinHeap(&res);
    int len = res.size();
    for (int i = 0; i < len; i++)
    {
        // std::cout << pop(&res) << " ";
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}