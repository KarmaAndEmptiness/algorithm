#include <iostream>
#include <queue>
// AVL树节点
struct TreeNode
{
    int val{};         // 节点值
    int height = 0;    // 节点高度
    TreeNode *left{};  // 左节点
    TreeNode *right{}; // 右节点
    TreeNode() = default;
    explicit TreeNode(int x) : val(x) {}
};
// 获取节点高度
int height(TreeNode *node)
{
    return node == nullptr ? -1 : node->height;
}
// 更新节点高度
void updateHeight(TreeNode *node)
{
    node->height = std::max(height(node->left), height(node->right)) + 1;
}
// 获取平衡因子
int balanceFactor(TreeNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
// 右旋转
TreeNode *rightRotate(TreeNode *node)
{
    TreeNode *child = node->left;
    TreeNode *grandChild = child->right;

    child->right = node;
    node->left = grandChild;

    updateHeight(node);
    updateHeight(child);

    return child;
}
// 左旋转
TreeNode *leftRotate(TreeNode *node)
{
    TreeNode *child = node->right;
    TreeNode *grandChild = child->left;

    child->left = node;
    node->right = grandChild;

    updateHeight(node);
    updateHeight(child);

    return child;
}
// 旋转
TreeNode *rotate(TreeNode *node)
{
    int _balanceFactor = balanceFactor(node);
    // 左偏树
    if (_balanceFactor > 1)
    {
        // 右旋转
        if (balanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }
        // 先左旋转再右旋转
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // 右偏树
    if (_balanceFactor < -1)
    {
        // 左旋转
        if (balanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        // 先右旋转再左旋转
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}
// 插入节点
TreeNode *insertHelper(TreeNode *node, int val)
{

    if (node == nullptr)
        return new TreeNode(val);

    if (val < node->val)
    {
        node->left = insertHelper(node->left, val);
    }
    if (val > node->val)
    {
        node->right = insertHelper(node->right, val);
    }
    else
        return node;

    updateHeight(node);
    node = rotate(node);
    return node;
}
// 删除节点
TreeNode *removeHelper(TreeNode *node, int val)
{
    // 查找并删除节点
    if (val < node->val)
    {
        node->left = removeHelper(node->left, val);
    }
    else if (val > node->val)
    {
        node->right = removeHelper(node->right, val);
    }
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        {
            TreeNode *child = node->left == nullptr ? node->left : node->right;

            // 没有子节点
            if (child == nullptr)
            {
                delete node;
                return nullptr;
            }
            // 一个子节点
            delete node;
            node = child;
        }
        // 两个子节点
        else
        {
            TreeNode *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->val = temp->val;
            node->right = removeHelper(node->right, temp->val);
        }
    }
    updateHeight(node);
    node = rotate(node);
    return node;
}
// 层序遍历
void levelOrder(TreeNode *root)
{
    if (root == nullptr)
        return;
    // 用队列存储
    std::queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        TreeNode *node = queue.front();
        queue.pop();
        std::cout << node->val << " ";
        if (node->left != nullptr)
        {
            queue.push(node->left);
        }
        if (node->right != nullptr)
        {
            queue.push(node->right);
        }
    }
}
// 前序遍历
void preOrder(TreeNode *root)
{
    if (root == nullptr)
        return;
    std::cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}
// 中序遍历
void inOrder(TreeNode *node)
{
    if (node == nullptr)
        return;
    inOrder(node->left);
    std::cout << node->val << " ";
    inOrder(node->right);
}
// 后序遍历
void postOrder(TreeNode *node)
{
    if (node == nullptr)
        return;
    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->val << " ";
}
int main()
{
    // TreeNode root(1);
    // TreeNode left(2);
    // TreeNode right(3);
    // root.left = &left;
    // root.right = &right;
    // updateHeight(&root);
    // std::cout << height(&root) << std::endl;
    TreeNode *root = nullptr;
    for (int i = 0; i < 9; i++)
    {
        /* code */
        root = insertHelper(root, i);
    }
    // root = insertHelper(root, 2);
    // root = insertHelper(root, 3);
    root = removeHelper(root, 8);
    levelOrder(root);
    std::cout << std::endl;
    preOrder(root);
    std::cout << std::endl;
    inOrder(root);
    std::cout << std::endl;
    postOrder(root);
    std::cout << std::endl;
    return 0;
}