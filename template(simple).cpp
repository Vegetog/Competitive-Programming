#include "bits/stdc++.h"
#define int long long

using i128 = __int128;
using pii = std::pair<int, int>;

constexpr int N = 1E6 + 10, inf64 = 1E18 + 10;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    auto p = std::vector<std::vector<int>>(N + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        p[x].push_back(i);
    }

    int ans = inf64;
    for (int i = 1; i <= N; i++) {
        if (p[i].size() <= 1) continue;
        for (int j = 1; j < p[i].size(); j++) {
            ans = std::min(ans, p[i][j] - p[i][j - 1] + 1);
        }
    }

    std::cout << (ans == inf64 ? -1 : ans) << "\n";

    return 0;
}