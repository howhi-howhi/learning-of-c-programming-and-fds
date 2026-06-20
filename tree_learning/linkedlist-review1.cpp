#include <stdio.h>
#include <stdlib.h>
typedef struct Node *node;
struct Node
{
    int data;
    node next;
};
node create(int n, int *arr)
{
    node head = (node)malloc(sizeof(struct Node));
    if (arr == NULL)
        return NULL;
    head->data = arr[0];
    head->next = NULL;
    node tail = head;
    for (int i = 1; i < n; i++)
    {
        node newnode = (node)malloc(sizeof(struct Node));
        newnode->data = arr[i];
        newnode->next = NULL;
        tail->next = newnode;
        tail = newnode;
    }
    return head;
}
node deletenode(node head, int value)
{
    struct Node dummy;
    dummy.next=head;
    node curr=head,prev=&dummy;
    while (curr!=NULL)
    {
        if (curr->data==value)
        {
            node temp=curr;
            prev->next=temp->next;
            curr=prev->next;
            free(temp);
        }
        else
        {
            prev=curr;
            curr=curr->next;
        }
    }  
    return dummy.next;
}
void printlist(node head)
{
    node temp=head;
    while (temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}
node reverse(node head)
{
    node prev,curr,next;
    prev=NULL;
    curr=head;
    next=NULL;
    while (curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return prev;
}
int main()
{
    int arr[8]={1,2,3,4,5,6,7,8};
    node n=create(8,arr);
    printlist(n);
    n=reverse(n);
    printlist(n);
    deletenode(n,4);
    printlist(n);
    return 0;
}
