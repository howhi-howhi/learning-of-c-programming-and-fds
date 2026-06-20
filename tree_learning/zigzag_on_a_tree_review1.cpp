#include <stdio.h>
#include <stdlib.h>
#define MAXN 30 + 5
typedef struct Tree *tree;
struct Tree
{
    int data;
    struct Tree *left;
    struct Tree *right;
};
tree build(int *in, int *post, int inl, int inr, int postl, int postr)
{
    if (inl > inr || postl > postr)
        return NULL;
    tree root = (tree)malloc(sizeof(struct Tree));
    root->data = post[postr];
    root->left = root->right = NULL;
    int cur = post[postr];
    int index;
    for (index = inl; index <= inr; index++)
        if (in[index] == cur)
            break;
    int leftlength = index - inl;
    root->left = build(in, post, inl, index - 1, postl, postl + leftlength - 1);
    root->right = build(in, post, index + 1, inr, postl + leftlength, postr - 1);
    return root;
}
void zigzag(tree root, int n)
{
    if (root == NULL)
        return;
    tree queue[MAXN];
    int rear = 0, front = 0;
    queue[rear++] = root;
    int lefttoright = 0;
    int isfirst = 1;
    while (front < rear)
    {
        int levelsize = rear - front;
        int level[MAXN];
        for (int i = 0; i < levelsize; i++)
        {
            tree cur = queue[front++];
            level[i] = cur->data;
            if (cur->left)
                queue[rear++] = cur->left;
            if (cur->right)
                queue[rear++] = cur->right;
        }
        if (lefttoright)
        {
            for (int i = 0; i < levelsize; i++)
            {
                if (isfirst)
                {
                    printf("%d", level[i]);
                    isfirst = 0;
                }
                else
                    printf(" %d", level[i]);
            }
        }
        else
        {
            for (int i = levelsize - 1; i >= 0; i--)
            {
                if (isfirst)
                {
                    printf("%d", level[i]);
                    isfirst = 0;
                }
                else
                    printf(" %d", level[i]);
            }
        }
        lefttoright=1-lefttoright;
   }
}
int main()
{
    int n;
    scanf("%d", &n);
    int *in = (int *)malloc(n * sizeof(int));
    int *post = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &post[i]);
    tree T = build(in, post, 0, n - 1, 0, n - 1);
    zigzag(T,n);
    return 0;
}