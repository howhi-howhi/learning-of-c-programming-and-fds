#include <stdio.h>
#include <stdlib.h>
#define MAXN 1005
typedef struct Stack *stack;
struct Stack
{
    int top;
    int data[MAXN];
};
int pop(stack s)
{
    if (s->top == -1)
        return -1;
    int temp = s->data[s->top];
    s->top = s->top - 1;
    return temp;
}
int main()
{
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    stack s = (stack)malloc(sizeof(struct Stack));
    int sequence[k][n];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &sequence[i][j]);
        }
        int ok = 1;
        s->top = -1;
        int nextpush = 1;
        for (int q = 0; q < n; q++)
        {
            int x = sequence[i][q];
            while ((s->top == -1 || s->data[s->top] != x) && nextpush <= n)
            {
                s->data[++(s->top)] = nextpush++;
                if (s->top + 1 > m)
                {
                    ok = 0;
                    break;
                }
            }
            if (s->top != -1 && s->data[s->top] == x)
                s->top--;
            else
                ok = 0;
            if (!ok)
                break;
        }
        if (ok)
            printf("YES\n");
        else
            printf("NO\n");
    } // We don't have to use specific push/pop function.Just simulate it manually is ok.
    free(s);
    return 0;
}
