#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = pair<int, int>;

constexpr int N = 1e6 + 5, inf = 2e18 + 5;

int n;
int a[N + 1], t[N + 1];

void add(int p, int v) {
    for (int i = p; i <= n; i += i & -i) t[i] += v;
}
int sum(int p) {
    int res = 0;
    for (int i = p; i >= 1; i -= i & -i) res += t[i];
    return res;
}

void solve() {
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i, a[i]);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, k;
            cin >> x >> k;
            add(x, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l - 1) << "\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(12);

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}
