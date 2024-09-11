#include <iostream>
/* 链表节点 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x) {}
};
/*基于链表实现栈*/
class LinkedStack
{
private:
    /* data */
    ListNode *stackTop; // 栈顶
    int listSize = 0;   // 栈的长度

public:
    LinkedStack();
    ~LinkedStack();
    void push(int val);
    int pop();
};

/* 构造函数 */
LinkedStack::LinkedStack() : stackTop(nullptr)
{
}

/* 析构函数 */
LinkedStack::~LinkedStack()
{
    ListNode *node = stackTop;
    ListNode *temp = nullptr;
    if (node == nullptr)
        std::cout << "node is nullptr" << std::endl;
    while (node != nullptr)
    {
        /* code */
        temp = node->next;
        delete node;
        node = temp;
        std::cout << "delete!" << std::endl;
    }
    std::cout << "delete finish!" << std::endl;
}

/* 入栈 */
void LinkedStack::push(int val)
{
    ListNode *temp = new ListNode(val);
    temp->next = stackTop;
    stackTop = temp;
    listSize++;
}

/* 出栈 */
int LinkedStack::pop()
{
    if (stackTop == nullptr || listSize == 0)
        return -1;
    ListNode *temp = stackTop;
    int res = stackTop->val;
    stackTop = stackTop->next;
    delete temp;
    listSize--;
    return res;
}

int main()
{
    LinkedStack ls;
    ls.push(1);
    ls.push(2);
    ls.push(3);
    std::cout << ls.pop() << std::endl;
    std::cout << ls.pop() << std::endl;
    return 0;
}