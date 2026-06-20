#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct edge
{
    int from;
    int to;
    int next;
    int capacity;
} Edge;
char name[505][4];
Edge arr[2005];
int head[2005];
int pre[2005];
int cnt = 0;
int getid(char *s)
{
    for (int i = 0; i < cnt; i++)
    {
        if (strcmp(name[i], s) == 0)
            return i;
    }
    strcpy(name[cnt], s);
    return cnt++;
}
int edgecnt = 0;
void addedge(int u, int v, int c)
{
    arr[edgecnt].to = v;
    arr[edgecnt].from = u;
    arr[edgecnt].capacity = c;
    arr[edgecnt].next = head[u];
    head[u] = edgecnt++;
    arr[edgecnt].to = u;
    arr[edgecnt].capacity = 0;
    arr[edgecnt].next = head[v];
    arr[edgecnt].from = v;
    head[v] = edgecnt++;
}
int BFS(int S, int T)
{
    int queue[2005];
    int front = 0, rear = 0;
    int vis[2005] = {0};
    vis[S] = 1;
    queue[rear++] = S;
    while (front < rear)
    {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = arr[i].next)
        {
            int v = arr[i].to;
            if (!vis[v] && arr[i].capacity > 0)
            {
                vis[v] = 1;
                pre[v] = i;
                if (v == T)
                    return 1;
                queue[rear++] = v;
            }
        }
    }
    return 0;
}
int main()
{
    memset(head, -1, sizeof(head));
    int n;
    char s[4], t[4];
    scanf("%3s %3s %d", s, t, &n);
    char s1[4], s2[4];
    int c;
    int S = getid(s);
    int T = getid(t);
    for (int i = 0; i < n; i++)
    {
        scanf("%3s %3s %d", s1, s2, &c);
        int u = getid(s1);
        int v = getid(s2);
        addedge(u, v, c);
    }
    int maxflow = 0;
    while (BFS(S, T))
    {
        int flow = 1e9;
        for (int v = T; v != S;)
        {
            int i = pre[v];
            if (arr[i].capacity < flow)
                flow = arr[i].capacity;
            v = arr[i].from;
        }
        for (int v = T; v != S;)
        {
            int i = pre[v];
            arr[i].capacity -= flow;
            arr[i ^ 1].capacity += flow;
            v = arr[i].from;
        }
        maxflow += flow;
    }
    printf("%d", maxflow);
    return 0;
}