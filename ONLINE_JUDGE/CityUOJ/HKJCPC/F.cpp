#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = std::pair<int, int>;

constexpr int N = 1e6, inf = 2e18;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> ls(n + 1), rs(n + 1);
    vector<int> stk;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && a[stk.back()] >= a[i]) {
            stk.pop_back();
        }
        ls[i] = stk.empty() ? i : stk.back();
        stk.push_back(i);
        g[ls[i]].push_back(i);
    }
    stk.clear();
    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && a[stk.back()] >= a[i]) {
            stk.pop_back();
        }
        rs[i] = stk.empty() ? i : stk.back();
        stk.push_back(i);
        g[i].push_back(rs[i]);
    }

    vector<vector<pii>> query(n + 1);
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        query[l].emplace_back(r, i);
    }
    vector<int> fen(n + 1);
    auto add = [&](int p, int v) {
        for (int i = p; i <= n; i += i & -i) fen[i] = max(fen[i], v);
    };
    auto rquery = [&](int p) {
        int res = -inf;
        for (int i = p; i >= 1; i -= i & -i) res = max(res, fen[i]);
        return res;
    };
    vector<int> ans(q + 1);
    for (int i = n; i >= 1; i--) {
        for (auto r : g[i]) {
            add(r, r - i + 1);
        }
        for (auto [r, id] : query[i]) {
            ans[id] = rquery(r);
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
