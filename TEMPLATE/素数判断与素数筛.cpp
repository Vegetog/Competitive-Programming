/*
算法：素数判断与素数筛
简介：提供试除判素、线性筛和埃氏筛。
复杂度：判素 O(√n)/O(1)；线性筛 O(n)/O(n)；埃氏筛 O(n log log n)/O(n)（时间/空间）。
约定：筛的上界 n >= 0，返回表中下标即数值，0 和 1 不是素数。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

// 作用：试除判素；输入：整数 n；输出：n 是素数时返回 true。
bool is_prime(i64 n) {
    if (n < 2) return false;
    for (i64 p = 2; p <= n / p; ++p) {
        if (n % p == 0) return false;
    }
    return true;
}

struct Sieve {
    vector<int> pr;
    vector<bool> is_prime;

    // 作用：线性筛；输入：上界 n>=0；输出：填好素数表 pr 与判素表 is_prime[0..n] 的对象。
    explicit Sieve(int n) : is_prime(n + 1, true) {
        assert(n >= 0);
        is_prime[0] = false;
        if (n >= 1) is_prime[1] = false;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) pr.push_back(i);
            for (int prime : pr) {
                if (prime > n / i) break;
                is_prime[i * prime] = false;
                if (i % prime == 0) break;
            }
        }
    }
};

// 作用：埃氏筛判素；输入：上界 n>=0；输出：长度 n+1 的表，第 i 项表示 i 是否为素数。
vector<bool> erat(int n) {
    assert(n >= 0);
    vector<bool> prime(n + 1, true);
    prime[0] = false;
    if (n >= 1) prime[1] = false;
    for (int i = 2; i <= n / i; ++i) {
        if (!prime[i]) continue;
        for (i64 j = i64(i) * i; j <= n; j += i) prime[j] = false;
    }
    return prime;
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    Sieve sieve(10);
    for (int prime : sieve.pr) cout << prime << ' ';            // 2 3 5 7
    cout << '\n' << is_prime(97) << ' ' << erat(10)[9] << '\n'; // 1 0
}
