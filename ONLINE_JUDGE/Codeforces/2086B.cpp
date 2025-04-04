#include "bits/stdc++.h"
using namespace std;
#define x1 X1
#define x2 X2
#define y1 Y1
#define y2 Y2
#define int long long
template <typename C>
inline int size(const C& x) {
    return static_cast<int>(x.size());
}

using i64 = long long;
using i128 = __int128;
using pii = pair<int, int>;

constexpr int B = 30, N = 2E6 + 10, mod = 998244353, inf32 = 1E9 + 10;
constexpr i64 inf = 2E18 + 10;

void Gura() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n + 1), pr(n + 1);
    int sum = 0;
    int nl = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pr[i] = a[i] + pr[i - 1];
        sum += a[i];
    }

    int l = 0, r = n * k;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        i128 t = k * sum;
        int tm = mid - 1;
        t -= tm / n * sum;
        t -= pr[tm % n];

        if (t >= x)
            l = mid;
        else
            r = mid - 1;
    }

    cout << r << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(15);

    int Gawr = 1;
    cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura();
    }

    return 0;
}
