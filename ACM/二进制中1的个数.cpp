#include <bits/stdc++.h>
using namespace std;

int num1(int x)
{
    int cnt = 0;
    while (x)
    {
        x -= x & (-x); // lowbit(x);
        cnt++;
    }
    return cnt;
}
int main()
{
    int x;
    cin >> x;
    cout << num1(x);
}