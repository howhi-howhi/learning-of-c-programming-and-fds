#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int table[1005];
int heap[1005];
int indegree[1005];
int result[1005];
int heapsize = 0;
void push(int val)
{
    heap[++heapsize] = val;
    int i = heapsize;
    while (i > 1 && heap[i / 2] > heap[i])
    {
        int temp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = temp;
        i /= 2;
    }
}
int pop()
{
    int val = heap[1];
    heap[1] = heap[heapsize--];
    int i = 1;
    while (i * 2 <= heapsize)
    {
        int child = 2 * i;
        if (i * 2 + 1 <= heapsize && heap[2 * i + 1] < heap[2 * i])
            child++;
        if (heap[i] <= heap[child])
            break;
        int temp = heap[i];
        heap[i] = heap[child];
        heap[child] = temp;
        i = child;
    }
    return val;
}
bool isheapempty()
{
    return heapsize == 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        indegree[i] = 0;
    int resultcount = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &table[i]);
        if (table[i] >= 0)
        {
            int ideal = table[i] % n;
            if (i >= ideal)
            {
                indegree[i] = i - ideal;
            }
            else
            {
                indegree[i] = i + n - ideal;
            }
            if (indegree[i] == 0)
            {
                push(table[i]);
                indegree[i] = -1;
            }
        }
    }
    while (!isheapempty())
    {
        int cur = pop();
        result[resultcount++] = cur;
        int curidx = -1;
        for (int i = 0; i < n; i++)
        {
            if (table[i] == cur)
            {
                curidx = i;
                break;
            }
        }
        table[curidx] = -1;
        int count = 0;
        int nextidx = (curidx + 1) % n;
        while (table[nextidx] >= 0 && count < n - 1)
        {
            if (indegree[nextidx] > 0)
            {
                indegree[nextidx]--;
                if (indegree[nextidx] == 0)
                {
                    push(table[nextidx]);
                    indegree[nextidx] = -1;
                }
            }
            nextidx = (nextidx + 1) % n;
            count++;
        }
    }
    for (int i = 0; i < resultcount; i++)
    {
        printf("%d", result[i]);
        if (i < resultcount - 1)
            printf(" ");
    }
    return 0;
}