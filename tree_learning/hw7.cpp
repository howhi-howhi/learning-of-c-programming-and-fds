#include <stdio.h>
#include <stdlib.h>
int find(int *par, int x)
{
    if (par[x] != x)
        par[x] = find(par, par[x]);
    return par[x];
}
void unionset(int *parent, int a, int b, int *size)
{
    int ra = find(parent, a);
    int rb = find(parent, b);
    if (ra != rb)
    {
        if (size[ra] < size[rb])
        {
            parent[ra] = rb;
            size[rb] += size[ra];
        }
        else
        {
            parent[rb] = ra;
            size[ra] += size[rb];
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    char prompt;
    int num1, num2;
    int *parent = (int *)malloc((n + 1) * sizeof(int));
    int *size = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }
    while (scanf(" %c", &prompt) == 1)
    {
        if (prompt == 'I')
        {
            scanf("%d %d", &num1, &num2);
            unionset(parent, num1, num2, size);
        }
        if (prompt == 'C')
        {
            scanf("%d %d", &num1, &num2);
            if (find(parent, num1) == find(parent, num2))
                printf("yes\n");
            else
                printf("no\n");
        }
        if (prompt == 'S')
        {
            int cnt = 0;
            for (int i = 1; i <= n; i++)
                if (find(parent, i) == i)
                    cnt++;

            if (cnt == 1)
                printf("The network is connected.\n");
            else
                printf("There are %d components.\n", cnt);

            break;
        }
    }
    return 0;
}