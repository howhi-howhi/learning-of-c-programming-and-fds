#include <stdio.h>
#include <stdlib.h>
#define MAXV 1010//顶点总数不超过1e3，留出额外一些空间，取1010
#define MAXE 200005//读入边的总数不超过1e5，但是无向图每次读入一组数据要建边两次，取2e5+5
#define INF 100000000//权重不超过100，顶点数不超过1000，确保正常情况下无法达到INF的路径长度，是可靠的判断标准，在找最小值等时候发挥作用
typedef struct Edge
{
    int to;            // 到达节点是谁
    int weight;        // 权重
    struct Edge *next; // 把和同一个点相连的边串成一个链表
} Edge;                // 存储边
Edge *graph[MAXV];     // 顶点数最大为1000，选择MAXV为1010
// Nv<=1e3,Ne<=1e5
// 根据边和顶点的关系，该图相对稀疏，适合用邻接表储存
int dist[MAXV];                   // 某一点到源点，目前确认的最小距离
int visited[MAXV];                // visited的含义是最短路径已经确定
void AddEdge(int u, int v, int w) // 给定起点u，到达v，权重为w的一条边，加入邻接表
{
    Edge *e = (Edge *)malloc(sizeof(Edge)); // 分配内存
    e->to = v;                              // 到达v
    e->weight = w;                          // 权重为w
    e->next = graph[u];                     // 头插法建立链表，先将新边e和邻接表接起来
    graph[u] = e;                           // 更新头部位置为e
}
void init(int Nv)
{
    for (int i = 1; i <= Nv; i++) // 注意索引是1~Nv
    {
        dist[i] = INF;
        visited[i] = 0;
    } // 初始化数组，路径长记作一个很大整数，在本题不可能达到
    // 初始化到访标记为0（实际上visited含义是确定最短路径）
}
int check(int seq[], int Nv) // 检验是否是合法Dijkstra序列的函数
{
    init(Nv);                    // 初始化dist和visited数组
    dist[seq[0]] = 0;            // 默认数组第一个位置，是源点，初始化源点dist=0
    for (int i = 0; i < Nv; i++) // 对每一个数组元素进行检验
    {
        int u = seq[i]; // 取出当前元素
        int min = INF;  // 初始化min为INF，是路径长度无法达到的值，确保找最小值
        for (int j = 1; j <= Nv; j++)
        {
            if (!visited[j] && dist[j] < min)
                min = dist[j]; // 找到所有未确定最小dist的元素中，dist最小的一个，这是Dijkstra合法的访问顺序
        }
        if (dist[u] != min)
            return 0;                                    // 如果当前元素seq[i]，对应dist[u]，不具有最小的dist（在未确定最小dist的元素中），则序列不合法
        visited[u] = 1;                                  // 标记，已经确定最小dist
        for (Edge *e = graph[u]; e != NULL; e = e->next) // 以当前节点为起点，扩展至周围与之直接相连的边，进行松弛操作
        {
            int v = e->to;     // 边所连的下一个顶点
            int w = e->weight; // 权重
            if (!visited[v] && dist[u] + w < dist[v])
                dist[v] = dist[u] + w; // 对边松弛，更新dist
        }
    }
    return 1; // 如果以上每一次检验都合法，那么是一个合法的Dijkstra序列
}
void freegraph(int Nv) // 用于释放邻接表内存
{
    for (int i = 1; i <= Nv; i++) // 遍历graph数组
    {
        Edge *cur = graph[i];
        while (cur != NULL)
        {
            Edge *tmp = cur; // 取出当前节点
            cur = cur->next; // 继续遍历
            free(tmp);       // 释放节点内存
        }
        graph[i] = NULL; // 最后改变指向，避免野指针
    }
}
int main()
{
    int Nv, Ne;               // 顶点和边的总数
    scanf("%d %d", &Nv, &Ne); // 读入
    for (int i = 1; i <= Nv; i++)
        graph[i] = NULL; // 初始化graph，便于头插法建立邻接表
    for (int i = 0; i < Ne; i++)
    {
        int end1, end2, weight; // 分别读入两端和权重
        scanf("%d %d %d", &end1, &end2, &weight);
        AddEdge(end1, end2, weight);
        AddEdge(end2, end1, weight); // 因为是无向图，所以必须双向建立边，否则会形成有向图的模式导致错误
    }
    int k; // 序列总数
    scanf("%d", &k);
    int **data = (int **)malloc(k * (sizeof(int *))); // 用动态内存分配，把数组放在堆上更稳健
    for (int i = 0; i < k; i++)
    {
        data[i] = (int *)malloc(Nv * sizeof(int)); // 分配一维数组
        for (int j = 0; j < Nv; j++)               // 注意使用0-base索引，与check函数一致
            scanf("%d", &data[i][j]);
    }
    for (int i = 0; i < k; i++) // 遍历所有序列
    {
        if (check(data[i], Nv)) // check=1，序列合法，输出Yes；
            printf("Yes\n");
        else
            printf("No\n"); // check=0，不是合法的dijkstra序列，输出No
    }
    for (int i = 0; i < k; i++)
        free(data[i]);
    free(data);//释放数组内存
    freegraph(Nv);//释放邻接表内存
    return 0;
}
