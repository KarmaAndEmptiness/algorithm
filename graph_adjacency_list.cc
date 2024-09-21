#include <iostream>
#include <vector>

struct Vertex
{
    int val;
    Vertex *next;

    // 构造函数，初始化顶点值并将 next 指针设为 nullptr
    Vertex(int _val) : val(_val), next(nullptr) {}
};

class GraphAdjacencyList
{
private:
    std::vector<Vertex *> vertices; // 用于存储顶点的动态数组
    int verticesSize;               // 当前图中顶点的数量

public:
    // 构造函数，传入顶点列表并初始化图
    GraphAdjacencyList(const std::vector<Vertex *> &_vertices);

    // 析构函数，销毁图，释放内存
    ~GraphAdjacencyList();

    // 添加顶点
    void addVertex(int val);

    // 删除顶点
    void removeVertex(int val);

    // 添加边
    void addEdge(int a, int b);

    // 删除边
    void removeEdge(int a, int b);

    // 打印图的邻接表
    void print();
};

// 构造函数实现
GraphAdjacencyList::GraphAdjacencyList(const std::vector<Vertex *> &_vertices) : vertices(_vertices), verticesSize(vertices.size())
{
}

// 析构函数实现
GraphAdjacencyList::~GraphAdjacencyList()
{
    Vertex *temp = nullptr;
    Vertex *tempNext = nullptr;
    // 遍历每个顶点并释放链表中的所有节点
    for (int i = 0; i < verticesSize; i++)
    {
        temp = vertices[i];
        while (temp != nullptr)
        {
            std::cout << "delete vertex! val:" << temp->val << std::endl; // 输出删除信息
            tempNext = temp->next;
            delete temp;     // 删除当前节点
            temp = tempNext; // 移动到下一个节点
        }
    }
    std::cout << "delete finish!" << std::endl; // 删除完成
}

// 添加顶点函数实现
void GraphAdjacencyList::addVertex(int val)
{
    vertices.push_back(new Vertex(val)); // 在图中添加新顶点
    verticesSize++;                      // 更新顶点数量
}

// 删除顶点函数实现
void GraphAdjacencyList::removeVertex(int val)
{
    Vertex *temp = nullptr;
    int targetIdx = -1; // 记录要删除的顶点索引

    // 遍历所有顶点，找到目标顶点
    for (int i = 0; i < verticesSize; i++)
    {
        temp = vertices[i];
        if (temp->val == val)
        {
            targetIdx = i;
            continue;
        }
        // 遍历当前顶点的邻接链表，删除与目标顶点相关的边
        while (temp->next != nullptr)
        {
            temp = temp->next;
            if (temp->val == val)
                removeEdge(vertices[i]->val, val); // 删除边
        }
    }
    temp = vertices[targetIdx];
    // 将目标顶点从数组中移除
    for (int i = targetIdx + 1; i < verticesSize; i++)
    {
        vertices[i - 1] = vertices[i];
    }
    verticesSize--;                                               // 更新顶点数量
    vertices.erase(vertices.end() - 1);                           // 删除数组末尾的顶点
    std::cout << "delete vertex! val:" << temp->val << std::endl; // 输出删除信息
    delete temp;                                                  // 删除目标顶点
}

// 添加边函数实现
void GraphAdjacencyList::addEdge(int a, int b)
{
    if (a == b)
        return; // 如果是自环则直接返回

    Vertex *temp = nullptr;
    // 遍历顶点列表，找到顶点 a 和 b
    for (int i = 0; i < verticesSize; i++)
    {
        if (vertices[i]->val == a)
        {
            temp = vertices[i];
            // 将 b 添加到 a 的邻接链表中
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new Vertex(b);
        }
        if (vertices[i]->val == b)
        {
            temp = vertices[i];
            // 将 a 添加到 b 的邻接链表中
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new Vertex(a);
        }
    }
}

// 删除边函数实现
void GraphAdjacencyList::removeEdge(int a, int b)
{
    if (a == b)
        return; // 自环边则直接返回

    Vertex *temp = nullptr;
    Vertex *prev = nullptr;
    // 遍历顶点列表，删除顶点 a 和 b 之间的边
    for (int i = 0; i < verticesSize; i++)
    {
        if (vertices[i]->val == a)
        {
            temp = vertices[i];
            while (temp != nullptr)
            {
                if (temp->val == b)
                {
                    prev->next = temp->next; // 重新连接链表
                    temp->next = nullptr;
                    std::cout << "delete vertex! val:" << temp->val << std::endl; // 输出删除信息
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        if (vertices[i]->val == b)
        {
            temp = vertices[i];
            while (temp != nullptr)
            {
                if (temp->val == a)
                {
                    prev->next = temp->next; // 重新连接链表
                    temp->next = nullptr;
                    std::cout << "delete vertex! val:" << temp->val << std::endl; // 输出删除信息
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }
    }
}

// 打印图的邻接表
void GraphAdjacencyList::print()
{
    Vertex *temp = nullptr;
    for (int i = 0; i < verticesSize; i++)
    {
        std::cout << "Vertex " << " ";
        temp = vertices[i];
        // 打印当前顶点的邻接链表
        while (temp->next != nullptr)
        {
            std::cout << temp->val << " -> ";
            temp = temp->next;
        }
        std::cout << temp->val << std::endl;
    }
}

int main()
{
    std::vector<Vertex *> vertices;
    // 创建顶点 1 到 4
    for (int i = 1; i < 5; i++)
    {
        vertices.push_back(new Vertex(i));
    }
    GraphAdjacencyList gal(vertices); // 创建图
    gal.addEdge(1, 2);                // 添加边 1 -> 2
    gal.addEdge(2, 3);                // 添加边 2 -> 3
    gal.addEdge(3, 4);                // 添加边 3 -> 4
    gal.removeEdge(2, 3);             // 删除边 2 -> 3
    gal.addVertex(5);                 // 添加顶点 5
    gal.addEdge(5, 4);                // 添加边 5 -> 4
    gal.print();                      // 打印当前图
    std::cout << std::endl;
    gal.removeVertex(3); // 删除顶点 3
    gal.print();         // 打印当前图
    gal.removeVertex(1); // 删除顶点 1
    gal.print();         // 打印当前图
    return 0;
}