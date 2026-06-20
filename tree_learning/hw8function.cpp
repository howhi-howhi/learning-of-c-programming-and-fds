#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false,
    true
} bool;
#define MaxVertexNum 10 /* maximum number of vertices */
typedef int Vertex;     // 顶点      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        // 邻接顶点
    PtrToAdjVNode Next; // 下一个边节点
};

typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];
// 注意定义：结构体只有一个成员。即指向第一个邻边的指针firstedge
// 定义一个数组类型 struct Vnode [MaxVertexnum] 等价于Adjlist类型
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;    // 节点数量
    int Ne;    // 边数量
    AdjList G; // 所有节点的，各自的邻接边
}; // 存储整个图
typedef PtrToGNode LGraph;
// lgraph强调是一个图，ptrtonode强调是一个指针，但是二者逻辑一样

LGraph ReadG(); /* details omitted */

bool IsTopSeq(LGraph Graph, Vertex Seq[]);

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < G->Nv; j++)
            scanf("%d", &Seq[j]);
        if (IsTopSeq(G, Seq) == true)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}

/* Your function will be put here */
bool IsTopSeq(LGraph Graph, Vertex Seq[])
{
    int indegree[MaxVertexNum] = {0};
    int n = Graph->Nv;
    for (int i = 0; i < n; i++)
    {
        PtrToAdjVNode p = Graph->G[i].FirstEdge;
        while (p)
        {
            indegree[p->AdjV]++;
            p = p->Next;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int vv = Seq[i]-1;
        if (indegree[vv] != 0)
            return false;
        PtrToAdjVNode p = Graph->G[vv].FirstEdge;
        while (p)
        {
            indegree[p->AdjV]--;
            p=p->Next;
        }
    }
    return true;
}