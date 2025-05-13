#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
// #include "_my_utils.h"
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
    int n, m, a, k;
    cin >> n >> m >> a >> k;
    if (n == m && m == a && a == k && k == 0) exit(0);
    // n-m+m*x=a+k*y
    // 需要正整数解，x，y都为正整数
    // m*x-k*y=a+m-n
    int x, y;
    if (extgcd(m, k, x, y, -(a - n))) {
        // cout << x << " " << y << "\n";
        int d = gcd(m, k);
        // x=x0+b/d*k,y=y0-a/d*k
        int p = k / d, q = m / d;
        // 先把x变成最小正整数解
        // 最小正整数解，即x+k*p>=1
        if (x < 0) {
            int h = (1 - x + p - 1) / p;
            x += h * p;
            y -= h * q;
        } else {
            int h = (x - 1) / p;
            x -= h * p;
            y += h * q;
        }
        // cout << x << " " << y << "\n";
        // if (y > 0)
        cout << n + m * x << "\n";
        // else
        //     cout << "Impossible\n";
    } else {
        cout << "Impossible\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1;; CUR++) {
        SINGLE_TEST();
    }
}
