#include "bits/stdc++.h"
#define int long long
using namespace std;

using pii = std::pair<int, int>;
constexpr int N = 2e6, inf = 2e18;

long long merge_sort(vector<int>& a, int l, int r) { // [l,r)
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    long long ans = merge_sort(a, l, m) + merge_sort(a, m, r);

    vector<int> t;
    int i = l, j = m;
    while (i < m && j < r) {
        if (a[i] <= a[j]) t.push_back(a[i++]);
        else {
            ans += m - i;
            t.push_back(a[j++]);
        }
    }
    while (i < m) t.push_back(a[i++]);
    while (j < r) t.push_back(a[j++]);
    copy(t.begin(), t.end(), a.begin() + l);
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << merge_sort(a, 0, n) << '\n';
}
