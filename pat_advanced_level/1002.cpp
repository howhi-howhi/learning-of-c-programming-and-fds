#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
int main()
{
    double poly[1001]={0.0};
    int n1,n2;
    cin>>n1;
    int exp;
    double cof;
    for (int i=0;i<n1;i++)
    {
       cin>>exp>>cof;
       poly[exp]+=cof;
    }
    cin>>n2;
    for(int i=0;i<n2;i++)
    {
        cin>>exp>>cof;
        poly[exp]+=cof;
    }
    int total=0;
    for (int i=0;i<1001;i++)
    {
        if (fabs(poly[i])>1e-8)
        total++;
    }
    cout<<total;
    if (total==0)
    return 0;
    for (int i=1000;i>=0;i--)
    {
         if (fabs(poly[i])>1e-8)
        {
            printf(" %d %.1lf",i,poly[i]);
        }
    }
    return 0;
    
}