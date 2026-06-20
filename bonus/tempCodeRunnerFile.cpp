#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int value;
    int frozen;
} node;
typedef struct
{
    int size;
    int capacity;
    node *data;
} heap;
int cmp(node a, node b)
{
    if (a.frozen != b.frozen)
        return a.frozen < b.frozen;
    return a.value < b.value;
}
int isempty(heap h)
{
    return h.size == 0;
}
void push(heap *h, node n)
{
    h->data[++h->size] = n;

    for (int i = h->size; i > 1; i /= 2)
    {
        if (cmp(h->data[i], h->data[i / 2]))
        {
            node temp = h->data[i];
            h->data[i] = h->data[i / 2];
            h->data[i / 2] = temp;
        }
        else
            break;
    }
}
node pop(heap *h)
{
    node ret = h->data[1];
    node last = h->data[h->size--];
    int i = 1;
    while (2 * i <= h->size)
    {
        int child = 2 * i;
        if (child + 1 <= h->size && cmp(h->data[child + 1], h->data[child]))
            child++;
        if (!cmp(h->data[child], last))
            break;
        h->data[i] = h->data[child];
        i = child;
    }
    h->data[i] = last;
    return ret;
}
int main()
{
    int n, c;
    scanf("%d %d", &n, &c);
    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    heap h;
    h.data = (node *)malloc((c + 1) * sizeof(node));
    h.capacity = c + 1;
    h.size = 0;
    for (int i = 0; i < c; i++)
    {
        node x;
        x.value = arr[i];
        x.frozen = 0;
        push(&h, x);
    }
    int isfirst = 1;
    int next = c;
    while (!isempty(h))
    {
        if (h.data[1].frozen == 1)
        {
            printf("\n");
            for (int i = 1; i <= h.size; i++)
                h.data[i].frozen = 0;
            isfirst = 1;
        }
        node t = pop(&h);
        if (!isfirst)
            printf(" ");
        printf("%d", t.value);
        isfirst = 0;
        if (next < n)
        {
            node m;
            m.value = arr[next++];
            if (m.value >= t.value)
                m.frozen = 0;
            else
                m.frozen = 1;
            push(&h, m);
        }
    }
    return 0;
}