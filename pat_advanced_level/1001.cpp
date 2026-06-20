#include <iostream>
using namespace std;
int main()
{
    int a, b;
    cin >> a >> b;
    int c = a + b;
    int arr[10];
    int index = 0;
    if (c == 0)
    {
        cout << "0";
        return 0;
    }
    if (c < 0)
    {
        c = -c;
        cout << "-";
    }
    while (c > 0)
    {
        arr[index++] = c % 10;
        c /= 10;
    }
    for (int i = index - 1; i >= 0; i--)
    {
        cout << arr[i];
        if (i% 3 == 0 && i != 0)
            cout << ",";
    }
    return 0;
}