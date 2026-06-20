#include <stdio.h>
#include <stdlib.h>
struct ListNode;
typedef struct ListNode *Position;
struct Hashtbl;
typedef struct Hashtbl *HashTable;
struct ListNode
{
    int Element;
    Position Next;
};
typedef Position List;
struct Hashtbl
{
    int TableSize;
    List *TheLists;
};
int isPrime(int N)
{
    if (N <= 1)
        return 0;
    for (int i = 2; i * i <= N; i++)
    {
        if (N % i == 0)
            return 0;
    }
    return 1;
}
int NextPrime(int N)
{
    if (N % 2 == 0)
        N++;
    while (!isPrime(N))
        N += 2;
    return N;
}
HashTable InitialHashTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct Hashtbl));
    if (H == NULL)
    {
        printf("Error!\n");
        return NULL;
    }
    H->TableSize = NextPrime(TableSize);
    H->TheLists = (List *)malloc(sizeof(List) * H->TableSize);
    for (i = 0; i < H->TableSize; i++)
    {
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        H->TheLists[i]->Next = NULL;
    }
    return H;
}
int Hash(int key, int tablesize)
{
    int hashval = key % tablesize;
    if (hashval < 0)
        hashval += tablesize;
    return hashval;
}
Position Find(int key, HashTable H)
{
    Position P;
    List L;
    L = H->TheLists[Hash(key, H->TableSize)];
    P = L->Next;
    while (P != NULL && P->Element != key)
        P = P->Next;
    return P;
}
void insert(int key,HashTable H)
{
    Position P,New;
    List L;
    P=Find(key,H);
    if (P==NULL)
    {
        New=(Position)malloc(sizeof(struct ListNode));
    }
    L=H->TheLists[Hash(key,H->TableSize)];
    New->Element=key;
    New->Next=L->Next;
    L->Next=New;
}