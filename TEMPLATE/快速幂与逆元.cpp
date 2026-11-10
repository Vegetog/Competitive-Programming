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

// 作用：二进制快速幂；输入：底数 base 和非负指数 e，中间乘法须不溢出；输出：base^e。
template <class T> T qpow(T base, i64 e) {
    assert(e >= 0);
    T res = 1;
    while (e) {
        if (e & 1) res *= base;
        e >>= 1;
        if (e) base *= base;
    }
    return res;
}

// 作用：规范余数；输入：整数 value 和正模数 mod；输出：[0,mod) 内与 value 同余的值。
i64 norm(i64 value, i64 mod) {
    value %= mod;
    return value < 0 ? value + mod : value;
}

// 作用：无溢出模加；输入：a、b 均在 [0,mod)，mod 为正；输出：(a+b) mod mod。
i64 add_mod(i64 a, i64 b, i64 mod) {
    return a >= mod - b ? a - (mod - b) : a + b;
}

// 作用：无溢出模乘；输入：整数 a、b 和正模数 mod；输出：a×b mod mod 的非负余数。
i64 mul_mod(i64 a, i64 b, i64 mod) {
    assert(mod > 0);
    a = norm(a, mod);
    b = norm(b, mod);
    i64 res = 0;
    while (b) {
        if (b & 1) res = add_mod(res, a, mod);
        a = add_mod(a, a, mod);
        b >>= 1;
    }
    return res;
}

// 作用：求模幂；输入：底数 base、非负指数 e、正模数 mod；输出：base^e mod mod 的非负余数。
i64 qpow_mod(i64 base, i64 e, i64 mod) {
    assert(e >= 0 && mod > 0);
    i64 res = 1 % mod;
    base = norm(base, mod);
    while (e) {
        if (e & 1) res = mul_mod(res, base, mod);
        base = mul_mod(base, base, mod);
        e >>= 1;
    }
    return res;
}

// 作用：费马逆元；输入：value、素数 prime，value 不被 prime 整除；输出：value 在模 prime 下的逆元。
i64 inv(i64 value, i64 prime) {
    assert(prime > 1 && value % prime != 0);
    return qpow_mod(value, prime - 2, prime);
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    cout << qpow(2LL, 10) << '\n';       // 1024
    cout << mul_mod(8, 9, 17) << '\n';   // 4
    cout << qpow_mod(2, 10, 17) << '\n'; // 4
    cout << inv(3, 17) << '\n';          // 6
}
