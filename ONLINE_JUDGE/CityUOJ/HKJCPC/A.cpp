#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = std::pair<int, int>;

constexpr int N = 1e6, inf = 2e18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    unordered_map<int, int> f;
    auto at = [&](int x) -> int& { return f.count(x) ? f[x] : f[x] = x; };
    auto find = [&](int x) {
        while (x != at(x)) x = at(x) = at(at(x));
        return x;
    };

    for (int i = 1; i <= n; i++) {
        int x = find(a[i]);
        at(x) = find(x + 1);
        cout << x << " \n"[i == n];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
