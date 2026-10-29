/*
算法：快速幂、快速乘与素数模逆元
简介：二进制拆分指数/乘数，计算整数幂、模乘、模幂及费马逆元。
复杂度：整数幂 O(log b)；快速乘 O(log p)；模幂/逆元 O(log b·log p)；空间 O(1)。
约定：指数非负，模数 p > 0；普通幂的中间结果须在类型范围内；逆元要求素数 p 且 a 不被 p 整除。
*/
#include <cassert>
#include <iostream>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

template <class T> T power(T base, i64 exponent) {
    assert(exponent >= 0);
    T result = 1;
    while (exponent) {
        if (exponent & 1) result *= base;
        exponent >>= 1;
        if (exponent) base *= base;
    }
    return result;
}

i64 normalize(i64 value, i64 modulus) {
    value %= modulus;
    return value < 0 ? value + modulus : value;
}

i64 add_mod(i64 a, i64 b, i64 modulus) {
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

i64 multiply_mod(i64 a, i64 b, i64 modulus) {
    assert(modulus > 0);
    a = normalize(a, modulus);
    b = normalize(b, modulus);
    i64 result = 0;
    while (b) {
        if (b & 1) result = add_mod(result, a, modulus);
        a = add_mod(a, a, modulus);
        b >>= 1;
    }
    return result;
}

i64 power_mod(i64 base, i64 exponent, i64 modulus) {
    assert(exponent >= 0 && modulus > 0);
    i64 result = 1 % modulus;
    base = normalize(base, modulus);
    while (exponent) {
        if (exponent & 1) result = multiply_mod(result, base, modulus);
        base = multiply_mod(base, base, modulus);
        exponent >>= 1;
    }
    return result;
}

i64 inverse_prime(i64 value, i64 prime) {
    assert(prime > 1 && value % prime != 0);
    return power_mod(value, prime - 2, prime);
}

// ==================== 使用示例 ====================
int main() {
    cout << power(2LL, 10) << '\n';         // 1024
    cout << multiply_mod(8, 9, 17) << '\n'; // 4
    cout << power_mod(2, 10, 17) << '\n';   // 4
    cout << inverse_prime(3, 17) << '\n';   // 6
}
