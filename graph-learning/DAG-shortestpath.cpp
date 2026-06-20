#include <stdio.h>
#include <stdlib.h>
#define MAXV 100
#define INF 100000000
typedef struct node
{
    int v;
    int w;
    struct node *next;
} node;
node *graph[MAXV];
typedef struct
{
    int dist;
    int path;
} table;
void compute_indegree(int n, node **graph, int *indegree)
{
    for (int i = 0; i < n; i++)
        indegree[i] = 0;
    for (int u = 0; u < n; u++)
    {
        node *p = graph[u];
        while (p)
        {
            indegree[p->v]++;
            p = p->next;
        }
    }
}
int topsort(int n, node **graph, int *top)
{
    int indegree[MAXV];
    compute_indegree(n, graph, indegree);
    int queue[MAXV];
    int front = 0, rear = 0;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            queue[rear++] = i; // 把入度为0的点先加入队列
    int count = 0;
    while (front < rear)
    {
        int u = queue[front++];
        top[count++] = u; // 取出队的元素，入队早，出队早。对应拓扑排序在前
        node *p = graph[u];
        while (p)
        {
            indegree[p->v]--;
            if (indegree[p->v] == 0)
                queue[rear++] = p->v;
            p = p->next;
        }
    }
    return count; // count=0,有环；count=n，无环
}
void DAGshortestpath(int n, int s, node **graph, table *t)
{
    int top[MAXV];
    int cnt = topsort(n, graph, top);
    if (cnt < n)
    {
        printf("图中有环,无法使用DAG\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        t[i].dist = INF;
        t[i].path = -1;
    }
    t[s].dist = 0;
    for (int i = 0; i < n; i++)
    {
        int u = top[i];
        if (t[u].dist == INF)
            continue;
        node *p=graph[u];
        while (p)
        {
            int v=p->v;
            int w=p->w;
            if (t[u].dist+w<t[v].dist)
            {
                t[v].dist=t[u].dist+w;
                t[v].path=u;
             }
             p=p->next;
        }
    }
}