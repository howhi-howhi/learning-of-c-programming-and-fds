#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

Edge edge[200005];
int parent[200005];
int temp[200005];
int cu[200005], cv[200005];

int n, m;

int cmp(const void *a, const void *b)
{
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

/* ===== 主DSU ===== */
int find(int x)
{
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y) parent[x] = y;
}

/* ===== 临时DSU（用于同权检测） ===== */
int tfind(int x)
{
    if (temp[x] == x) return x;
    return temp[x] = tfind(temp[x]);
}

/* ===================== */

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);

    qsort(edge, m, sizeof(Edge), cmp);

    int mst_weight = 0, used = 0;
    int unique = 1;

    for (int i = 0; i < m; )
    {
        int j = i;

        /* ===== 同权分组 ===== */
        while (j < m && edge[j].w == edge[i].w) j++;

        int cnt = 0;

        /* ===== 记录候选边（基于当前DSU） ===== */
        for (int k = i; k < j; k++)
        {
            int u = find(edge[k].u);
            int v = find(edge[k].v);

            if (u != v)
            {
                cu[cnt] = u;
                cv[cnt] = v;
                cnt++;
            }
        }

        /* ===== 初始化临时DSU ===== */
        for (int k = 1; k <= n; k++)
            temp[k] = k;

        /* ===== 检查是否形成环（判断唯一性） ===== */
        for (int k = 0; k < cnt; k++)
        {
            int fu = tfind(cu[k]);
            int fv = tfind(cv[k]);

            if (fu == fv)
            {
                unique = 0;
                goto BUILD;
            }
            temp[fu] = fv;
        }

    BUILD:

        /* ===== 正常Kruskal合并 ===== */
        for (int k = i; k < j; k++)
        {
            int u = edge[k].u;
            int v = edge[k].v;

            if (find(u) != find(v))
            {
                unite(u, v);
                mst_weight += edge[k].w;
                used++;
            }
        }

        i = j;
    }

    /* ===================== 输出 ===================== */

    if (used < n - 1)
    {
        printf("No MST\n");

        int comp = 0;
        for (int i = 1; i <= n; i++)
            if (find(i) == i) comp++;

        printf("%d\n", comp);
    }
    else
    {
        printf("%d\n", mst_weight);
        printf("%s\n", unique ? "Yes" : "No");
    }

    return 0;
}