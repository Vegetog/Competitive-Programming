#include <bits/stdc++.h>
using namespace std;

#define int long long

using i64 = long long;
using pii = pair<int, int>;

constexpr int N = 1e3 + 5, mod = 1e9 + 7;
constexpr i64 inf = 2e18;

int fac[N + 1], invfac[N + 1];

int power(int x, int y = mod - 2) {
    int res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

int C(int n, int m) {
    if (m > n || m < 0) return 0;
    return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int A(int n, int m) {
    if (m > n || m < 0) return 0;
    return fac[n] * invfac[n - m] % mod;
}

void solve() {
    int x, y;
    cin >> x >> y;
    for (int i = 1; i <= x + y; i++) {
        cout << (C(x - 1, i / 2 - 1) * C(y - 1, i - i / 2 - 1) % mod +
                 C(x - 1, i - i / 2 - 1) * C(y - 1, i / 2 - 1) % mod) %
                    mod
             << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(12);

    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        invfac[i] = power(fac[i]);
    }

    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }

    return 0;
}