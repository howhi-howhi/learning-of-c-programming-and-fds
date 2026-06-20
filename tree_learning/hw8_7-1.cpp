#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int matrix[n+1][n+1]={0};
    for (int i=0;i<m;i++)
    {
        int p,q;
        scanf("%d %d",&p,&q);
        matrix[p][q]=1;
        matrix[q][p]=1;
    }
    int k;
    scanf("%d",&k);
    for (int i=0;i<k;i++)
    {
        int num;
        scanf("%d",&num);
        int arr[num];
        for (int j=0;j<num;j++)
        {
            scanf("%d",&arr[j]);
        }
        if (num!=n+1)
        {
            printf("NO\n");
            continue;
        }
        if (arr[0]!=arr[num-1])
        {
            printf("NO\n");
            continue;
        }
        int ok=1;
        int vis[n+1]={0};
        for (int s=0;s<num-1;s++)
        {
            if (vis[arr[s]])
            {
                ok=0;
                printf("NO\n");
                break;
            }
            vis[arr[s]]=1;
            if (matrix[arr[s]][arr[s+1]]!=1)
            {
                printf("NO\n");
                ok=0;
                break;
            }
        }
        if (ok)
            printf("YES\n");
    }
    return 0;
}