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

void solve() {
    int n;
    cin >> n;

    if (n == 2) {
        cout << -1 << "\n";
        return;
    }

    if (n % 2 == 1) {
        for (int i = 2; i <= n; i++) {
            cout << i << " ";
        }
        cout << 1 << "\n";
        return;
    }

    for (int i = 2; i <= n - 2; i++) {
        cout << i << " ";
    }
    cout << n << " " << 1 << " " << n - 1 << "\n";

    return;
    
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    do {
        bool ok = 1;
        for (int i = 1; i <= n; i++) {
            if (p[i] == i) {
                ok = 0;
                break;
            }
            for (int j = i + 1; j <= n; j++) {
                if (p[i] + i == p[j] + j) {
                    ok = 0;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) {
            for (int i = 1; i <= n; i++) {
                cout << p[i] << " ";
            }
            cout << "\n";
        }
    } while (next_permutation(p.begin() + 1, p.end()));
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
