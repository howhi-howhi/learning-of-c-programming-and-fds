#include <stdio.h>
#include <stdlib.h>
struct binary_tree
{
    int data;
    struct binary_tree *left;
    binary_tree *right;
};
typedef binary_tree *Tree;
Tree createtree(int inorder[], int postorder[], int in_start, int in_end, int po_start, int po_end)
{
    if (in_start > in_end || po_start > po_end)
        return NULL;
    int rootvalue = postorder[po_end];
    Tree root = (Tree)malloc(sizeof(struct binary_tree));
    root->data = rootvalue;
    root->left = root->right = NULL;
    int index;
    for (int i = in_start; i <= in_end; i++)
    {
        if (inorder[i] == rootvalue)
        {
            index = i;
            break;
        }
    }
    int left_length = index - in_start;
    root->left = createtree(inorder, postorder, in_start, index - 1, po_start, po_start + left_length - 1);
    root->right = createtree(inorder, postorder, index + 1, in_end, po_start + left_length, po_end - 1);
    return root;
}
void zigzag(Tree root, int n)
{
    if (!root)
        return;
    Tree queue[n];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int x = 1, first = 1;
    while (front < rear)
    {
        int level_size = rear - front;
        int level[n];
        for (int i = 0; i < level_size; i++)
        {
            Tree node = queue[front++];
            level[i] = node->data;
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
        if (x)
        {
            for (int i = level_size - 1; i >= 0; i--)
            {
                if (!first)
                    printf(" ");
                printf("%d", level[i]);
                first = 0;
            }
        }
        else
        {
            for (int i = 0; i < level_size; i++)
            {
                if (!first)
                    printf(" ");
                printf("%d", level[i]);
                first = 0;
            }
        }
        x=1-x;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    Tree root1 = NULL, root2 = NULL;
    int arr1[n], arr2[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr2[i]);
    }
    Tree root = createtree(arr1, arr2, 0, n - 1, 0, n - 1);
    zigzag(root, n);
    return 0;
}