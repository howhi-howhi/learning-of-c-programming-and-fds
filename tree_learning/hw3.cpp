#include <stdio.h>
#include <stdlib.h>
#define MAXN 1005
typedef struct Stack
{
    int top;
    int data[MAXN];
} stack;
int main()
{
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    stack s;
    int sequence[k][n];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &sequence[i][j]);
        }
        int ok = 1;
        s.top = -1;
        int nextpush = 1;
        for (int q = 0; q < n; q++)
        {
            int x = sequence[i][q];
            while ((s.top == -1 || s.data[s.top] != x) && (nextpush <= n))
            {
                if (s.top == m - 1)
                {
                    ok = 0;
                    break;
                }
                s.data[++s.top] = nextpush++;
            }
            if (s.top != -1 && s.data[s.top] == x)
            {
                s.top--;
            }
            else
            {
                ok = 0;
                break;
            }
        }
        if (ok)
            printf("YES\n");
        else
            printf("NO\n");
    }
}

