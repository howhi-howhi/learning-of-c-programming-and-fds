#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 1000 + 5
typedef struct Tree *tree;
struct Tree
{
    int data;
    struct Tree *left;
    struct Tree *right;
};
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
int leftnum(int n)
{
    if (n <= 1)
        return 0;
    int h = (int)log2(n + 1);
    int x = n - ((1 << h) - 1);
    return ((1 << (h - 1)) - 1) + min(x, 1 << (h - 1));
}
tree create(int *arr, int l, int r)
{
    if (l > r)
        return NULL;
    int n = r - l + 1;
    int left = leftnum(n);
    int rootindex = l + left;
    tree root = (tree)malloc(sizeof(struct Tree));
    root->data = arr[rootindex];
    root->left = create(arr, l, rootindex-1);
    root->right = create(arr, rootindex + 1, r);
    return root;
}
void levelorder(tree root)
{
    if (root == NULL)
        return;
    tree q[MAXN];
    int front = 0, rear = 0;
    q[rear++] = root;
    int isfirst = 1;
    while (front < rear)
    {
        tree cur = q[front++];
        if (isfirst)
        {
            printf("%d", cur->data);
            isfirst = 0;
        }
        else
        {
            printf(" %d", cur->data);
        }
        if (cur->left)
            q[rear++] = cur->left;
        if (cur->right)
            q[rear++] = cur->right;
    }
}
// tree create_tree(int *arr,int *i)
// {
//   tree newnode=(tree)malloc(sizeof(struct Tree));
//   newnode->data=arr[*i];
//   *i=(*i)*2;
//   newnode->left=create_tree(arr,i);
//   (*i)++;
//   newnode->right=create_tree(arr,i);
//   return newnode;
// }The wrong version.
int main()
{
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(int), cmp);
    tree root = create(arr, 0, n - 1);
    levelorder(root);
    return 0;
    free(root);
    free(arr);
}
