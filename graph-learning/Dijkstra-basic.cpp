#include <stdio.h>
#include <math.h>
#define INF 1000000000
#define MAXV 100
typedef struct Node
{
    int v;
    struct Node *next;
} Node; // unweighted
typedef struct
{
    int u;
    int v;
    int w;
} edge; // 这里直接存储所有边，意为u->v,权值为w
typedef struct
{
    int v;
    int d;
} heapnode;
typedef struct
{
    heapnode *data;
    int size;
    int capacity;
} heap;
typedef struct node
{
    int v;
    int w;
    struct node *next;
} node; // weighted
typedef struct
{
    int dist;  // 起点到该点的距离，若known，则确定是最短距离
    int known; // 是否确定为最短距离。1--是，0--否
    int path;  // 前驱节点
} table;
typedef struct
{
    int front;
    int rear; // 注意。这里rear指向的是下一个有效位置，size=rear-front
    int data[MAXV];
} queue;
void enqueue(int x, queue *q)
{
    q->data[q->rear++] = x;
}
int dequeue(queue *q)
{
    return q->data[q->front++];
}
int isempty(queue *q)
{
    return (q->rear == q->front) ? 1 : 0;
}
void unweighted_BFS(int graph[MAXV][MAXV], table *t, queue *q, int n, int s)
{
    int i, j, u;
    for (int i = 0; i < n; i++)
    {
        t[i].dist = -1;
        t[i].known = 0;
        t[i].path = -1;
    }
    q->front = q->rear = 0;
    t[s].dist = 0;
    t[s].known = 1;
    enqueue(s, q);
    while (!isempty(q))
    {
        u = dequeue(q);
        for (j = 0; j < n; j++)
        {
            if (graph[u][j] && !t[j].known)
            {
                t[j].known = 1;
                t[j].dist = t[u].dist + 1;
                t[j].path = u;
                enqueue(j, q);
            }
        }
    }
} // 使用邻接矩阵，每次要扫描整行，时间复杂度O(N^2)
void unweighted_BFS_optimized(int n, int s, queue *q, table *t, Node **Graph)
{
    int i, u, v;
    Node *p;
    for (i = 0; i < n; i++)
    {
        t[i].dist = -1;
        t[i].known = 0;
        t[i].path = -1;
    }
    q->front = q->rear = 0;
    t[s].dist = 0;
    t[s].known = 1;
    enqueue(s, q);
    while (!isempty(q))
    {
        u = dequeue(q);
        p = Graph[u];
        while (p != NULL)
        {
            v = p->v;
            if (!t[v].known)
            {
                t[v].known = 1;
                t[v].dist = t[u].dist + 1;
                t[v].path = u;
                enqueue(v, q);
            }
            p = p->next;
        }
    }
}
void ini_heap(heap *h, int c)
{
    h->data = (heapnode *)malloc((c + 1) * sizeof(heapnode));
    h->size = 0;
    h->capacity = c;
}
heapnode pop(heap *h)
{
    heapnode ret = h->data[1];
    heapnode last = h->data[h->size--];
    int i = 1;
    int child;
    while (i * 2 <= h->size)
    {
        child = 2 * i;
        if (h->data[child + 1].d < h->data[child].d && child + 1 <= h->size)
            child++;
        if (last.d <= h->data[child].d)
            break;
        h->data[i] = h->data[child];
        i = child;
    }
    h->data[i] = last;
    return ret;
}
int emptyheap(heap *h)
{
    return h->size == 0;
}
void push(int v, int d, heap *h)
{
    int i;
    h->size++;
    i = h->size;
    h->data[i].v = v;
    h->data[i].d = d;
    while (i > 1 && h->data[i].d < h->data[i / 2].d)
    {
        heapnode temp = h->data[i];
        h->data[i] = h->data[i / 2];
        h->data[i / 2] = temp;
        i /= 2;
    }
}
int main()
{
    int graph[MAXV][MAXV];
    int n; // 顶点的总数
    scanf("%d", &n);
    int s;
    scanf("%d", &s);
    // 表示从哪个顶点开始的最短路径
    table t[n];
    for (int i = 0; i < n; i++)
    {
        t[i].dist = INF;
        t[i].known = 0;
        t[i].path = -1;
    }
    t[s].dist = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1;
        int min = INF;
        for (int j = 0; j < n; j++)
        {
            if (!t[j].known && t[j].dist < min)
            {
                min = t[j].dist;
                u = j;
            }
        } // 找到unknown中dist最小的点，即离起点最近但还没处理的点
        if (u == -1)
            break; // 没有找到
        t[u].known = 1;
        for (int j = 0; j < n; j++)
        {
            if (graph[u][j] != INF && !t[j].known)
            {
                if (t[u].dist + graph[u][j] < t[j].dist)
                {
                    t[j].dist = t[u].dist + graph[u][j];
                    t[j].path = u;
                    // 借助u来寻找其他的最小值
                }
            }
        }
    }
}
// 邻接矩阵的表示方法，每次要遍历找最小值和遍历修改t[j]，需要两层循环，时间复杂度O(N^2)
// 优化：邻接表加最小堆
void weighted_optimized(int n, int s, node **graph, table *t)
{
    // n是顶点总数，s是起始位置，graph存储图（邻接表），t存储路径
    int i, u, v, w;
    node *p;
    heap h;
    heapnode cur;
    ini_heap(&h, n * n);
    for (i = 0; i < n; i++)
    {
        t[i].dist = INF;
        t[i].known = 0;
        t[i].path = -1;
    }
    t[s].dist = 0;
    push(s, 0, &h);
    while (!emptyheap(&h))
    {
        cur = pop(&h); // 从堆里取得d最小的点
        u = cur.v;
        if (t[u].known)
            continue;
        t[u].known = 1;
        p = graph[u]; // p是node*，是链表节点
        // 从graph[u]开始，逐个扫描u的邻居
        while (p != NULL)
        {
            v = p->v;
            w = p->w;
            if (!t[v].known && t[u].dist + w < t[v].dist)
            {
                t[v].dist = t[u].dist + w;
                t[v].path = u;
                push(v, t[v].dist, &h);
            }
            p = p->next;
        }
    }
    free(h.data);
}
void bellmanford(int n, int m, edge *e, int s, table *t)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        t[i].dist = INF;
        t[i].path = -1;
    } // 因为有负边的存在，所以即使known，也无法确保是最短路径，这里不用known
    t[s].dist = 0;
    for (i = 1; i < n - 1; i++)//因为最多有n-1个边，所以传递n-1次，可以确保得到最终结果
    {
        for (j = 0; j < m; j++)
        {
            int u = e[j].u;
            int v = e[j].v;
            int w = e[j].w;
            if (t[u].dist != INF && t[u].dist + w < t[v].dist)
            {
                t[v].dist = t[u].dist + w;
                t[v].path = u;
            }
        }
    }
}