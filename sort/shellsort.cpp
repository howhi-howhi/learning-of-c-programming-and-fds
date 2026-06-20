#include <stdio.h>
#define MAXN 1000
int arr[20] = {11, 23, 12, 45, 32, 1, 23, 5, 44, 90, 87, 88, 69, 223, 91, 33, 42, 56, 213, 99};
int heap[MAXN];
void shellsort(int arr[], int n);
void print(int arr[], int n);
void ini(int arr[], int n);
void percdown(int heap[], int p, int n);
void buildheap(int arr[], int n);
int deletemin(int heap[], int &n);
int main()
{
    buildheap(arr, 20);
    int n = 20;
    for (int i = 0; i < 20; i++)
        arr[i] = deletemin(heap, n);
    // shellsort(arr, 20);
    print(arr, 20);
    return 0;
}
void shellsort(int arr[], int n)
{
    int i, j, increment;
    int tmp;
    // The key is to find the proper increment,and this sequence:n/2,n/4,...1 is not so efficient.
    for (increment = n / 2; increment >= 1; increment /= 2)
    {
        for (i = increment; i < n; i++)
        {
            tmp = arr[i];
            for (j = i; j >= increment; j -= increment)
            {
                if (tmp < arr[j - increment])
                    arr[j] = arr[j - increment];
                else
                    break;
            }
            arr[j] = tmp;
        }
    }
}
void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}
void ini(int arr[], int n)
{
    for (int i = 1; i < n + 1; i++)
        heap[i] = arr[i - 1];
}
void percdown(int heap[], int p, int n)
{
    int parent, child;
    int x = heap[p];
    for (parent = p; 2 * parent <= n; parent = child)
    {
        child = 2 * parent;
        if (child + 1 <= n && heap[child] > heap[child + 1])
            child++;
        if (x > heap[child])
            heap[parent] = heap[child];
        else
            break;
    }
    heap[parent] = x;
}
void buildheap(int arr[], int n)
{
    ini(arr, n);
    for (int i = n / 2; i > 0; i--)
        percdown(heap, i, n);
}
int deletemin(int heap[], int &n)
{
    int tmp = heap[1];
    int x = heap[n];
    n--;
    int parent, child;
    for (parent = 1; 2 * parent <= n; parent = child)
    {
        child = 2 * parent;
        if (child + 1 <= n && heap[child + 1] < heap[child])
            child++;
        if (x > heap[child])
            heap[parent] = heap[child];
        else
            break;
    }
    heap[parent] = x;
    return tmp;
}