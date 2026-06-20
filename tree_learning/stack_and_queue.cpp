#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
typedef struct arrayStack
{
    int data[MAXN];
    int top;
} arrayStack;
void pusharraystack(arrayStack *s, int x)
{
    if (s->top == MAXN - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    s->top++;
    s->data[s->top] = x;
}
int poparraystack(arrayStack *s)
{
    if (s->top == -1)
    {
        printf("empty\n");
        return -1;
    }
    int x = s->data[s->top];
    s->top--;
    return x;
}
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} stack;
void push(stack **top, int data)
{
    stack *newNode = (stack *)malloc(sizeof(stack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}
int pop(stack **top)
{
    if (*top == NULL)
    {
        printf("Stack underflow\n");
        return -1;
    }
    stack *temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}
void printstack(stack *top)
{
    stack *temp = top;
    while (temp != NULL)
    {
        printf("%d-- ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
int main()
{
    stack *stack1 = NULL;
    push(&stack1, 10);
    push(&stack1, 20);
    push(&stack1, 30);
    printstack(stack1);
    printf("\n");
    //后进后出 输入是10到30 输出是30到10
    arrayStack stack2;
    stack2.top = -1;
    pusharraystack(&stack2, 10);
    pusharraystack(&stack2, 20);
    pusharraystack(&stack2, 30);
    for (int i=0;i<3;i++)
    {
        printf("%d--",poparraystack(&stack2));
    }
    return 0;
}