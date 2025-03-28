#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif

#define int long long
#define new _MY_NEW_
#define lg(ITEM) static_cast<int>(std::log2(ITEM))

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr long long INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

template <typename T = long long>
bool extgcd(T a, T b, T &x, T &y, T d) {  // ax+by=d
    if (!b && d % a) return false;
    if (!b) {
        x = d / a, y = 0;
        return true;
    }
    if (extgcd(b, a % b, y, x, d)) {
        y -= a / b * x;
        return true;
    }
    return false;
}
int exgcd(int a, int b, int &x, int &y) {  // ax+by=gcd(a,b)
    int d = a;
    if (!b)
        x = 1, y = 0;
    else {
        d = exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
    return d;
}

void SINGLE_TEST() {
    int a, b, c;
    cin >> a >> b >> c;
    int x, y;
    if (extgcd(a, b, x, y, c)) {
        int d = gcd(a, b);
        // x=x0+b/d*k,y=y0-a/d*k
        int p = b / d, q = a / d;
        // 先把x变成最小正整数解
        // 最小正整数解，即x+k*p>=1
        if (x < 0) {
            // int k = ceil((1.0 - x) / p);
            int k = (1 - x + p - 1) / p;
            x += k * p;
            y -= k * q;
        } else {
            int k = (x - 1) / p;
            x -= k * p;
            y += k * q;
        }
        if (y > 0) {
            // 有正整数解，即为 x,y 均为正整数的解，0不是正整数
            cout << (y - 1) / q + 1 << " ";      // 解的个数
            cout << x << " ";                    // x的最小正整数解
            cout << (y - 1) % q + 1 << " ";      // y的最小正整数解
            cout << x + (y - 1) / q * p << " ";  // x的最大正整数解
            cout << y << "\n";                   // y的最大正整数解
        } else {
            // 有整数解，但是不是正整数解
            cout << x << " ";  // x的最小正整数值
            cout << y + q * ((1 - y + q - 1) / q) << "\n";  // y的最小正整数值
        }

    } else {
        cout << -1 << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}