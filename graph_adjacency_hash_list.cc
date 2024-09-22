#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

/* 定义图的顶点结构体 */
struct Vertex
{
    int val;                        /* 顶点的值 */
    Vertex(int _val) : val(_val) {} /* 构造函数，初始化顶点的值 */
};

/* 使用邻接哈希表实现的图类 */
class GraphAdjacencyHashList
{
private:
    std::vector<Vertex *> vertices;                                               /* 存储所有顶点的容器,遍历的时候可以用map.first代替，这里只是分开清楚一点*/
    std::unordered_map<Vertex *, std::unordered_map<Vertex *, Vertex *>> adjList; /* 邻接表，使用哈希表嵌套哈希表 */
    void dfs(std::unordered_set<Vertex *> &visited, std::vector<Vertex *> &res, Vertex *vert);

public:
    GraphAdjacencyHashList(const std::vector<Vertex *> &_vertices, const std::vector<std::vector<Vertex *>> &edges); /* 构造函数 */
    ~GraphAdjacencyHashList();                                                                                       /* 析构函数 */
    void addVertex(Vertex *vertex);                                                                                  /* 添加顶点 */
    void removeVertex(int idx);                                                                                      /* 移除顶点 */
    void addEdge(Vertex *a, Vertex *b);                                                                              /* 添加边 */
    void removeEdge(Vertex *a, Vertex *b);                                                                           /* 移除边 */
    void print();                                                                                                    /* 打印图的邻接表 */
    std::vector<Vertex *> graphBFS(Vertex *startVert);
    std::vector<Vertex *> graphDFS(Vertex *startVert);
};

/* 构造函数：初始化图结构，接收顶点和边 */
GraphAdjacencyHashList::GraphAdjacencyHashList(const std::vector<Vertex *> &_vertices, const std::vector<std::vector<Vertex *>> &edges)
{
    /* 添加所有顶点到图中 */
    for (int i = 0; i < _vertices.size(); i++)
    {
        addVertex(_vertices[i]);
    }
    /* 添加所有边 */
    for (int i = 0; i < edges.size(); i++)
    {
        addEdge(edges[i][0], edges[i][1]);
    }
}

/* 析构函数 */
GraphAdjacencyHashList::~GraphAdjacencyHashList()
{
    /* 不做特殊处理，默认析构行为 */
}

/* 添加顶点到图中 */
void GraphAdjacencyHashList::addVertex(Vertex *vertex)
{
    vertices.push_back(vertex);                                 /* 将顶点加入vertices列表 */
    adjList[vertex] = std::unordered_map<Vertex *, Vertex *>(); /* 在邻接表中为该顶点创建一个空的邻接点列表 */
}

/* 根据索引移除顶点 */
void GraphAdjacencyHashList::removeVertex(int idx)
{
    /* 移除该顶点与其他顶点的边 */
    for (int i = 0; i < vertices.size(); i++)
    {
        removeEdge(vertices[i], vertices[idx]);
    }
    /* 从邻接表中删除该顶点的记录 */
    adjList.erase(vertices[idx]);
    /* 从vertices列表中删除该顶点 */
    vertices.erase(vertices.begin() + idx);
}

/* 添加两个顶点之间的边 */
void GraphAdjacencyHashList::addEdge(Vertex *a, Vertex *b)
{
    if (a == b)
        return;
    adjList[a][b] = b; /* 在a的邻接表中加入b */
    adjList[b][a] = a; /* 在b的邻接表中加入a，实现无向图 */
}

