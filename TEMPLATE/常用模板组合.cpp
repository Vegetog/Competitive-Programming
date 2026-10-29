/*
算法：常用模板组合
简介：集中保留模整数、排列组合、并查集、普通线段树与懒标记线段树；单独使用时优先复制对应专题文件。
复杂度：模幂 O(log b)，组合数预处理 O(n)、查询 O(1)，并查集均摊 O(α(n))，线段树构建 O(n)、单次操作 O(log n)。
约定：C++17，GCC/Clang 的 __int128 扩展；下标从 0 开始，区间 [l,r)；模数为正。
      静态模数为不超过 2^63-1 的素数，逆元要求非零；动态模数小于 2^31，除数须与模数互素。
      动态模数变更后需重建所有模整数；组合数 n < 模数；power 的中间结果须在对应类型范围内。
      Info{} 为合并单位元，Tag{} 为恒等变换；find_first/find_last 需传入可安全剪枝的谓词。
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
template <class T> constexpr T power(T a, u64 b, T res = 1) {
    while (b != 0) {
        if (b & 1) res *= a;
        b >>= 1;
        if (b) a *= a;
    }
    return res;
}

template <u32 kMod> constexpr u32 mul_mod(u32 a, u32 b) {
    return u64(a) * b % kMod;
}

template <u64 kMod> constexpr u64 mul_mod(u64 a, u64 b) {
    return static_cast<u128>(a) * b % kMod;
}

constexpr i64 safe_mod(i64 x, i64 m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

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

template <class U, U kMod> struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}
    template <class T, enable_if_t<is_unsigned_v<T>, int> = 0>
    constexpr ModIntBase(T x_) : x(x_ % mod()) {}
    template <class T, enable_if_t<is_signed_v<T>, int> = 0> constexpr ModIntBase(T x_) {
        i128 v = static_cast<i128>(x_) % mod();
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    static_assert(kMod > 1 && kMod <= 9223372036854775807ULL);
    constexpr static U mod() { return kMod; }

    constexpr U val() const { return x; }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const {
        assert(x != 0);
        return power(*this, mod() - 2);
    }

    constexpr ModIntBase& operator*=(const ModIntBase& rhs) & {
        x = mul_mod<mod()>(x, rhs.val());
        return *this;
    }
    constexpr ModIntBase& operator+=(const ModIntBase& rhs) & {
        if (x >= mod() - rhs.val())
            x -= mod() - rhs.val();
        else
            x += rhs.val();
        return *this;
    }
    constexpr ModIntBase& operator-=(const ModIntBase& rhs) & {
        x = x >= rhs.val() ? x - rhs.val() : mod() - (rhs.val() - x);
        return *this;
    }
    constexpr ModIntBase& operator/=(const ModIntBase& rhs) & { return *this *= rhs.inv(); }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase& rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase& rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream& operator>>(std::istream& is, ModIntBase& a) {
        i64 i = 0;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const ModIntBase& a) {
        return os << a.val();
    }

    friend constexpr bool operator==(const ModIntBase& lhs, const ModIntBase& rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(const ModIntBase& lhs, const ModIntBase& rhs) {
        return !(lhs == rhs);
    }
    friend constexpr bool operator<(const ModIntBase& lhs, const ModIntBase& rhs) {
        return lhs.val() < rhs.val();
    }
    friend constexpr bool operator>(const ModIntBase& lhs, const ModIntBase& rhs) {
        return rhs < lhs;
    }
    friend constexpr bool operator<=(const ModIntBase& lhs, const ModIntBase& rhs) {
        return !(rhs < lhs);
    }
    friend constexpr bool operator>=(const ModIntBase& lhs, const ModIntBase& rhs) {
        return !(lhs < rhs);
    }

private:
    U x;
};

template <u32 kMod> using ModInt = ModIntBase<u32, kMod>;
template <u64 kMod> using ModInt64 = ModIntBase<u64, kMod>;

struct Barrett {
public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    constexpr u32 mod() const { return m; }

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

template <u32 kId> struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}
    template <class T, enable_if_t<is_unsigned_v<T>, int> = 0>
    constexpr DynModInt(T x_) : x(x_ % mod()) {}
    template <class T, enable_if_t<is_signed_v<T>, int> = 0> constexpr DynModInt(T x_) {
        i128 v = static_cast<i128>(x_) % mod();
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    static void set_mod(u32 m) {
        assert(1 <= m && m < (u32{1} << 31));
        bt = Barrett(m);
    }

    static u32 mod() { return bt.mod(); }

    constexpr u32 val() const { return x; }

    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr DynModInt inv() const {
        auto v = inv_gcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt& operator*=(const DynModInt& rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    constexpr DynModInt& operator+=(const DynModInt& rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr DynModInt& operator-=(const DynModInt& rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr DynModInt& operator/=(const DynModInt& rhs) & { return *this *= rhs.inv(); }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt& rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt& rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream& operator>>(std::istream& is, DynModInt& a) {
        i64 i = 0;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const DynModInt& a) {
        return os << a.val();
    }

    friend constexpr bool operator==(const DynModInt& lhs, const DynModInt& rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(const DynModInt& lhs, const DynModInt& rhs) {
        return !(lhs == rhs);
    }
    friend constexpr bool operator<(const DynModInt& lhs, const DynModInt& rhs) {
        return lhs.val() < rhs.val();
    }
    friend constexpr bool operator>(const DynModInt& lhs, const DynModInt& rhs) {
        return rhs < lhs;
    }
    friend constexpr bool operator<=(const DynModInt& lhs, const DynModInt& rhs) {
        return !(rhs < lhs);
    }
    friend constexpr bool operator>=(const DynModInt& lhs, const DynModInt& rhs) {
        return !(lhs < rhs);
    }

private:
    u32 x;
    inline static Barrett bt{998244353};
};

template <typename T> struct Combinations {
    std::vector<T> fac, inv_fac;

    Combinations() {}
    Combinations(int n) { init(n); }

    void init(int n) {
        assert(n >= 0);
        fac.assign(n + 1, 0);
        inv_fac.assign(n + 1, 0);
        fac[0] = inv_fac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
        inv_fac[n] = fac[n].inv();
        for (int i = n - 1; i > 0; i--) inv_fac[i] = inv_fac[i + 1] * (i + 1);
    }

    // 排列数：permutations(n,k) = n!/(n-k)!
    inline T permutations(int a, int b) const {
        if (a < 0 || b < 0 || a < b) return 0;
        assert(a < static_cast<int>(fac.size()));
        return fac[a] * inv_fac[a - b];
    }

    // 组合数：combinations(n,k) = n!/[k!(n-k)!]
    inline T combinations(int a, int b) const {
        if (a < 0 || b < 0 || a < b) return 0;
        assert(a < static_cast<int>(fac.size()));
        return fac[a] * inv_fac[b] * inv_fac[a - b];
    }
};

struct DisjointSet {
    std::vector<int> f, siz;
    DisjointSet(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) std::swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

template <class Info> struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T> SegmentTree(std::vector<T> init_) { init(init_); }
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    template <class T> void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 * std::max(1, n), Info());
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
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info& v) { modify(1, 0, n, p, v); }
    Info range_query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return range_query(2 * p, l, m, x, y) + range_query(2 * p + 1, m, r, x, y);
    }
    Info range_query(int l, int r) { return range_query(1, 0, n, l, r); }
    template <class F> int find_first(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = find_first(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = find_first(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F> int find_first(int l, int r, F pred) {
        return find_first(1, 0, n, l, r, pred);
    }
    template <class F> int find_last(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = find_last(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = find_last(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F> int find_last(int l, int r, F pred) {
        return find_last(1, 0, n, l, r, pred);
    }
};

template <class Info, class Tag> struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T> LazySegmentTree(std::vector<T> init_) { init(init_); }
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    template <class T> void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 * std::max(1, n), Info());
        tag.assign(4 * std::max(1, n), Tag());
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
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(int p, const Tag& v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info& v) { modify(1, 0, n, p, v); }
    Info range_query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return range_query(2 * p, l, m, x, y) + range_query(2 * p + 1, m, r, x, y);
    }
    Info range_query(int l, int r) { return range_query(1, 0, n, l, r); }
    void range_apply(int p, int l, int r, int x, int y, const Tag& v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        range_apply(2 * p, l, m, x, y, v);
        range_apply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void range_apply(int l, int r, const Tag& v) { return range_apply(1, 0, n, l, r, v); }
    template <class F> int find_first(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = find_first(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = find_first(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F> int find_first(int l, int r, F pred) {
        return find_first(1, 0, n, l, r, pred);
    }
    template <class F> int find_last(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = find_last(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = find_last(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F> int find_last(int l, int r, F pred) {
        return find_last(1, 0, n, l, r, pred);
    }
};

// ==================== 使用示例 ====================
struct AddTag {
    i64 add = 0;
    void apply(const AddTag& other) { add += other.add; }
};
struct SumInfo {
    i64 sum = 0;
    int length = 0;
    void apply(const AddTag& tag) { sum += tag.add * length; }
    friend SumInfo operator+(const SumInfo& a, const SumInfo& b) {
        return {a.sum + b.sum, a.length + b.length};
    }
};
int main() {
    using Mint = ModInt<998244353>;
    Combinations<Mint> comb(5);
    cout << comb.combinations(5, 2) << '\n'; // 10
    using DynamicMint = DynModInt<0>;
    DynamicMint::set_mod(12);
    cout << DynamicMint(5).inv() << '\n'; // 5
    DisjointSet dsu(3);
    dsu.merge(0, 1);
    cout << dsu.same(0, 1) << '\n'; // 1
    vector<SumInfo> values{{1, 1}, {2, 1}, {3, 1}};
    SegmentTree<SumInfo> tree(values);
    tree.modify(1, {5, 1});
    cout << tree.range_query(0, 3).sum << '\n'; // 9
    LazySegmentTree<SumInfo, AddTag> lazy(values);
    lazy.range_apply(0, 2, {3});
    cout << lazy.range_query(0, 3).sum << '\n'; // 12
}
