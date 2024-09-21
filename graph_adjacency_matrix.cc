#include <iostream>
#include <vector>

/**
 * GrapAdjacencyMatrix 类，使用邻接矩阵表示图
 * 包含顶点和邻接矩阵的管理，支持添加和删除顶点、边
 */
class GrapAdjacencyMatrix
{
private:
    std::vector<int> vertices;            // 存储图的顶点
    std::vector<std::vector<int>> adjMat; // 存储邻接矩阵，表示边的连接关系

public:
    /**
     * 构造函数
     * @param _vertices 初始的顶点集合
     * @param edges 初始的边的集合，每个边是一个由两个整数构成的向量
     */
    GrapAdjacencyMatrix(const std::vector<int> &_vertices, const std::vector<std::vector<int>> &edges);

    /**
     * 析构函数
     */
    ~GrapAdjacencyMatrix();

    /**
     * 添加顶点
     * @param val 要添加的顶点的值
     */
    void addVertex(int val);

    /**
     * 删除顶点
     * @param idx 要删除的顶点在vertices中的索引
     */
    void removeVertex(int idx);

    /**
     * 添加边
     * @param i 边的一个顶点索引
     * @param j 边的另一个顶点索引
     */
    void addEdge(int i, int j);

    /**
     * 删除边
     * @param i 边的一个顶点索引
     * @param j 边的另一个顶点索引
     */
    void removeEdge(int i, int j);

    /**
     * 打印顶点和邻接矩阵
     */
    void print();
};

/**
 * 构造函数
 * 遍历给定的顶点和边，依次添加到图中
 */
GrapAdjacencyMatrix::GrapAdjacencyMatrix(const std::vector<int> &_vertices, const std::vector<std::vector<int>> &edges)
{
    // 添加顶点
    for (int i = 0; i < _vertices.size(); i++)
    {
        addVertex(_vertices[i]);
    }

    // 添加边
    for (int i = 0; i < edges.size(); i++)
    {
        addEdge(edges[i][0], edges[i][1]);
    }
}

/**
 * 析构函数
 * 在此没有特殊操作
 */
GrapAdjacencyMatrix::~GrapAdjacencyMatrix()
{
}

/**
 * 添加顶点
 * 为每个现有的顶点在邻接矩阵中增加新的一列，并为新顶点创建对应的行
 */
void GrapAdjacencyMatrix::addVertex(int val)
{
    vertices.push_back(val); // 将新顶点加入顶点列表
    int n = vertices.size(); // 获取顶点的数量

    // 为新顶点添加新行
    adjMat.push_back(std::vector<int>(n, 0));

    // 为现有的每一行添加新列
    for (int i = 0; i < adjMat.size(); i++)
    {
        int len = adjMat[i].size();
        for (int j = 0; j < n - len; j++)
        {
            adjMat[i].push_back(0); // 新列初始化为0
        }
    }
}

/**
 * 删除顶点
 * 首先移除顶点，然后调整邻接矩阵，移除与该顶点相关的行和列
 */
void GrapAdjacencyMatrix::removeVertex(int idx)
{
    // 移除顶点
    for (int j = idx + 1; j < vertices.size(); j++)
    {
        vertices[j - 1] = vertices[j]; // 调整顶点位置
    }
    vertices.erase(vertices.end() - 1); // 删除最后一个顶点

    // 移除邻接矩阵的列
    for (int i = 0; i < adjMat.size(); i++)
    {
        for (int j = 0; j < adjMat[i].size(); j++)
        {
            if (j > idx)
            {
                adjMat[i][j - 1] = adjMat[i][j]; // 左移列
            }
        }
        adjMat[i].erase(adjMat[i].end() - 1); // 删除最后一列
    }

    // 移除邻接矩阵的行
    for (int i = 0; i < adjMat.size(); i++)
    {
        if (i > idx)
        {
            adjMat[i - 1] = adjMat[i]; // 上移行
        }
    }
    adjMat.erase(adjMat.end() - 1); // 删除最后一行
}

/**
 * 添加边
 * 在邻接矩阵中标记两个顶点之间的连接关系
 * @param i 边的第一个顶点
 * @param j 边的第二个顶点
 */
void GrapAdjacencyMatrix::addEdge(int i, int j)
{
    int n = vertices.size();
    // 检查索引是否合法且不是自循环边
    if (i == j || i < 0 || j < 0 || i >= n || j >= n)
        return;
    adjMat[i][j] = 1; // 在矩阵中标记边
    adjMat[j][i] = 1; // 无向图，i到j和j到i都标记为1
}

/**
 * 删除边
 * 在邻接矩阵中移除两个顶点之间的连接关系
 * @param i 边的第一个顶点
 * @param j 边的第二个顶点
 */
void GrapAdjacencyMatrix::removeEdge(int i, int j)
{
    int n = vertices.size();
    // 检查索引是否合法且不是自循环边
    if (i == j || i < 0 || j < 0 || i >= n || j >= n)
        return;
    adjMat[i][j] = 0; // 移除边
    adjMat[j][i] = 0; // 无向图，i到j和j到i都置为0
}

/**
 * 打印顶点和邻接矩阵
 */
void GrapAdjacencyMatrix::print()
{
    std::cout << "vertices: " << std::endl;
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i] << " "; // 打印顶点
    }
    std::cout << std::endl;

    std::cout << "adjMat: " << std::endl;
    for (int i = 0; i < adjMat.size(); i++)
    {
        for (int j = 0; j < adjMat[i].size(); j++)
        {
            std::cout << adjMat[i][j] << " "; // 打印邻接矩阵
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    // 初始化顶点和边
    std::vector<int> vertices = {3, 1, 2, 4};
    std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}};

    // 创建图的邻接矩阵表示
    GrapAdjacencyMatrix gam(vertices, edges);
    gam.print(); // 打印初始图

    // 添加新顶点
    gam.addVertex(5);
    gam.print(); // 打印更新后的图

    // 添加新边
    gam.addEdge(4, 1);
    gam.print(); // 打印更新后的图

    // 删除顶点
    gam.removeVertex(1);
    gam.print(); // 打印更新后的图

    // 删除边
    gam.removeEdge(2, 1);
    gam.print(); // 打印最终图

    return 0;
}