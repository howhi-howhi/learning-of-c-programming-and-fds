//根据中序遍历和后序遍历，建立一棵树，并按照“之”字形，对每一层进行遍历
#include <stdio.h>
#include <stdlib.h>
struct binary_tree
{
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
};
typedef binary_tree *Tree;
Tree createtree(int inorder[], int postorder[], int in_start, int in_end, int po_start, int po_end)
//根据中序遍历和后序遍历，可以唯一确定一棵树
{
    if (in_start > in_end || po_start > po_end)
        return NULL;//确保不越界
    int rootvalue = postorder[po_end];//后序遍历，父节点的值放在end 选择end 开始建立
    Tree root = (Tree)malloc(sizeof(struct binary_tree));
    root->data = rootvalue;
    root->left = root->right = NULL;
    int index;
    for (int i = in_start; i <= in_end; i++)
    {
        if (inorder[i] == rootvalue)
        {
            index = i;//查找当前节点Value在inorder中的位置，方便递归
            break;
        }
    }//根据中序遍历，index为分界线，index-1及其左侧是左子树，index+1及其右侧是右子树
    int left_length = index - in_start;//用于计算postorder中的下标范围。
    root->left = createtree(inorder, postorder, in_start, index - 1, po_start, po_start + left_length - 1);//注意后序遍历的方式，左--右--中 
    //po_start--po_start+left_length-1  是左子树的范围   po_start+left_length---po_end-1 是右子树范围
    root->right = createtree(inorder, postorder, index + 1, in_end, po_start + left_length, po_end - 1);
    return root;//返回当前节点
}
void zigzag(Tree root, int n)
{
    if (!root)
        return;
    Tree queue[n];//使用队列，实现遍历
    int front = 0, rear = 0;
    queue[rear++] = root;//当前节点入队
    int x = 1, first = 1;
    while (front < rear)
    {
        int level_size = rear - front;
        int level[n];
        for (int i = 0; i < level_size; i++)
        {
            Tree node = queue[front++];//临时保存当前队首节点，同时front加1
            level[i] = node->data;//当前节点数值写入level数组
            if (node->left)
                queue[rear++] = node->left;//左子节点先入队
            if (node->right)
                queue[rear++] = node->right;//右子节点后入队
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
