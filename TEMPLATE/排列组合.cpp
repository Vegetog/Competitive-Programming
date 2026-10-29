/*
算法：排列数与组合数
简介：预处理阶乘和逆阶乘，常数时间查询模素数意义下的排列数、组合数。
复杂度：预处理 O(n + log p)，查询 O(1)，空间 O(n)。
约定：固定素数 p = 1000000007，预处理 0 <= n < p；合法查询须 n 不超过预处理上界。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

struct Combinatorics {
    static constexpr i64 kModulus = 1000000007;
    vector<i64> factorial, inverse_factorial;

    static i64 power(i64 base, i64 exponent) {
        i64 result = 1;
        for (; exponent; exponent >>= 1, base = base * base % kModulus) {
            if (exponent & 1) result = result * base % kModulus;
        }
        return result;
    }
    explicit Combinatorics(int n) {
        assert(n >= 0 && n < kModulus);
        factorial.assign(n + 1, 1);
        inverse_factorial.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) factorial[i] = factorial[i - 1] * i % kModulus;
        inverse_factorial[n] = power(factorial[n], kModulus - 2);
        for (int i = n; i > 0; --i) inverse_factorial[i - 1] = inverse_factorial[i] * i % kModulus;
    }
    i64 combination(int n, int k) const {
        if (n < 0 || k < 0 || k > n) return 0;
        assert(n < int(factorial.size()));
        return factorial[n] * inverse_factorial[k] % kModulus * inverse_factorial[n - k] % kModulus;
    }
    i64 permutation(int n, int k) const {
        if (n < 0 || k < 0 || k > n) return 0;
        assert(n < int(factorial.size()));
        return factorial[n] * inverse_factorial[n - k] % kModulus;
    }
};

// ==================== 使用示例 ====================
int main() {
    Combinatorics combinatorics(10);
    cout << combinatorics.combination(5, 2) << ' ' << combinatorics.permutation(5, 2)
         << '\n'; // 10 20
}
