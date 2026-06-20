#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10 /* maximum number of vertices */
typedef int Vertex;    /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode
{
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode
{
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV(Vertex V)
{
    printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V));

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents(G, PrintV);
    return 0;
}

/* Your function will be put here */
int top = -1;
void dfs1(Graph G, Vertex v, Vertex *stack, int *visited)
{
    visited[v] = 1;
    for (PtrToVNode p = G->Array[v]; p != NULL; p = p->Next)
    {
        Vertex w = p->Vert;
        if (!visited[w])
            dfs1(G, w, stack, visited);
    }
    stack[++top] = v;
}
void dfs2(Graph G,Vertex v, int *visited, Vertex *stack, void (*visit)(Vertex V))
{
    visited[v]=1;
    visit (v);
    for (PtrToVNode p=G->Array[v];p!=NULL;p=p->Next)
    {
        Vertex w=p->Vert;
        if (!visited[w])
            dfs2(G,w,visited,stack,visit);
    }

}
void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{
    int vertex = G->NumOfVertices;
    int visited[vertex] = {0};
    Vertex stack[vertex];
    for (int i = 0; i < vertex; i++)
    {
        if (!visited[i])
            dfs1(G, i, stack, visited);
    }
    Graph gg = (Graph)malloc(sizeof(struct GNode));
    gg->NumOfEdges = G->NumOfEdges;
    gg->NumOfVertices = G->NumOfVertices;
    gg->Array = (PtrToVNode *)malloc(vertex * sizeof(PtrToVNode));
    for (int i = 0; i < vertex; i++)
        gg->Array[i] = NULL;
    for (int i = 0; i < vertex; i++)
    {
        for (PtrToVNode p = G->Array[i]; p != NULL; p = p->Next)
        {
            Vertex w = p->Vert;
            PtrToVNode newnode = (PtrToVNode)malloc(sizeof(struct VNode));
            newnode->Vert = i;
            newnode->Next = gg->Array[w];
            gg->Array[w] = newnode;
        }
    }
    for (int i = 0; i < vertex; i++)
        visited[i] = 0;
    while (top!=-1)
    {
        Vertex v=stack[top--];
        if (!visited[v])
        {
            dfs2(gg,v,visited,stack,visit);
            printf("\n");
        }
    }
}
