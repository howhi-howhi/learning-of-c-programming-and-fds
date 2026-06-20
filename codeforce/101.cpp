#include <stdio.h>
int arr[1000000];
int check(int n, int x)
{
    int l = 1, r = n;
    while (l < r)
    {
        if (arr[l] == arr[r])
        {
            l++;
            r--;
        }
        else if (arr[l] == x)
            l++;
        else if (arr[r] == x)
            r--;
        else
            return 0;
    }
    return 1;
}
int main()
{
    int l, r;
    int t, n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d", &n);
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &arr[j]);
        }
        int l = 1, r = n;
        while (l < r && arr[l] == arr[r])
        {
            l++;
            r--;
        }
        if (l >= r)
        {
            printf("YES\n");
            continue;
        }
        int x1 = arr[l];
        int x2 = arr[r];
        if (check(n, x1) || check(n, x2))
        {
            printf("YES\n");
        }
        else
            printf("NO\n");
    }
}