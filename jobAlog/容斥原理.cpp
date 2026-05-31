// 题目：https://www.acwing.com/problem/content/description/892
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];

    int ans = 0;
    for (int i = 1; i < (1 << m); i++) {
        int bt = 0;
        i64 t = 1;
        bool ok = 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                bt++;
                t = lcm(t, a[j]);
                if (t > n) {
                    ok = 0;
                    break;
                }
            }
        }
        if (!ok) continue;
        if (bt % 2 == 1)
            ans += n / t;
        else
            ans -= n / t;
    }
    cout << ans << "\n";
}
