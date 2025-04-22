#include <iostream>
#include <string>

using i64 = __int64_t;
using i128 = __int128_t;
using pii = std::pair<int, int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a, b;
    std::cin >> a >> b;

    std::cout << "Hello, World!" << "\n";
    std::cout << a + b << "\n";

    return 0;
}