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

bool is_prime(i64 n) {
    if (n < 2) return false;
    for (i64 divisor = 2; divisor <= n / divisor; ++divisor) {
        if (n % divisor == 0) return false;
    }
    return true;
}

struct PrimeSieve {
    vector<int> primes;
    vector<bool> is_prime;

    explicit PrimeSieve(int n) : is_prime(n + 1, true) {
        assert(n >= 0);
        is_prime[0] = false;
        if (n >= 1) is_prime[1] = false;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) primes.push_back(i);
            for (int prime : primes) {
                if (prime > n / i) break;
                is_prime[i * prime] = false;
                if (i % prime == 0) break;
            }
        }
    }
};

vector<bool> eratosthenes(int n) {
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
int main() {
    PrimeSieve sieve(10);
    for (int prime : sieve.primes) cout << prime << ' ';                // 2 3 5 7
    cout << '\n' << is_prime(97) << ' ' << eratosthenes(10)[9] << '\n'; // 1 0
}
