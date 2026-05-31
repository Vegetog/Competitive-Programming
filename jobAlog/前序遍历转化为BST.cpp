#include "bits/stdc++.h"
#define int long long

using namespace std;

using i64 = long long;
using pii = pair<int, int>;

constexpr int N = 1e6 + 5, mod = 998244353;
constexpr i64 inf = 2e18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // val: 节点值, color: 0-黑, 1-红
    // ch[u][0/1]: 左/右子节点索引 (0表示NIL)
    vector<int> val(n + 2), color(n + 2);
    vector<array<int, 2>> ch(n + 2);

    int t = 1;
    function<int(int, int)> build = [&](int lo, int hi) -> int {
        if (t > n) return 0;
        int v = abs(a[t]);
        int c = (a[t] < 0) ? 1 : 0;
        if (v <= lo || v >= hi) return 0;
        int cur = t++;
        val[cur] = v;
        color[cur] = c;
        ch[cur][0] = build(lo, v);
        ch[cur][1] = build(v, hi);
        return cur;
    };

    int root = build(-inf, inf);

    bool valid = true;

    if (root && color[root] == 1) valid = false;

    int blackHeight = -1;
    function<void(int, int)> check = [&](int u, int bh) {
        if (u == 0) {
            if (blackHeight == -1)
                blackHeight = bh;
            else if (blackHeight != bh)
                valid = false;
            return;
        }

        if (color[u] == 0) bh++;

        if (color[u] == 1) {
            if (ch[u][0] && color[ch[u][0]] == 1) valid = false;
            if (ch[u][1] && color[ch[u][1]] == 1) valid = false;
        }

        check(ch[u][0], bh);
        check(ch[u][1], bh);
    };

    check(root, 0);

    cout << (valid ? "Yes" : "No") << "\n";
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
