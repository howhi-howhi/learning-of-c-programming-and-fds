#include <cstdio>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    vector <vector<int>> arr(105);
    for (int i=0;i<m;i++)
    {
        int index;
        cin>>index;
        int num;
        cin>>num;
        for (int j=0;j<num;j++)
        {
            int t;
            cin>>t;
            arr[index].push_back(t);
        }
    }
    queue <int> q;
    q.push(1);
    while (!q.empty())
    {
        int size=q.size();
        while (size--)
        {
            int x=q.front();
            
        }
    }
}