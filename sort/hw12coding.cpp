#include <stdio.h>
#include <stdlib.h>
int isinsertionsort(int arr[], int sorted[], int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        if (sorted[i] > sorted[i + 1])
            break;
    }
    for (i = i + 1; i < n; i++)
    {
        if (arr[i] != sorted[i])
            return 0;
    }
    return 1;
}
int main()
{
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(n));
    int *sorted = (int *)malloc(n * sizeof(n));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &sorted[i]);
    int j;
    for (j = 0; j < n - 1; j++)
    {
        if (sorted[j] > sorted[j + 1])
            break;
    }
    if (isinsertionsort(arr, sorted, n))
    {
        printf("Insertion Sort\n");
        int x = sorted[j + 1];
        int s;
        for (s = j; s >= 0; s--)
        {
            if (sorted[s] > x)
                sorted[s + 1] = sorted[s]; // 1,2,4,5,3
            else
                break;
        }
        sorted[s + 1] = x;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                printf("%d", sorted[i]);
            else
                printf(" %d", sorted[i]);
        }
    }
    else
    {
        printf("Heap Sort\n");
        int maxindex;
        for (maxindex = n - 1; maxindex > 0; maxindex--)
        {
            if (sorted[maxindex] < sorted[maxindex - 1])
                break; // 3,6,5,2,4
        }
        int newmax = sorted[0], newmaxindex = 0;
        for (int k = 1; k < maxindex; k++)
            if (sorted[k] > sorted[newmaxindex])
            {
                newmaxindex = k;
                newmax = sorted[k];
            }
        for (int sk = newmaxindex; sk < maxindex - 1; sk++)
        {
            sorted[sk] = sorted[sk + 1];
        }
        sorted[maxindex - 1] = newmax;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                printf("%d", sorted[i]);
            else
                printf(" %d", sorted[i]);
        }
        return 0;
    }
}