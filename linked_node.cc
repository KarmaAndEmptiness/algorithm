#include <iostream>
/*链表节点结构体*/
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
/*在节点n之后插入p*/
void insert(ListNode *n, ListNode *p)
{
    ListNode *temp = n->next;
    n->next = p;
    p->next = temp;
}
/* 删除节点n之后的首个节点*/
void remove(ListNode *n)
{
    n->next = n->next->next;
}
/* 查找从n开始值为target的首个节点*/
void find(ListNode *n, int target)
{
    if (n == nullptr)
        return;
    while (n != nullptr)
    {
        /* code */
        if (n->val == target)
        {
            std::cout << "finish!" << std::endl;
            break;
        }
        n = n->next;
    }
}
int main()
{
    /*初始化链表*/
    ListNode n0(1);
    ListNode n1(2);
    ListNode n2(3);
    n0.next = &n1;
    n1.next = &n2;

    ListNode n3(4);

    /* 在n1后插入节点 n3 */
    insert(&n1, &n3);

    /* 遍历链表 */
    ListNode *n = &n0;
    while (n != nullptr)
    {
        std::cout << n->val << " ";
        n = n->next;
    }
    std::cout << std::endl;

    /* 删除n0之后的首个元素 */
    remove(&n0);

    /* 遍历链表 */
    n = &n0;
    while (n != nullptr)
    {
        std::cout << n->val << " ";
        n = n->next;
    }
    std::cout << std::endl;

    /* 查找n0之后的值为4的元素 */
    find(&n0, 4);

    return 0;
}