#include <iostream>

int sum(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i;
    }
    // return ans;
}

int main() {
    int n;
    std::cin >> n;
    int res = sum(n);
    std::cout << res << std::endl;
    return 0;
}
