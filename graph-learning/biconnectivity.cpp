#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 1000
#define MAXE 2000000
// 10 11
// 0 1
// 1 2
// 2 4
// 4 3
// 1 3
// 3 5
// 5 6
// 5 7
// 6 7
// 7 8
// 7 9
// 测试数据
typedef struct edge
{
    int to;
    int next;
} Edge;
int head[MAXV];
Edge edge[MAXE];
int vis[MAXV];
int parent[MAXV];
int treeu[MAXE];
int treev[MAXE];
int backu[MAXE];
int backv[MAXE];
int dfn[MAXV];
int low[MAXV];
int cut[MAXV];
int tcnt = 0;
int bcnt = 0;
int timer = 0;
int cnt = 0;
void addedge(int u, int v)
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}
void traversal(int u)
{
    printf("%d ---", u);
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        printf("%d ", v);
    }
    printf("\n");
}
void dfs(int u)
{
    vis[u] = 1;
    printf("%d ", u);
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!vis[v])
            dfs(v);
    }
}
void spanning_tree(int u, int fa) // u是dfs的起始点，fa是u的父亲
{
    vis[u] = 1;
    parent[u] = fa;
    dfn[u] = low[u] = timer++;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!vis[v])
        {
            treeu[tcnt] = u;
            treev[tcnt] = v;
            tcnt++;
            spanning_tree(v, u);
            low[u] = ((low[u] < low[v]) ? low[u] : low[v]);
        }
        else if (v != fa)
        {
            backu[bcnt] = u;
            backv[bcnt] = v;
            bcnt++;
            low[u] = ((low[u] < dfn[v]) ? low[u] : dfn[v]);
        }
    }
}
void DFS(int u, int fa)
{
    dfn[u] = low[u] = timer++;
    int child = 0;

    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;

        if (dfn[v] == -1)
        {
            child++;
            DFS(v, u);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (fa != -1 && low[v] >= dfn[u])
               cut[u]=1;
        }
        else if (v != fa)
        {
            low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
        }
    }

    if (fa == -1 && child >= 2)
      cut[u]=1;

}
int main()
{
    memset(head, -1, sizeof(head));
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(cut,0,sizeof(cut));
    int vertexs, edges;
    scanf("%d %d", &vertexs, &edges);
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    // for (int i = 0; i < vertexs; i++)
    //     traversal(i);//验证图读入是否正确
    // dfs(1); //dfs检验
    printf("The articulation points:\n");
    int rootcnt = 0;
    int u = 1; // 从1开始dfs，可修改
    DFS(u, -1);
    for (int i=0;i<vertexs;i++)
    {
        if (cut[i])
        printf("%d ",i);
    }
    // spanning_tree(u,-1);
    // for (int i = 0; i < edges; i++)
    // {
    //     if (treeu[i] == u)
    //         rootcnt++;
    // }
    // if (rootcnt >= 2)
    //     printf("%d ", u);
    // for (int i=1;i<vertexs;i++)
    // {
    //     int isarticulation=0;
    //    for (int j=0;j<edges;j++)
    //    {
    //        if (treeu[j]==i)
    //        {
    //         int s=treev[j];
    //         if (low[s]>=dfn[i])
    //         isarticulation=1;
    //         break;
    //        }
    //    }
    //    if (isarticulation)
    //    printf("%d ",i);
    // }
    return 0;
}
