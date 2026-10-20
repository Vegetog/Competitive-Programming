#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = std::pair<int, int>;

constexpr int N = 1e6, inf = 2e18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    vector pos(n + 1, vector<int>(m + 1));
    auto c = a;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            pos[i][a[i][j]] = j;
        }
    }
    vector<int> b(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        c[b[i]][pos[b[i]][i]]++;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            c[j][i] += c[j][i - 1];
            if (j != 1 && c[j][i] != c[j - 1][i]) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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
