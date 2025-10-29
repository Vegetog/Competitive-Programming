#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using pii = pair<int, int>;

constexpr int N = 2e6 + 5, inf = 1e9 + 5, mod = 998244353;
constexpr i64 inf64 = 2e18 + 5;

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int i = l, j = mid + 1;
    vector<int> temp;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            temp.push_back(a[i++]);

        } else {
            temp.push_back(a[j++]);
        }
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= r) temp.push_back(a[j++]);
    for (int k = l; k <= r; k++) a[k] = temp[k - l];
}

void solve(int& _turn) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    mergeSort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(12);

    int sample = 1;
    // cin >> sample;
    for (int i = 1; i <= sample; i++) {
        solve(i);
    }

    return 0;
}
