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
void shiftUp(int idx)
{
    while (true)
    {
        int p = parent(idx);
        // 如果是根节点 或者是当前节点大于父节点则返回
        if (idx == 0 || minHeap[idx] > minHeap[p])
            break;
        swap(&minHeap[idx], &minHeap[p]);
        idx = p;
    }
}
// 从顶至底堆化
void shiftDown(int idx)
{
    int l, r, min = idx;
    while (true)
    {
        l = left(idx);
        r = right(idx);
        if (l < minHeap.size() - 1 && minHeap[l] < minHeap[min])
        {
            min = l;
        }
        if (r < minHeap.size() - 1 && minHeap[r] < minHeap[min])
        {
            min = r;
        }
        if (min == idx)
            break;
        swap(&minHeap[idx], &minHeap[min]);
        idx = min;
    }
}
// 入堆
void push(int val)
{
    minHeap.push_back(val);
    shiftUp(minHeap.size() - 1);
}
// 出堆
void pop()
{
    if (minHeap.empty())
        return;

    // 交换堆顶和堆底的节点
    swap(&minHeap[0], &minHeap[minHeap.size() - 1]);

    // 删除堆底的节点
    minHeap.pop_back();

    shiftDown(0);
}
// 层序遍历
void levelOrder()
{
    for (int i = 0; i < minHeap.size(); i++)
    {
        /* code */
        std::cout << minHeap[i] << " ";
    }
    std::cout << std::endl;
}
// 前序遍历
void preOrder(int idx)
{
    if (idx > minHeap.size() - 1)
        return;
    std::cout << minHeap[idx] << " ";
    preOrder(left(idx));
    preOrder(right(idx));
}

int main()
{
    for (int i = 10; i > 0; i--)
    {
        /* code */
        push(i);
    }
    pop();
    std::cout << peek() << std::endl;
    levelOrder();
    preOrder(0);
    std::cout << std::endl;
    return 0;
}