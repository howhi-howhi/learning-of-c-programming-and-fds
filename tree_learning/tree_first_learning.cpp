#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
typedef struct TreeNode
{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} tree; // it includes three elements: data, left and right
tree *createnode(char value)
{
    tree *newnode = (tree *)malloc(sizeof(tree));
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// There are four ways to traverse a binary tree: pre-order, in-order, post-order and level-order.
void preorder(tree *root)
{
    if (!root)
        return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}
void inorder(tree *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}
void postorder(tree *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}
tree *quene[MAXN];
int front = 0, rear = 0;
void enqueue(tree *x)
{
    quene[rear] = x;
    rear = (rear + 1) % MAXN;
}
tree *dequeue()
{
    tree *t = quene[front];
    front = (front + 1) % MAXN;
    return t;
}
int empty()
{
    return front == rear;
}
void levelorder(tree *root)
{
    if (!root)
        return;
    front = rear = 0;
    enqueue(root);
    while (!empty())
    {
        tree *t = dequeue();
        printf("%c ", t->data);
        if (t->left)
            enqueue(t->left);
        if (t->right)
            enqueue(t->right);
    }
}
int main()
{
    tree *A = createnode('A');
    tree *B = createnode('B');

    tree *C = createnode('C');
    tree *D = createnode('D');
    tree *E = createnode('E');
    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;
    printf("Pre-order: ");
    preorder(A);
    printf("\nIn-order: ");
    inorder(A);
    printf("\nPost-order: ");
    postorder(A);
    printf("\nLevel-order: ");
    levelorder(A);
    return 0;
}
