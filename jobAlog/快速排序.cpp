#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e6 + 5, inf = 1e9 + 5, mod = 998244353;
constexpr i64 inf64 = 2e18 + 5;

void quicksort(vector<int>& a, int l, int r) {
    int sd = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < sd) i++;
        while (a[j] > sd) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (l < j) quicksort(a, l, j);
    if (i < r) quicksort(a, i, r);
}

void Gura(int& _turn) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    quicksort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Gawr = 1;
    // std::cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura(_i);
    }

    return 0;
}
