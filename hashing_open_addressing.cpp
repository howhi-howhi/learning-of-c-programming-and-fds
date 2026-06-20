#include <stdio.h>
#include <stdlib.h>
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
enum KindOfEntry
{
    Legitimate,
    Empty,
    Deleted
};
struct HashEntry
{
    int Element;
    enum KindOfEntry info;
};
typedef struct HashEntry Cell;
struct HashTbl
{
    int TableSize;
    Cell *TheCells;
};
typedef HashTbl *HashTable;
HashTable Initial(int tablesize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = NextPrime(tablesize);
    H->TheCells = (Cell *)malloc(sizeof(Cell) * H->TableSize);
    for (int i = 0; i < H->TableSize; i++)
        H->TheCells[i].info = Empty;
    return H;
}
int Hash(int key, int tablesize)
{
    int val = key % tablesize;
    if (val < 0)
        val += tablesize;
    return val;
}
int Hash2(int key, int r)
{
    int val = r - (r % key);
    if (val == 0)
        val = 1;
    return val;
}
int Linear_Find(int key, HashTable H)
{
    int curpos = Hash(key, H->TableSize);
    while (H->TheCells[curpos].info != Empty && H->TheCells[curpos].Element != key)
    {
        curpos++;
        if (curpos >= H->TableSize)
            curpos -= H->TableSize;
    }
    return curpos;
}
int Quadratic_Find(int key, HashTable H)
{
    int curpos = Hash(key, H->TableSize);
    int collisionnum = 0;
    while (H->TheCells[curpos].info != Empty && H->TheCells[curpos].Element != key)
    {
        collisionnum++;
        curpos = (Hash(key, H->TableSize) + collisionnum * collisionnum) % H->TableSize;
    }
    return curpos;
}
void Quadratic_Insert(int key, HashTable H)
{
    int pos = Quadratic_Find(key, H);
    if (H->TheCells[pos].info != Legitimate)
    {
        H->TheCells[pos].info = Legitimate;
        H->TheCells[pos].Element = key;
    }
}
void Lazy_Delete(int key, HashTable H)
{
    int pos = Quadratic_Find(key, H);
    if (H->TheCells[pos].info == Legitimate)
        H->TheCells[pos].info = Deleted;
}
int double_hash(int key,HashTable H)
{
    int h1=Hash(key,H->TableSize);
    int r=H->TableSize-2;
    int h2=Hash2(key,r);
    int curpos=h1;
    int i=0;
    while (H->TheCells[curpos].info!=Empty&&H->TheCells[curpos].Element!=key)
    {
        i++;
        curpos=(h1+i*h2)%H->TableSize;
    }
    return curpos;
}
void doublehash_insert(int key,HashTable H)
{
    
}
