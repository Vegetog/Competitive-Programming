/*
算法：常用模板组合
简介：集中保留模整数、排列组合、并查集、普通线段树与懒标记线段树；单独使用时优先复制对应专题文件。
复杂度：模幂 O(log b)，组合数预处理 O(n)、查询 O(1)，并查集均摊 O(α(n))，线段树构建 O(n)、单次操作 O(log n)。
约定：C++17，GCC/Clang 的 __int128 扩展；下标从 0 开始，区间 [l,r)；模数为正。
      静态模数为不超过 2^63-1 的素数，逆元要求非零；动态模数小于 2^31，除数须与模数互素。
      动态模数变更后需重建所有模整数；组合数 n < 模数；qpow 的中间结果须在对应类型范围内。
      Info{} 为合并单位元，Tag{} 为恒等变换；first/last 需传入可安全剪枝的谓词。
      各结构空间 O(n)；find 的谓词若无法剪枝，最坏时间 O(n)；64 位模乘使用精确 128 位中间值。
*/
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// ==================== 算法模板 ====================
// 作用：二进制快速幂；输入：底数 a、非负指数 b、初始累乘值 res（默认 1）；输出：res×a^b。
template <class T> constexpr T qpow(T a, u64 b, T res = 1) {
    while (b != 0) {
        if (b & 1) res *= a;
        b >>= 1;
        if (b) a *= a;
    }
    return res;
}

// 作用：精确模乘；输入：无符号 a、b，模板正模数 kMod；输出：a×b mod kMod。
template <u32 kMod> constexpr u32 mul_mod(u32 a, u32 b) {
    return u64(a) * b % kMod;
}

// 作用：精确模乘；输入：无符号 a、b，模板正模数 kMod；输出：a×b mod kMod。
template <u64 kMod> constexpr u64 mul_mod(u64 a, u64 b) {
    return static_cast<u128>(a) * b % kMod;
}

