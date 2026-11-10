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

template <i64 P = 998244353> struct Mint {
    static_assert(P == 0 || P > 1, "Modulus must be greater than one");
    inline static i64 dyn_mod = 998244353;
    i64 value = 0;

    // 作用：读取模数；输入：无；输出：当前结构使用的模数。
    static i64 mod() { return P > 0 ? P : dyn_mod; }
    // 作用：设置动态模数；输入：合法的新模数；输出：无返回值，更新共享模数，原有模整数须重新构造。
    static void set_mod(i64 mod) {
        static_assert(P == 0, "Use Mint<0> for a dynamic modulus");
        assert(mod > 1);
        dyn_mod = mod;
    }
    // 作用：构造模整数；输入：整数 x（默认 0）；输出：规范到 [0,mod()) 的模整数。
    Mint(i64 x = 0) : value(x % mod()) {
        if (value < 0) value += mod();
    }
    // 作用：求模幂；输入：当前底数和非负指数 e；输出：模 mod() 的 e 次幂。
    Mint qpow(i64 e) const {
        assert(e >= 0);
        Mint res(1), base = *this;
        for (; e; e >>= 1, base *= base) {
            if (e & 1) res *= base;
        }
        return res;
    }
    // 作用：费马逆元；输入：素数模数下的非零当前值；输出：其模乘逆元。
    Mint inv() const {
        assert(value != 0);
        return qpow(mod() - 2);
    }
    // 作用：取相反数；输入：当前值；输出：相反数副本。
    Mint operator-() const { return Mint(value == 0 ? 0 : mod() - value); }
    // 作用：模加并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    Mint& operator+=(Mint other) {
        value = (i128(value) + other.value) % mod();
        return *this;
    }
    // 作用：模减并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    Mint& operator-=(Mint other) {
        value -= other.value;
        if (value < 0) value += mod();
        return *this;
    }
    // 作用：模乘并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    Mint& operator*=(Mint other) {
        value = i128(value) * other.value % mod();
        return *this;
    }
    // 作用：模除并赋值；输入：当前值和右操作数（除数非零且满足本文件逆元约定）；输出：更新后的当前对象引用。
    Mint& operator/=(Mint other) { return *this *= other.inv(); }
    // 作用：模加法；输入：两个模整数；输出：运算结果副本。
    friend Mint operator+(Mint a, Mint b) { return a += b; }
    // 作用：模减法；输入：两个模整数；输出：运算结果副本。
    friend Mint operator-(Mint a, Mint b) { return a -= b; }
    // 作用：模乘法；输入：两个模整数；输出：运算结果副本。
    friend Mint operator*(Mint a, Mint b) { return a *= b; }
    // 作用：模除法；输入：两个模整数，除数非零且满足本文件逆元约定；输出：运算结果副本。
    friend Mint operator/(Mint a, Mint b) { return a /= b; }
    // 作用：比较相等关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend bool operator==(Mint a, Mint b) { return a.value == b.value; }
    // 作用：比较不等关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend bool operator!=(Mint a, Mint b) { return !(a == b); }
    // 作用：读取整数；输入：输入流和接收对象；输出：原输入流，并在成功读取时更新对象的值。
    friend istream& operator>>(istream& in, Mint& x) {
        i64 value;
        if (in >> value) x = Mint(value);
        return in;
    }
    // 作用：输出整数；输入：输出流和整数对象；输出：原输出流，并写入十进制代表值。
    friend ostream& operator<<(ostream& out, Mint x) { return out << x.value; }
};

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    cout << Mint<>(3).qpow(4) << ' ' << Mint<>(6) / Mint<>(3) << '\n'; // 81 2
    Mint<0>::set_mod(17);
    cout << Mint<0>(-1) + Mint<0>(3) << '\n'; // 2
}
