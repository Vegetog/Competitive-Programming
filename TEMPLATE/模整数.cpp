/*
算法：模整数
简介：封装模意义下的四则运算，支持编译期模数和运行期模数。
复杂度：加减乘 O(1)，幂与逆元 O(log p)；单个整数空间 O(1)。
约定：模数 p > 1；逆元/除法要求 p 为素数且除数非零；设置动态模数后重新构造对象。乘法使用 GCC/Clang 的 __int128。
*/
#include <cassert>
#include <iostream>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
using i128 = __int128;

template <i64 kModulus = 998244353> struct ModInt {
    static_assert(kModulus == 0 || kModulus > 1, "Modulus must be greater than one");
    inline static i64 dynamic_modulus = 998244353;
    i64 value = 0;

    static i64 modulus() { return kModulus > 0 ? kModulus : dynamic_modulus; }
    static void set_modulus(i64 modulus) {
        static_assert(kModulus == 0, "Use ModInt<0> for a dynamic modulus");
        assert(modulus > 1);
        dynamic_modulus = modulus;
    }
    ModInt(i64 x = 0) : value(x % modulus()) {
        if (value < 0) value += modulus();
    }
    ModInt power(i64 exponent) const {
        assert(exponent >= 0);
        ModInt result(1), base = *this;
        for (; exponent; exponent >>= 1, base *= base) {
            if (exponent & 1) result *= base;
        }
        return result;
    }
    ModInt inverse() const {
        assert(value != 0);
        return power(modulus() - 2);
    }
    ModInt operator-() const { return ModInt(value == 0 ? 0 : modulus() - value); }
    ModInt& operator+=(ModInt other) {
        value = (i128(value) + other.value) % modulus();
        return *this;
    }
    ModInt& operator-=(ModInt other) {
        value -= other.value;
        if (value < 0) value += modulus();
        return *this;
    }
    ModInt& operator*=(ModInt other) {
        value = i128(value) * other.value % modulus();
        return *this;
    }
    ModInt& operator/=(ModInt other) { return *this *= other.inverse(); }
    friend ModInt operator+(ModInt a, ModInt b) { return a += b; }
    friend ModInt operator-(ModInt a, ModInt b) { return a -= b; }
    friend ModInt operator*(ModInt a, ModInt b) { return a *= b; }
    friend ModInt operator/(ModInt a, ModInt b) { return a /= b; }
    friend bool operator==(ModInt a, ModInt b) { return a.value == b.value; }
    friend bool operator!=(ModInt a, ModInt b) { return !(a == b); }
    friend istream& operator>>(istream& input, ModInt& x) {
        i64 value;
        if (input >> value) x = ModInt(value);
        return input;
    }
    friend ostream& operator<<(ostream& output, ModInt x) { return output << x.value; }
};

// ==================== 使用示例 ====================
int main() {
    using Mint = ModInt<>;
    cout << Mint(3).power(4) << ' ' << Mint(6) / Mint(3) << '\n'; // 81 2
    ModInt<0>::set_modulus(17);
    cout << ModInt<0>(-1) + ModInt<0>(3) << '\n'; // 2
}