// 作用：规范余数；输入：整数 x、正模数 m；输出：[0,m) 内与 x 同余的值。
constexpr i64 safe_mod(i64 x, i64 m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

// 作用：求 gcd 与约化逆元；输入：整数 a、正模数 b；输出：{g,x}，g=gcd(a,b)，0<=x<b/g 且 ax≡g (mod b)。
constexpr std::pair<i64, i64> inv_gcd(i64 a, i64 b) {
    a = safe_mod(a, b);
    if (a == 0) {
        return {b, 0};
    }

    i64 s = b, t = a;
    i64 m0 = 0, m1 = 1;

    while (t) {
        i64 u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        std::swap(s, t);
        std::swap(m0, m1);
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return {s, m0};
}

template <class U, U kMod> struct MintBase {
public:
    // 作用：构造模零；输入：无；输出：代表值为 0 的模整数。
    constexpr MintBase() : x(0) {}
    // 作用：构造模整数；输入：无符号整数 x_；输出：规范到 [0,mod()) 的模整数。
    template <class T, enable_if_t<is_unsigned_v<T>, int> = 0>
    constexpr MintBase(T x_) : x(x_ % mod()) {}
    // 作用：构造模整数；输入：整数参数；输出：规范到 [0,mod()) 的模整数。
    template <class T, enable_if_t<is_signed_v<T>, int> = 0> constexpr MintBase(T x_) {
        i128 v = static_cast<i128>(x_) % mod();
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    static_assert(kMod > 1 && kMod <= 9223372036854775807ULL);
    // 作用：读取模数；输入：无；输出：当前结构使用的模数。
    constexpr static U mod() { return kMod; }

    // 作用：读取规范余数；输入：当前模整数；输出：[0,mod()) 内的代表值。
    constexpr U val() const { return x; }

    // 作用：取相反数；输入：当前值；输出：相反数副本。
    constexpr MintBase operator-() const {
        MintBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    // 作用：费马逆元；输入：素数模数下的非零当前值；输出：其模乘逆元。
    constexpr MintBase inv() const {
        assert(x != 0);
        return qpow(*this, mod() - 2);
    }

    // 作用：模乘并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    constexpr MintBase& operator*=(const MintBase& rhs) & {
        x = mul_mod<mod()>(x, rhs.val());
        return *this;
    }
    // 作用：模加并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    constexpr MintBase& operator+=(const MintBase& rhs) & {
        if (x >= mod() - rhs.val())
            x -= mod() - rhs.val();
        else
            x += rhs.val();
        return *this;
    }
    // 作用：模减并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    constexpr MintBase& operator-=(const MintBase& rhs) & {
        x = x >= rhs.val() ? x - rhs.val() : mod() - (rhs.val() - x);
        return *this;
    }
    // 作用：模除并赋值；输入：当前值和右操作数（除数非零且满足本文件逆元约定）；输出：更新后的当前对象引用。
    constexpr MintBase& operator/=(const MintBase& rhs) & { return *this *= rhs.inv(); }

    // 作用：模乘法；输入：两个模整数；输出：运算结果副本。
    friend constexpr MintBase operator*(MintBase lhs, const MintBase& rhs) {
        lhs *= rhs;
        return lhs;
    }
    // 作用：模加法；输入：两个模整数；输出：运算结果副本。
    friend constexpr MintBase operator+(MintBase lhs, const MintBase& rhs) {
        lhs += rhs;
        return lhs;
    }
    // 作用：模减法；输入：两个模整数；输出：运算结果副本。
    friend constexpr MintBase operator-(MintBase lhs, const MintBase& rhs) {
        lhs -= rhs;
        return lhs;
    }
    // 作用：模除法；输入：两个模整数，除数非零且满足本文件逆元约定；输出：运算结果副本。
    friend constexpr MintBase operator/(MintBase lhs, const MintBase& rhs) {
        lhs /= rhs;
        return lhs;
    }

    // 作用：读取模整数；输入：流 is 和对象 a；输出：原流，并将局部整数 i 赋给 a；读取前 i 初始化为 0。
    friend constexpr std::istream& operator>>(std::istream& is, MintBase& a) {
        i64 i = 0;
        is >> i;
        a = i;
        return is;
    }
    // 作用：输出整数；输入：输出流和整数对象；输出：原输出流，并写入十进制代表值。
    friend constexpr std::ostream& operator<<(std::ostream& os, const MintBase& a) {
        return os << a.val();
    }

    // 作用：比较相等关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator==(const MintBase& lhs, const MintBase& rhs) {
        return lhs.val() == rhs.val();
    }
    // 作用：比较不等关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator!=(const MintBase& lhs, const MintBase& rhs) {
        return !(lhs == rhs);
    }
    // 作用：比较小于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator<(const MintBase& lhs, const MintBase& rhs) {
        return lhs.val() < rhs.val();
    }
    // 作用：比较大于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator>(const MintBase& lhs, const MintBase& rhs) { return rhs < lhs; }
    // 作用：比较小于等于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator<=(const MintBase& lhs, const MintBase& rhs) {
        return !(rhs < lhs);
    }
    // 作用：比较大于等于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator>=(const MintBase& lhs, const MintBase& rhs) {
        return !(lhs < rhs);
    }

private:
    U x;
};

template <u32 kMod> using Mint = MintBase<u32, kMod>;
template <u64 kMod> using Mint64 = MintBase<u64, kMod>;

struct Barrett {
public:
    // 作用：预处理 Barrett 模乘；输入：1<=m_<2^31；输出：保存模数与倒数近似的对象。
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    // 作用：读取模数；输入：无；输出：当前结构使用的模数。
    constexpr u32 mod() const { return m; }

