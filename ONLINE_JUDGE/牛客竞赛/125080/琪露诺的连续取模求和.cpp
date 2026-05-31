#include "bits/stdc++.h"
#define int long long

using namespace std;

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << "=" << (x) << endl
#define debuga(a)                       \
    cerr << #a << "=[";                 \
    for (auto& v : a) cerr << v << " "; \
    cerr << "]" << endl
#else
#define debug(x)
#define debuga(a)
#endif

using i64 = long long;
using pii = pair<int, int>;

constexpr int N = 64, mod = 998244353;
constexpr i64 inf = 2e18 + 5;

int f(int n, int p, int q) {
    int res = p * (p - 1) / 2;
    res *= (n / q);

    int t = min(n % q, p - 1);
    res += t * (t + 1) / 2;

    return res;
}

void solve() {
    int l, r, p, q;
    cin >> l >> r >> p >> q;
    
    cout << f(r, p, q) - f(l - 1, p, q) << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(12);

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}
