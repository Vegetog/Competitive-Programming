#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = pair<int, int>;

constexpr int N = 2e6 + 5;
constexpr long long inf = 1e18;

int x, y, z;
int xx, yy;
int a[101 * 101][4];
int tot = 1;

void solve() {
    cin >> x >> y >> z;
    tot = 1;
    int mn = min({x, y, z});
    cout << x * y * z / mn << "\n";
    int sum = x * y * z / mn;
    vector<pii> ve = {{x, 1}, {y, 2}, {z, 3}};
    sort(ve.begin(), ve.end());

    xx = ve[1].first;
    yy = ve[2].first;
    int t = 1;
    int stt = ve[0].first;
    for (int i = 1; i <= xx; i++) {
        int st = stt;
        for (int j = 1; j <= yy; j++) {
            a[tot][ve[1].second] = i;
            a[tot][ve[2].second] = j;
            a[tot][ve[0].second] = st;
            st--;
            if (st == 0) st = ve[0].first;
            tot++;
        }
        stt--;
        if (stt == 0) stt = ve[0].first;
    }
    for (int i = 1; i <= sum; i++) {
        cout << a[i][1] << " " << a[i][2] << " " << a[i][3] << "\n";
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
}
