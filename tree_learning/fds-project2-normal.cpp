#include <stdio.h>
#include <stdlib.h>
typedef struct binary_tree
{
    long long val; // val may be very large,so we choose long-long to ensure security.
    int parent;    // parent,is used to find the root.
    int left;      // left child.
    int right;     // right child.
} tree;
// Use indices to build parent-child relationships,
// so the tree is implemented with an array and structs.
void insert(tree *t, int root, int i)
// this function is used to insert a node into the tree,we can create a new tree.
{
    int curr = root;
    // curr is the reference node.
    // If the value to insert is smaller than curr, go to the left subtree;
    // otherwise (greater or equal), go to the right subtree.
    for (;;)// Keep looping until we find the right place.
    {
        if (t[i].val < t[curr].val)
        {
            if (t[curr].left == -1)//-1 means no left child,and we insert the new node here.
            {
                t[curr].left = i;
                return;
            }
            curr = t[curr].left;//if the parent node has a left child, we move down to the left child and continue searching.
        }
        else
        {
            if (t[curr].right == -1)//-1 means no right child,and we insert the new node here.
            {
                t[curr].right = i;
                return;
            }
            curr = t[curr].right;//if the parent node has a right child, we move down to the right child and continue searching.
        }
    }
}
void preorder_print(tree *t, int root, int *first)//first must be a pointer, because we need to change its value in the function to control the format of the output.
//according to the requirement,we need to print the tree in preorder traversal.
{
    if (root == -1)//-1 means no node,so we return.
        return;
    if (*first)//first is used to control the format of the output,if it's the first node we print,we don't print a space before it.
        *first = 0;
    else
        printf(" ");
    printf("%lld", t[root].val);//print the parent node first.
    preorder_print(t, t[root].left, first);//then the left child.
    preorder_print(t, t[root].right, first);//finally the right child.
}
//it uses recuisive method to traverse the tree in inorder.
void inorder(tree *t, int root, long long arr[], int *index)//index is used to keep track of the current position in the array,so it must be a pointer.
{
    if (root == -1)//-1 means no node,so we stop.
        return;
    inorder(t, t[root].left, arr, index);//first we traverse the left subtree.
    arr[(*index)++] = t[root].val;//then we store the value of the current node in the array and move the index forward.
    inorder(t, t[root].right, arr, index);//then the right.
}
int main()
{
    long long sum;//avoid the overflow of integer.
    int n1, n2, root1 = -1, root2 = -1;//root is initialized as -1,which means we haven't found the root yet.
    scanf("%d", &n1);
    tree *tree1 = (tree *)malloc(sizeof(tree) * n1);//we use dynamic memory allocation to create an array of tree nodes,which is more flexible and stable.
    for (int i = 0; i < n1; i++)
    {
        scanf("%lld %d", &tree1[i].val, &tree1[i].parent);//input the data.
        if (tree1[i].parent == -1)
            root1 = i;//if the parent is -1,then this node is the root.
        tree1[i].left = tree1[i].right = -1;//initialize the left and right child as -1,which means no child.
    }
    scanf("%d", &n2);
    tree *tree2 = (tree *)malloc(sizeof(tree) * n2);//create an array to denote tree2.
    for (int i = 0; i < n2; i++)
    {
        scanf("%lld %d", &tree2[i].val, &tree2[i].parent);//input the data.
        if (tree2[i].parent == -1)
            root2 = i;//find the root of tree2.
        tree2[i].left = tree2[i].right = -1;//initialize the left and right child as -1,which means no child.
    }
    scanf("%lld", &sum);//input the sum.
    for (int i = 0; i < n1; i++)
    {
        if (i == root1)
            continue;//we skip the root node because it's already in the tree, and we only need to insert the other nodes.
        insert(tree1, root1, i);//insert the node into the tree according to the value and the structure of the tree.
    }
    for (int i = 0; i < n2; i++)
    {
        if (i == root2)
            continue;//we skip the root node because it's already in the tree, and we only need to insert the other nodes.
        insert(tree2, root2, i);//insert the node into the tree according to the value and the structure of the tree.
    }
    int idx1 = 0, idx2 = 0;//idx1 and idx2 are used to keep track of the current position in the array,so they must be initialized as 0.
    long long *arr1 = (long long *)malloc(sizeof(long long) * n1);//to store the values of the nodes in tree1 in sorted order, we use an array and inorder traversal.
    long long *arr2 = (long long *)malloc(sizeof(long long) * n2);//for tree2.
    inorder(tree1, root1, arr1, &idx1);//use inorder to gain a sorted array of the values in tree1.
    inorder(tree2, root2, arr2, &idx2);//use inorder to gain a sorted array of the values in tree2.
    int i = 0, j = n2 - 1;
    //we use two pointers to find the pairs of values that sum up to the target value,one pointer starts from the beginning of arr1 and the other starts from the end of arr2.
    int have = 0;//it decides whether we ouput "true" or "false".
    while (i < n1 && j >= 0)
    {
        if (arr1[i] + arr2[j] == sum)
        {
            if (!have)
            {
                have = 1;
                printf("true\n");//the first time we find a pair of values that sum up to the target value, we print "true" and set have to 1, which means we have found at least one pair.
                //and ,as long as have is 1,we will not print true again.
            }
            printf("%lld = %lld + %lld\n", sum, arr1[i], arr2[j]);//according to the format.
            //store the current value of arr1[i] and arr2[j] in a and b, which are used to move the pointers until we find a different value.
            long long a = arr1[i];
            long long b = arr2[j];
            while (i < idx1 && arr1[i] == a)
                i++;//skip the same value in arr1,move the pointer i to the right until we find a different value.
            while (j >= 0 && arr2[j] == b)
                j--;
                //we need additional justice to avoid outputing the same pair of values multiple times,so we move the pointers until we find a different value.
        }
        else if (arr1[i] + arr2[j] < sum)
            i++;//the current sum is smaller than the target value,so we need to increase the sum by moving the pointer i to the right,which means we choose a larger value from arr1.
        else
            j--;//the current sum is larger than the target value,so we need to decrease the sum by moving the pointer j to the left,which means we choose a smaller value from arr2.
    }
    if (!have)
        printf("false\n");//if we haven't found any pair of values that sum up to the target value, we print "false".
    int idx3 = 1, idx4 = 1;//the are for the preorder print,they are used to control the format of the output,so they must be initialized as 0.
    preorder_print(tree1, root1, &idx3);//print tree1 in preorder traversal.
    printf("\n");
    preorder_print(tree2, root2, &idx4);//print tree2 in preorder traversal.
    printf("\n");
    //free the dynamically allocated memory to avoid memory leaks.
    free(tree1);
    free(tree2);
    free(arr1);
    free(arr2);
    return 0;
}
