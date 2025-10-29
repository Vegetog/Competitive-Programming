#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = pair<int, int>;

constexpr int N = 2e6 + 5, inf = 2e18 + 5;

void solve() {
    int n, m;
    string s, t;
    cin >> m >> t >> n >> s;

    vector<int> nxt(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && t[i] != t[j]) j = nxt[j - 1];
        if (t[i] == t[j]) j++;
        nxt[i] = j;
    }

    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j]) j = nxt[j - 1];
        if (s[i] == t[j]) j++;
        if (j == m) {
            cout << (i - m + 1) << " ";
            j = nxt[j - 1];
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
