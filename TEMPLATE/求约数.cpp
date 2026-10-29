/*
算法：试除法求约数
简介：枚举不超过平方根的因数，成对收集并排序。
复杂度：时间 O(√n + d log d)，空间 O(d)，d 为约数个数。
约定：n > 0；使用 i <= n/i 避免平方溢出。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

vector<i64> get_divisors(i64 n) {
    assert(n > 0);
    vector<i64> divisors;
    for (i64 i = 1; i <= n / i; ++i) {
        if (n % i != 0) continue;
        divisors.push_back(i);
        if (i != n / i) divisors.push_back(n / i);
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

// ==================== 使用示例 ====================
int main() {
    for (i64 divisor : get_divisors(12)) cout << divisor << ' '; // 1 2 3 4 6 12
    cout << '\n';
}
