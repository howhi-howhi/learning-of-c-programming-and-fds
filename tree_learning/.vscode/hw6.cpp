#include <stdio.h>
#include <stdlib.h>
typedef struct Tree *tree;
struct Tree
{
    int *elements;
    int capacity;
    int size;
};
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
void inorder(int i,tree T,int a[])
{
    if (i>T->capacity-1)
    return;
    inorder(2*i,T,a);
    T->elements[i]=a[T->size++];
    inorder(2*i+1,T,a);
}
int main()
{
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);
    tree Y = (tree)malloc(sizeof(struct Tree));
    Y->capacity = n + 1;
    Y->size = 0;
    Y->elements = (int *)malloc(sizeof(int) * Y->capacity);
    inorder(1, Y, a);
    int isfirst=1;
    for (int i = 1; i < Y->capacity; i++)     
    {
        if (isfirst)
        {
            isfirst=0;
        }
        else
        {
            printf(" ");
        }
        printf("%d", Y->elements[i]);
    }
    free(a);
    free(Y->elements);
    free(Y);
    return 0;
}