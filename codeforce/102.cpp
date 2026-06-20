#include <stdio.h>
#include <string.h>
char ch[1000005];
int A[1000005];
int B[1000005];
long long preA[1000005];
long long preB[1000005];
int main()
{
    int t, n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d", &n);
        scanf("%s", ch);
        ch[n] = '\0';
        long long fixed = 0;
        int cnt1 = 0;
        for (int j = 0; j < n; j++)
        {
            if (ch[j] == '1')
                cnt1++;
            if (ch[j] == '0')
                fixed += cnt1;
        }
        int cntl = 0, cntr = 0;
        int c = 0;
        for (int j = 0; j < n; j++)
        {
            if (ch[j] == '1')
                cntl++;
            if (ch[j] == '?')
                A[c++] = cntl;
        }
        int d = c - 1;
        for (int j = n - 1; j >= 0; j--)
        {
            if (ch[j] == '0')
                cntr++;
            if (ch[j] == '?')
                B[d--] = cntr;
        }
        preA[0] = 0;
        preB[0] = 0;

        for (int j = 1; j <=c; j++)
        {
            preA[j] = preA[j - 1] + A[j - 1];
            preB[j] = preB[j - 1] + B[j - 1];
        }
        long long ans = 0;

        for (int t = 0; t <=c; t++)
        {
            long long cur =
                fixed + preB[t] + (preA[c] - preA[t]) + 1LL * t * (c - t);

            if (cur > ans)
                ans = cur;
        }

        printf("%lld\n", ans);
    }
}