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

constexpr int N = 1e6 + 5, mod = 998244353;
constexpr i64 inf = 2e18 + 5;

void solve() {
    int n;
    cin >> n;
    vector<double> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    priority_queue<double, vector<double>, greater<double>> q;
    sort(a.begin() + 1, a.end());
    for (int i = 1; i <= n; i++) {
        q.push(a[i]);
    }

    while (q.size() > 1) {
        double x = q.top();
        q.pop();
        double y = q.top();
        q.pop();
        double z = sqrt(x * y);
        q.push(z);
    }
    cout << q.top() << "\n";
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
