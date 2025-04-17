#include "bits/stdc++.h"

using i64 = __int64_t;
using i128 = __int128_t;
using pii = std::pair<int, int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        std::cout << (x * x + (x * log(x))) << "\n";
    }

    return 0;
}