    // 作用：Barrett 模乘；输入：a、b 均在 [0,m)；输出：a×b mod m。
    constexpr u32 mul(u32 a, u32 b) const {
        u64 z = a;
        z *= b;

        u64 x = u64((u128(z) * im) >> 64);

        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    u32 m;
    u64 im;
};

template <u32 kId> struct DMint {
public:
    // 作用：构造模零；输入：无；输出：代表值为 0 的模整数。
    constexpr DMint() : x(0) {}
    // 作用：构造模整数；输入：无符号整数 x_；输出：规范到 [0,mod()) 的模整数。
    template <class T, enable_if_t<is_unsigned_v<T>, int> = 0>
    constexpr DMint(T x_) : x(x_ % mod()) {}
    // 作用：构造模整数；输入：整数参数；输出：规范到 [0,mod()) 的模整数。
    template <class T, enable_if_t<is_signed_v<T>, int> = 0> constexpr DMint(T x_) {
        i128 v = static_cast<i128>(x_) % mod();
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    // 作用：设置动态模数；输入：合法的新模数；输出：无返回值，更新共享模数，原有模整数须重新构造。
    static void set_mod(u32 m) {
        assert(1 <= m && m < (u32{1} << 31));
        bt = Barrett(m);
    }

    // 作用：读取模数；输入：无；输出：当前结构使用的模数。
    static u32 mod() { return bt.mod(); }

    // 作用：读取规范余数；输入：当前模整数；输出：[0,mod()) 内的代表值。
    constexpr u32 val() const { return x; }

    // 作用：取相反数；输入：当前值；输出：相反数副本。
    constexpr DMint operator-() const {
        DMint res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    // 作用：求动态模逆元；输入：与 mod() 互素的当前值；输出：模 mod() 下的乘法逆元。
    constexpr DMint inv() const {
        auto v = inv_gcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    // 作用：模乘并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    constexpr DMint& operator*=(const DMint& rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    // 作用：模加并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    constexpr DMint& operator+=(const DMint& rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    // 作用：模减并赋值；输入：当前值和右操作数；输出：更新后的当前对象引用。
    constexpr DMint& operator-=(const DMint& rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    // 作用：模除并赋值；输入：当前值和右操作数（除数非零且满足本文件逆元约定）；输出：更新后的当前对象引用。
    constexpr DMint& operator/=(const DMint& rhs) & { return *this *= rhs.inv(); }

    // 作用：模乘法；输入：两个模整数；输出：运算结果副本。
    friend constexpr DMint operator*(DMint lhs, const DMint& rhs) {
        lhs *= rhs;
        return lhs;
    }
    // 作用：模加法；输入：两个模整数；输出：运算结果副本。
    friend constexpr DMint operator+(DMint lhs, const DMint& rhs) {
        lhs += rhs;
        return lhs;
    }
    // 作用：模减法；输入：两个模整数；输出：运算结果副本。
    friend constexpr DMint operator-(DMint lhs, const DMint& rhs) {
        lhs -= rhs;
        return lhs;
    }
    // 作用：模除法；输入：两个模整数，除数非零且满足本文件逆元约定；输出：运算结果副本。
    friend constexpr DMint operator/(DMint lhs, const DMint& rhs) {
        lhs /= rhs;
        return lhs;
    }

    // 作用：读取模整数；输入：流 is 和对象 a；输出：原流，并将局部整数 i 赋给 a；读取前 i 初始化为 0。
    friend constexpr std::istream& operator>>(std::istream& is, DMint& a) {
        i64 i = 0;
        is >> i;
        a = i;
        return is;
    }
    // 作用：输出整数；输入：输出流和整数对象；输出：原输出流，并写入十进制代表值。
    friend constexpr std::ostream& operator<<(std::ostream& os, const DMint& a) {
        return os << a.val();
    }

    // 作用：比较相等关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator==(const DMint& lhs, const DMint& rhs) {
        return lhs.val() == rhs.val();
    }
    // 作用：比较不等关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator!=(const DMint& lhs, const DMint& rhs) { return !(lhs == rhs); }
    // 作用：比较小于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator<(const DMint& lhs, const DMint& rhs) {
        return lhs.val() < rhs.val();
    }
    // 作用：比较大于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator>(const DMint& lhs, const DMint& rhs) { return rhs < lhs; }
    // 作用：比较小于等于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator<=(const DMint& lhs, const DMint& rhs) { return !(rhs < lhs); }
    // 作用：比较大于等于关系；输入：两个操作数；输出：按规范余数比较的布尔结果。
    friend constexpr bool operator>=(const DMint& lhs, const DMint& rhs) { return !(lhs < rhs); }

private:
    u32 x;
    inline static Barrett bt{998244353};
};

template <typename T> struct Comb {
    std::vector<T> fac, ifac;

    // 作用：构造空组合数表；输入：无；输出：未预处理对象，查询前调用 init。
    Comb() {}
    // 作用：预处理组合数表；输入：上界 n>=0 且 n<模数，n! 在 T 中可逆；输出：填好 0..n 阶乘 fac、逆阶乘 ifac 的对象。
    Comb(int n) { init(n); }

    // 作用：重建组合数表；输入：上界 n>=0 且 n<模数，n! 在 T 中可逆；输出：无返回值，重填 fac、ifac[0..n]。
    void init(int n) {
        assert(n >= 0);
        fac.assign(n + 1, 0);
        ifac.assign(n + 1, 0);
        fac[0] = ifac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
        ifac[n] = fac[n].inv();
        for (int i = n - 1; i > 0; i--) ifac[i] = ifac[i + 1] * (i + 1);
    }

    // 作用：查询排列数 A(n,k)=n!/(n-k)!；输入：a=n、b=k，合法 n 已预处理；输出：模意义下的结果，n<0、k<0 或 k>n 时为 0。
    inline T A(int a, int b) const {
        if (a < 0 || b < 0 || a < b) return 0;
        assert(a < static_cast<int>(fac.size()));
        return fac[a] * ifac[a - b];
    }

    // 作用：查询组合数 C(n,k)=n!/[k!(n-k)!]；输入：a=n、b=k，合法 n 已预处理；输出：模意义下的结果，n<0、k<0 或 k>n 时为 0。
    inline T C(int a, int b) const {
        if (a < 0 || b < 0 || a < b) return 0;
        assert(a < static_cast<int>(fac.size()));
        return fac[a] * ifac[b] * ifac[a - b];
    }
};

struct DSU {
    std::vector<int> fa, sz;
    // 作用：初始化并查集；输入：元素数 n；输出：编号 0..n-1 各自成集的对象。
    DSU(int n) : fa(n), sz(n, 1) { std::iota(fa.begin(), fa.end(), 0); }
    // 作用：查找集合代表；输入：元素 x 的 0 下标；输出：根编号，并压缩查找路径。
    int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }
    // 作用：判断连通性；输入：元素 x、y 的 0 下标；输出：位于同一集合时返回 true，并压缩路径。
    bool same(int x, int y) { return find(x) == find(y); }
    // 作用：按大小合并集合；输入：元素 x、y；输出：发生合并返回 true，否则 false；更新父节点与集合大小。
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) std::swap(x, y);
        sz[x] += sz[y];
        fa[y] = x;
        return true;
    }
    // 作用：查询集合大小；输入：元素 x；输出：所在集合的元素数，并压缩路径。
    int size(int x) { return sz[find(x)]; }
};

