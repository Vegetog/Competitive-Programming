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

constexpr int N = 17, mod = 998244353;
constexpr i64 inf = 2e18 + 5;

vector<int> a(N + 1), b(N + 1);

void solve() {
    int x;
    cin >> x;

    int ans = inf;

    if (x % 9 == 0) {
        for (int i = 1; i <= N; i++) {
            if (b[i] >= x) {
                ans = min(ans, (b[i] - x) / 9);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        if (a[i] >= x) {
            int oa = (a[i] - x) / 9;
            int ob = (a[i] - x) % 9;
            ans = min(ans, oa + ob + 1);
        }
    }
    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(12);

    a[1] = 1;
    b[1] = 9;
    for (int i = 2; i <= N; i++) {
        a[i] = a[i - 1] * 10 + 1;
        b[i] = a[i] * 9;
    }

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}
