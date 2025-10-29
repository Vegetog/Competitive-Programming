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
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<pair<pii, int>> query;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        query.push_back({{l, r}, i});
    }
    sort(query.begin(), query.end(), [&](pair<pii, int> x, pair<pii, int> y) {
        return x.first.second < y.first.second;
    });

    vector<int> ans(q);
    int po = 1;
    unordered_map<int, int> vis;
    for (int i = 0; i < q; i++) {
        auto [l, r] = query[i].first;
        for (; po <= r; po++) {
            if (vis.count(a[po])) {
                add(vis[a[po]], -1);
            }
            vis[a[po]] = po;
            add(po, 1);
        }
        ans[query[i].second] = sum(r) - sum(l - 1);
    }
    for (auto x : ans) cout << x << "\n";
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