/* 移除两个顶点之间的边 */
void GraphAdjacencyHashList::removeEdge(Vertex *a, Vertex *b)
{
    if (a == b)
        return;
    adjList[a].erase(b); /* 从a的邻接表中移除b */
    adjList[b].erase(a); /* 从b的邻接表中移除a */
}
void GraphAdjacencyHashList::print()
{
    /* 遍历所有顶点 */
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << "Vertex " << vertices[i]->val << " -> "; /* 输出当前顶点 */
        /* 遍历该顶点的所有邻接点 */
        for (auto &neighbor : adjList[vertices[i]])
        {
            std::cout << neighbor.second->val << " -> "; /* 输出邻接点 */
        }
        std::cout << "null" << std::endl; /* 输出结束符 */
    }
    std::cout << std::endl; /* 输出换行符 */

    /* 以下方式有问题 */

    // for (int i = 0; i < vertices.size(); i++)
    // {
    //     std::cout << "Vertex " << vertices[i]->val << " -> ";
    //     for (int j = 0; j < adjList[vertices[i]].size() - 1; j++)
    //     {
    //         if (adjList[vertices[i]].count(vertices[j]) == 0)
    //             continue;
    //         std::cout << adjList[vertices[i]][vertices[j]]->val << " -> ";
    //     }
    //     if (adjList[vertices[i]].count(vertices[vertices.size() - 1]) != 0)
    //     {
    //         std::cout << adjList[vertices[i]][vertices[vertices.size() - 1]]->val;
    //     }
    //     std::cout << std::endl;
    // }
}
std::vector<Vertex *> GraphAdjacencyHashList::graphBFS(Vertex *startVert)
{
    std::queue<Vertex *> que;
    que.push(startVert);
    std::unordered_set<Vertex *> visited = {startVert};
    std::vector<Vertex *> res;
    while (!que.empty())
    {
        Vertex *vertex = que.front();
        que.pop();
        res.push_back(vertex);
        for (const auto &neighbor : adjList[vertex])
        {
            if (visited.count(neighbor.second))
                continue;
            que.push(neighbor.second);
            visited.emplace(neighbor.second);
        }
    }
    return res;
}
void GraphAdjacencyHashList::dfs(std::unordered_set<Vertex *> &visited, std::vector<Vertex *> &res, Vertex *vert)
{
    res.push_back(vert);
    visited.emplace(vert);
    for (const auto &adjvert : adjList[vert])
    {
        if (visited.count(adjvert.second))
            continue;
        dfs(visited, res, adjvert.second);
    }
}
std::vector<Vertex *> GraphAdjacencyHashList::graphDFS(Vertex *startVert)
{
    std::vector<Vertex *> res;
    std::unordered_set<Vertex *> visited;
    dfs(visited, res, startVert);
    return res;
}
int main()
{
    std::vector<Vertex *> vertices; /* 创建一个顶点数组 */
    Vertex vert1(1);
    Vertex vert2(2);
    Vertex vert3(3);
    Vertex vert4(4);

    /* 将顶点加入数组 */
    vertices.push_back(&vert1);
    vertices.push_back(&vert2);
    vertices.push_back(&vert3);
    vertices.push_back(&vert4);

    /* 定义边的列表 */
    std::vector<std::vector<Vertex *>> edges = {{&vert1, &vert2}, {&vert2, &vert3}, {&vert3, &vert4}};

    /* 创建图对象 */
    GraphAdjacencyHashList gahl(vertices, edges);

    /* 打印图的邻接表 */
    gahl.print();

    /* 添加新顶点 */
    Vertex vert5(5);
    gahl.addVertex(&vert5);
    gahl.print();

    /* 添加新边 */
    gahl.addEdge(&vert3, &vert5);
    gahl.print();

    std::vector<Vertex *> res = gahl.graphBFS(&vert2);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i]->val << " ";
    }
    std::cout << std::endl
              << std::endl;
    res = gahl.graphDFS(&vert1);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i]->val << " ";
    }
    std::cout << std::endl
              << std::endl;
    /* 移除边 */
    gahl.removeEdge(&vert2, &vert3);
    gahl.print();

    /* 移除顶点 */
    gahl.removeVertex(2);
    gahl.print();

    return 0; /* 程序结束 */
}