template <class Info> struct Seg {
    int n;
    std::vector<Info> info;
    // 作用：构造空线段树；输入：无；输出：n=0 的对象，使用前调用 init。
    Seg() : n(0) {}
    // 作用：用统一初值建树；输入：长度 n_、初值 v_（默认单位元）；输出：维护 n_ 个 v_ 的对象。
    Seg(int n_, Info v_ = Info()) { init(n_, v_); }
    // 作用：从数组建树；输入：可转换为 Info 的初始数组 init_；输出：维护该数组的新线段树。
    template <class T> Seg(std::vector<T> init_) { init(init_); }
    // 作用：用统一初值重建；输入：长度 n_、初值 v_；输出：无返回值，重建 n_ 个 v_ 的节点与懒标记（若有）。
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    // 作用：从数组重建；输入：可转换为 Info 的初始数组 init_；输出：无返回值，重置 n、节点信息。
    template <class T> void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 * std::max(1, n), Info());
        // 作用：递归建树；输入：节点 p、覆盖区间 [l,r)，捕获初始数组；输出：无返回值，填入叶子并向上合并。
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        if (n > 0) build(1, 0, n);
    }
    // 作用：合并子节点；输入：节点编号 p；输出：无返回值，用两个子节点的合并结果更新 info[p]。
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    // 作用：递归单点替换；输入：节点 p、覆盖区间 [l,r)、位置 x、新值 v；输出：无返回值，更新该叶子及祖先。
    void set(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            set(2 * p, l, m, x, v);
        } else {
            set(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    // 作用：单点替换；输入：合法 0 下标 p、新值 v；输出：无返回值，更新叶子和相关区间信息。
    void set(int p, const Info& v) { set(1, 0, n, p, v); }
    // 作用：递归区间查询；输入：节点 p、覆盖区间 [l,r)、查询 [x,y)；输出：交集的信息，空交集为 Info{}。
    Info qry(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return qry(2 * p, l, m, x, y) + qry(2 * p + 1, m, r, x, y);
    }
    // 作用：查询区间；输入：合法半开区间 [l,r)；输出：合并后的 Info，空区间为 Info{}。
    Info qry(int l, int r) { return qry(1, 0, n, l, r); }
    // 作用：查找最左位置；输入：节点 p 的区间 [l,r)、查询 [x,y)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1。
    template <class F> int first(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = first(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = first(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    // 作用：查找最左位置；输入：查询区间 [l,r)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1。
    template <class F> int first(int l, int r, F pred) { return first(1, 0, n, l, r, pred); }
    // 作用：查找最右位置；输入：节点 p 的区间 [l,r)、查询 [x,y)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1。
    template <class F> int last(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = last(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = last(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    // 作用：查找最右位置；输入：查询区间 [l,r)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1。
    template <class F> int last(int l, int r, F pred) { return last(1, 0, n, l, r, pred); }
};

template <class Info, class Tag> struct LazySeg {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    // 作用：构造空线段树；输入：无；输出：n=0 的对象，使用前调用 init。
    LazySeg() : n(0) {}
    // 作用：用统一初值建树；输入：长度 n_、初值 v_（默认单位元）；输出：维护 n_ 个 v_ 的对象。
    LazySeg(int n_, Info v_ = Info()) { init(n_, v_); }
    // 作用：从数组建树；输入：可转换为 Info 的初始数组 init_；输出：维护该数组的新线段树。
    template <class T> LazySeg(std::vector<T> init_) { init(init_); }
    // 作用：用统一初值重建；输入：长度 n_、初值 v_；输出：无返回值，重建 n_ 个 v_ 的节点与懒标记（若有）。
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    // 作用：从数组重建；输入：可转换为 Info 的初始数组 init_；输出：无返回值，重置 n、节点信息及懒标记（若有）。
    template <class T> void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 * std::max(1, n), Info());
        tag.assign(4 * std::max(1, n), Tag());
        // 作用：递归建树；输入：节点 p、覆盖区间 [l,r)，捕获初始数组；输出：无返回值，填入叶子并向上合并。
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        if (n > 0) build(1, 0, n);
    }
    // 作用：合并子节点；输入：节点编号 p；输出：无返回值，用两个子节点的合并结果更新 info[p]。
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    // 作用：作用并合成标记；输入：节点 p、后作用的标记 v；输出：无返回值，同时更新 info[p] 与 tag[p]。
    void apply(int p, const Tag& v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    // 作用：下传懒标记；输入：非叶节点编号 p；输出：无返回值，将 tag[p] 作用于子节点后清空它。
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    // 作用：递归单点替换；输入：节点 p、覆盖区间 [l,r)、位置 x、新值 v；输出：无返回值，更新该叶子及祖先。
    void set(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            set(2 * p, l, m, x, v);
        } else {
            set(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    // 作用：单点替换；输入：合法 0 下标 p、新值 v；输出：无返回值，更新叶子和相关区间信息。
    void set(int p, const Info& v) { set(1, 0, n, p, v); }
    // 作用：递归区间查询；输入：节点 p、覆盖区间 [l,r)、查询 [x,y)；输出：交集的信息，空交集为 Info{}；懒树会下传标记。
    Info qry(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return qry(2 * p, l, m, x, y) + qry(2 * p + 1, m, r, x, y);
    }
    // 作用：查询区间；输入：合法半开区间 [l,r)；输出：合并后的 Info，空区间为 Info{}；懒树会下传标记。
    Info qry(int l, int r) { return qry(1, 0, n, l, r); }
    // 作用：递归区间修改；输入：节点 p、覆盖区间 [l,r)、目标 [x,y)、标记 v；输出：无返回值，修改节点信息与懒标记。
    void upd(int p, int l, int r, int x, int y, const Tag& v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        upd(2 * p, l, m, x, y, v);
        upd(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    // 作用：区间修改；输入：合法半开区间 [l,r)、标记 v；输出：无返回值，将变换作用于区间并更新信息。
    void upd(int l, int r, const Tag& v) { return upd(1, 0, n, l, r, v); }
    // 作用：查找最左位置；输入：节点 p 的区间 [l,r)、查询 [x,y)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1；懒树会下传标记。
    template <class F> int first(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = first(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = first(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    // 作用：查找最左位置；输入：查询区间 [l,r)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1；懒树会下传标记。
    template <class F> int first(int l, int r, F pred) { return first(1, 0, n, l, r, pred); }
    // 作用：查找最右位置；输入：节点 p 的区间 [l,r)、查询 [x,y)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1；懒树会下传标记。
    template <class F> int last(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = last(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = last(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    // 作用：查找最右位置；输入：查询区间 [l,r)、可安全剪枝的谓词 pred；输出：满足谓词的叶子下标，无则 -1；懒树会下传标记。
    template <class F> int last(int l, int r, F pred) { return last(1, 0, n, l, r, pred); }
};

// ==================== 使用示例 ====================
struct AddTag {
    i64 add = 0;
    // 作用：合成加法标记；输入：后作用的标记 other；输出：无返回值，将其增量累加到当前标记。
    void apply(const AddTag& other) { add += other.add; }
};
struct SumInfo {
    i64 sum = 0;
    int length = 0;
    // 作用：更新区间和；输入：加法标记 tag 与当前区间信息；输出：无返回值，sum 增加 tag.add×length。
    void apply(const AddTag& tag) { sum += tag.add * length; }
    // 作用：合并区间统计；输入：左右区间信息 a、b；输出：总和与长度分别相加的新信息。
    friend SumInfo operator+(const SumInfo& a, const SumInfo& b) {
        return {a.sum + b.sum, a.length + b.length};
    }
};
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    using Z = Mint<998244353>;
    Comb<Z> comb(5);
    cout << comb.C(5, 2) << '\n'; // 10
    using Dyn = DMint<0>;
    Dyn::set_mod(12);
    cout << Dyn(5).inv() << '\n'; // 5
    DSU dsu(3);
    dsu.merge(0, 1);
    cout << dsu.same(0, 1) << '\n'; // 1
    vector<SumInfo> a{{1, 1}, {2, 1}, {3, 1}};
    Seg<SumInfo> tree(a);
    tree.set(1, {5, 1});
    cout << tree.qry(0, 3).sum << '\n'; // 9
    LazySeg<SumInfo, AddTag> lazy(a);
    lazy.upd(0, 2, {3});
    cout << lazy.qry(0, 3).sum << '\n'; // 12
}
