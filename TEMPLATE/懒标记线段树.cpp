/*
算法：通用懒标记线段树
简介：通过 Info/Tag 组合支持区间修改、区间查询及首末位置查找。
复杂度：时间：建树 O(nC)，修改/查询 O(C log n)；空间 O(nS)，C/S 为选用信息的操作代价/大小。
        首末查找最坏 O(nC)，最值存在性谓词下 O(C log n)。
约定：下标从 0 开始；区间为 [l,r)，边界不得超过原数组；Info{} 表示空区间。
      Tag{} 为恒等变换，旧标记.apply(新标记) 按先旧后新复合。
      全部中间整数须在 i64 范围内；GCD/相邻差的绝对值也须可表示。__int128 需 GCC/Clang。
*/
#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
template <class I, class T> struct LazySegmentTree {
    int n = 1, size;
    vector<I> t;
    vector<T> z;
    explicit LazySegmentTree(const vector<I>& a) : size(a.size()) {
        while (n < (int)a.size()) n <<= 1;
        t.resize(n * 2);
        z.resize(n * 2);
        copy(a.begin(), a.end(), t.begin() + n);
        for (int p = n - 1; p; p--) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    void apply(int p, const T& v) {
        t[p].apply(v);
        z[p].apply(v);
    }
    // v 非空则修改，为空则查询。
    I work(int l, int r, const T* v, int p, int s, int e) {
        if (l >= e || r <= s) return {};
        if (l <= s && e <= r) {
            if (v) apply(p, *v);
            return t[p];
        }
        int m = (s + e) / 2;
        apply(p * 2, z[p]);
        apply(p * 2 + 1, z[p]);
        z[p] = {};
        I a = work(l, r, v, p * 2, s, m) + work(l, r, v, p * 2 + 1, m, e);
        if (v) t[p] = t[p * 2] + t[p * 2 + 1];
        return a;
    }
    void range_apply(int l, int r, T v) {
        assert(0 <= l && l <= r && r <= size);
        work(l, r, &v, 1, 0, n);
    }
    I query(int l, int r) {
        assert(0 <= l && l <= r && r <= size);
        return work(l, r, nullptr, 1, 0, n);
    }
    // 可选查找段：返回 [l,r) 内首/末个满足 f 的叶子下标，无解返回 -1。
    // f(区间信息)==false 必须保证整段无解；如以 mx>=k 找首/末个值 >=k 的位置。
    template <class F> int find(int l, int r, F f, int d, int p, int s, int e) {
        if (l >= e || r <= s || !f(t[p])) return -1;
        if (e - s == 1) return s;
        int m = (s + e) / 2;
        apply(p * 2, z[p]);
        apply(p * 2 + 1, z[p]);
        z[p] = {};
        int a = find(l, r, f, d, p * 2 + d, d ? m : s, d ? e : m);
        return a != -1 ? a : find(l, r, f, d, p * 2 + !d, d ? s : m, d ? m : e);
    }
    template <class F> int find_first(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= size);
        return find(l, r, f, 0, 1, 0, n);
    }
    template <class F> int find_last(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= size);
        return find(l, r, f, 1, 1, 0, n);
    }
};

// 复制树框架和所需的一个命名空间即可；不必复制整份菜单。
// 数值叶子用 Info(x)，有效的零叶子用 Info(0)，Info{} 是空区间单位元。
// 字符/函数/矩阵/带下标方案按构造参数初始化；下方保留全部原有信息组合。
// 1. 常用短版：区间加/赋值，查询和、最值及次数。set 标志避免用数值当哨兵。
namespace AddSet {

struct Tag {
    bool has = false;
    i64 set = 0, add = 0;
    static Tag plus(i64 x) {
        Tag t;
        t.add = x;
        return t;
    }
    static Tag assign(i64 x) {
        Tag t;
        t.has = true;
        t.set = x;
        return t;
    }
    void apply(Tag t) {
        if (t.has)
            *this = t;
        else
            add += t.add;
    }
};
struct Info {
    i64 len = 0, sum = 0, mn = LLONG_MAX, mx = LLONG_MIN, cmn = 0, cmx = 0;
    Info() = default;
    Info(i64 x) : len(1), sum(x), mn(x), mx(x), cmn(1), cmx(1) {}
    void apply(Tag t) {
        if (!len) return;
        if (t.has) {
            sum = t.set * len;
            mn = mx = t.set;
            cmn = cmx = len;
        }
        sum += t.add * len;
        mn += t.add;
        mx += t.add;
    }
};
Info operator+(Info a, Info b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    c.cmn = (a.mn == c.mn ? a.cmn : 0) + (b.mn == c.mn ? b.cmn : 0);
    c.cmx = (a.mx == c.mx ? a.cmx : 0) + (b.mx == c.mx ? b.cmx : 0);
    return c;
}
// s.range_apply(l,r,Tag::plus(v)); s.range_apply(l,r,Tag::assign(v)); s.query(l,r).sum / .mn / .mx
} // namespace AddSet

// 2. 完整整数仿射：x -> mul*x+add（加、乘、赋值），查询和/平方和/最值/GCD。
// GCD 借助首尾值 + 相邻差 GCD：gc=gcd(first,gd)，加法只改变 first，差不变。
namespace Affine {

struct Tag {
    i64 mul = 1, add = 0;
    void apply(Tag t) {
        mul *= t.mul;
        add = add * t.mul + t.add;
    }
};
struct Info {
    i64 len = 0, sum = 0, s2 = 0, mn = LLONG_MAX, mx = LLONG_MIN, cmn = 0, cmx = 0;
    i64 first = 0, last = 0, gd = 0, gc = 0;
    Info() = default;
    Info(i64 x)
        : len(1), sum(x), s2(x * x), mn(x), mx(x), cmn(1), cmx(1), first(x), last(x),
          gc(std::gcd(x, 0LL)) {}
    void apply(Tag t) {
        if (!len) return;
        s2 = t.mul * t.mul * s2 + 2 * t.mul * t.add * sum + t.add * t.add * len;
        sum = t.mul * sum + t.add * len; // 必须在 s2 后更新，s2 用旧 sum。
        if (t.mul >= 0) {
            mn = mn * t.mul + t.add;
            mx = mx * t.mul + t.add;
        } else {
            i64 v = mn;
            mn = mx * t.mul + t.add;
            mx = v * t.mul + t.add;
            swap(cmn, cmx);
        }
        if (!t.mul) cmn = cmx = len;
        first = first * t.mul + t.add;
        last = last * t.mul + t.add;
        gd *= std::gcd(t.mul, 0LL);
        gc = std::gcd(first, gd);
    }
};
Info operator+(Info a, Info b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.s2 = a.s2 + b.s2;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    c.cmn = (a.mn == c.mn ? a.cmn : 0) + (b.mn == c.mn ? b.cmn : 0);
    c.cmx = (a.mx == c.mx ? a.cmx : 0) + (b.mx == c.mx ? b.cmx : 0);
    c.first = a.first;
    c.last = b.last;
    c.gd = std::gcd(std::gcd(a.gd, b.gd), b.first - a.last);
    c.gc = std::gcd(c.first, c.gd);
    return c;
}
// 加 v：{1,v}；乘 v：{v,0}；赋值 v：{0,v}。乘负数会交换最小/最大及次数。
// s.range_apply(l,r,{1,v}); s.query(l,r).gc / .s2 / .sum / .mn / .mx
// 不需要平方和/GCD时删对应字段及构造、合并、apply，省抄写和溢出风险。
} // namespace Affine

// 3. 模仿射：区间加/乘/赋值，维护 sum 和平方和；模运算下不维护大小/GCD。
namespace ModAffine {

constexpr i64 kMod = 998244353;
i64 norm(i64 x) {
    return (x % kMod + kMod) % kMod;
}
struct Tag {
    i64 mul = 1, add = 0;
    Tag() = default;
    Tag(i64 m, i64 b) : mul(norm(m)), add(norm(b)) {}
    void apply(Tag t) {
        mul = mul * t.mul % kMod;
        add = (add * t.mul + t.add) % kMod;
    }
};
struct Info {
    i64 len = 0, sum = 0, s2 = 0;
    Info() = default;
    Info(i64 x) : len(1), sum(norm(x)), s2(sum * sum % kMod) {}
    void apply(Tag t) {
        s2 = (t.mul * t.mul % kMod * s2 % kMod + 2 * t.mul * t.add % kMod * sum % kMod +
              t.add * t.add % kMod * (len % kMod) % kMod) %
             kMod;
        sum = (sum * t.mul + t.add * (len % kMod)) % kMod;
    }
};
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = (a.sum + b.sum) % kMod;
    c.s2 = (a.s2 + b.s2) % kMod;
    return c;
}
// s.range_apply(l,r,Tag(1,v)); Tag(v,0) 乘 v；Tag(0,v) 赋值 v。
// kMod 默认约 1e9，修改得很大时乘法须使用 __int128。
} // namespace ModAffine

// 4. 位运算：区间 AND/OR/XOR/赋值；逐位维护 1 的个数，查询和/异或/AND/OR。
// kBits 按题改（1<=kBits<=63），值/掩码必须是非负且小于 2^kBits。每次操作 O(kBits log n)。
namespace Bitwise {

using u64 = unsigned long long;
constexpr int kBits = 30;
constexpr u64 kMask = (1ULL << kBits) - 1;
struct Tag {
    u64 zero = 0, one = kMask; // 原位 0 -> zero 的该位，原位 1 -> one 的该位。
    static Tag make_xor(u64 x) { return {x, kMask ^ x}; }
    static Tag make_and(u64 x) { return {0, x}; }
    static Tag make_or(u64 x) { return {x, kMask}; }
    static Tag assign(u64 x) { return {x, x}; }
    void apply(Tag t) {
        zero = ((~zero & t.zero) | (zero & t.one)) & kMask;
        one = ((~one & t.zero) | (one & t.one)) & kMask;
    }
};
struct Info {
    int len = 0;
    array<int, kBits> cnt{};
    Info() = default;
    Info(u64 x) : len(1) {
        for (int i = 0; i < kBits; i++) cnt[i] = x >> i & 1;
    }
    void apply(Tag t) {
        for (int i = 0; i < kBits; i++) {
            int z = t.zero >> i & 1, o = t.one >> i & 1;
            cnt[i] = z * (len - cnt[i]) + o * cnt[i];
        }
    }
    __int128 sum() const { // kBits 较大时区间和可能超出 u64，统一用 __int128。
        __int128 ans = 0;
        for (int i = 0; i < kBits; i++) ans += (__int128)cnt[i] << i;
        return ans;
    }
    u64 xr() const {
        u64 x = 0;
        for (int i = 0; i < kBits; i++)
            if (cnt[i] & 1) x |= 1ULL << i;
        return x;
    }
    u64 band() const {
        u64 x = 0;
        for (int i = 0; i < kBits; i++)
            if (cnt[i] == len) x |= 1ULL << i;
        return x;
    }
    u64 bor() const {
        u64 x = 0;
        for (int i = 0; i < kBits; i++)
            if (cnt[i]) x |= 1ULL << i;
        return x;
    }
};
Info operator+(Info a, Info b) {
    a.len += b.len;
    for (int i = 0; i < kBits; i++) a.cnt[i] += b.cnt[i];
    return a;
}
// s.range_apply(l,r,Tag::make_xor(v)); 也可 make_and/make_or/assign；ans.sum()/xr()/band()/bor()。
// kBits=30、n=2e5 时 cnt 数组内存较大；只需异或查询+异或修改时可简化为 xr+len。
} // namespace Bitwise

// 5. 01 串区间赋 0/1、翻转；查询 1 的个数、连续段、交替段、同值段数、逆序对。
namespace BinaryRuns {

struct Tag {
    int zero = 0, one = 1;
    static Tag flip() { return {1, 0}; }
    static Tag assign(int x) { return {x, x}; }
    void apply(Tag t) {
        zero = zero ? t.one : t.zero;
        one = one ? t.one : t.zero;
    }
};
struct Info {
    int len = 0, sum = 0, first = 0, last = 0, blocks = 0;
    i64 inv = 0; // 01 逆序对：前面的 1 与后面的 0。
    array<int, 2> pre{}, suf{}, best{};
    int apre = 0, asuf = 0, abest = 0;
    Info() = default;
    Info(int x) : len(1), sum(x), first(x), last(x), blocks(1), apre(1), asuf(1), abest(1) {
        pre[x] = suf[x] = best[x] = 1;
    }
    void apply(Tag t) {
        if (!len) return;
        if (t.zero == t.one) {
            int x = t.zero;
            sum = x * len;
            first = last = x;
            blocks = 1;
            inv = 0;
            pre = suf = best = {0, 0};
            pre[x] = suf[x] = best[x] = len;
            apre = asuf = abest = 1;
        } else if (t.zero == 1) {
            inv = 1LL * sum * (len - sum) - inv;
            sum = len - sum;
            first ^= 1;
            last ^= 1;
            swap(pre[0], pre[1]);
            swap(suf[0], suf[1]);
            swap(best[0], best[1]);
        }
    }
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.first = a.first;
    c.last = b.last;
    c.inv = a.inv + b.inv + 1LL * a.sum * (b.len - b.sum);
    c.blocks = a.blocks + b.blocks - (a.last == b.first);
    for (int x = 0; x < 2; x++) {
        c.pre[x] = a.pre[x] + (a.pre[x] == a.len ? b.pre[x] : 0);
        c.suf[x] = b.suf[x] + (b.suf[x] == b.len ? a.suf[x] : 0);
        c.best[x] = max({a.best[x], b.best[x], a.suf[x] + b.pre[x]});
    }
    bool alt = a.last != b.first;
    c.apre = a.apre + (alt && a.apre == a.len ? b.apre : 0);
    c.asuf = b.asuf + (alt && b.asuf == b.len ? a.asuf : 0);
    c.abest = max({a.abest, b.abest, alt ? a.asuf + b.apre : 0});
    return c;
}
// s.range_apply(l,r,Tag::flip()); s.range_apply(l,r,Tag::assign(0));
// ans.best[1]/sum/abest/blocks/inv。
} // namespace BinaryRuns

// 6. 区间赋值，查询非空最大/最小子段和；这里不能直接加入区间加法标记。
namespace AssignSubarray {

struct Tag {
    bool has = false;
    i64 value = 0;
    static Tag assign(i64 x) { return {true, x}; }
    void apply(Tag t) {
        if (t.has) *this = t;
    }
};
struct Info {
    i64 len = 0, sum = 0, pre = LLONG_MIN, suf = LLONG_MIN, best = LLONG_MIN;
    i64 mpre = LLONG_MAX, msuf = LLONG_MAX, mbest = LLONG_MAX;
    Info() = default;
    Info(i64 x) : len(1), sum(x), pre(x), suf(x), best(x), mpre(x), msuf(x), mbest(x) {}
    void apply(Tag t) {
        if (!len || !t.has) return;
        sum = t.value * len;
        pre = suf = best = max(t.value, sum);
        mpre = msuf = mbest = min(t.value, sum);
    }
};
Info operator+(Info a, Info b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.pre = max(a.pre, a.sum + b.pre);
    c.suf = max(b.suf, b.sum + a.suf);
    c.best = max({a.best, b.best, a.suf + b.pre});
    c.mpre = min(a.mpre, a.sum + b.mpre);
    c.msuf = min(b.msuf, b.sum + a.msuf);
    c.mbest = min({a.mbest, b.mbest, a.msuf + b.mpre});
    return c;
}
// s.range_apply(l,r,Tag::assign(v)); ans.best / .mbest；允许空子段时取 max(0LL,ans.best)。
} // namespace AssignSubarray

// 7. 等差加法：对全局下标 i 加 k*i+b；维护区间和。不需要按左右子段调整 Tag。
namespace Progression {

struct Tag {
    i64 k = 0, b = 0;
    void apply(Tag t) {
        k += t.k;
        b += t.b;
    }
};
struct Info {
    i64 len = 0, sum = 0, idx = 0;
    Info() = default;
    Info(i64 x, i64 i) : len(1), sum(x), idx(i) {}
    void apply(Tag t) { sum += t.k * idx + t.b * len; }
};
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.idx = a.idx + b.idx;
    return c;
}
// 初始化 a.emplace_back(v[i],i)，idx 是全局下标和，不是当前区间的相对位置。
// 在 [l,r) 加首项 A、公差 D：s.range_apply(l,r,{D,A-D*l}); ans.sum。
// 可扩展为多项式加法：额外存 sum(i^2)、sum(i^3)...，Tag 存对应系数。
} // namespace Progression

// 8. 括号区间赋 '(' / ')'、翻转左右括号；维护含空前缀的最小/最大前缀和。
namespace Brackets {

struct Tag {
    int mul = 1, add = 0; // 只使用恒等 {1,0}、翻转 {-1,0}、赋值 {0,+/-1}。
    static Tag flip() { return {-1, 0}; }
    static Tag assign(char c) { return {0, c == '(' ? 1 : -1}; }
    void apply(Tag t) {
        mul *= t.mul;
        add = add * t.mul + t.add;
    }
};
struct Info {
    int len = 0, sum = 0, mn = 0, mx = 0;
    Info() = default;
    Info(char c) : len(1), sum(c == '(' ? 1 : -1), mn(min(0, sum)), mx(max(0, sum)) {}
    void apply(Tag t) {
        if (!len) return;
        if (!t.mul) {
            sum = t.add * len;
            mn = min(0, sum);
            mx = max(0, sum);
        } else if (t.mul == -1) {
            sum = -sum;
            int old = mn;
            mn = -mx;
            mx = -old;
        }
    }
};
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.mn = min(a.mn, a.sum + b.mn);
    c.mx = max(a.mx, a.sum + b.mx);
    return c;
}
// a.emplace_back(c); s.range_apply(l,r,Tag::flip()); s.range_apply(l,r,Tag::assign('('));
// 合法括号串：ans.sum==0 && ans.mn>=0；最少补括号数：ans.sum-2*ans.mn。
} // namespace Brackets

// 9. 短版：区间逐元素异或/赋值，只查询区间异或。不查询区间和时无需逐位计数。
namespace XorOnly {

struct Tag {
    bool has = false;
    i64 set = 0, xr = 0;
    static Tag make_xor(i64 x) {
        Tag t;
        t.xr = x;
        return t;
    }
    static Tag assign(i64 x) { return {true, x, 0}; }
    void apply(Tag t) {
        if (t.has)
            *this = t;
        else
            xr ^= t.xr;
    }
};
struct Info {
    int len = 0;
    i64 xr = 0;
    Info() = default;
    Info(i64 x) : len(1), xr(x) {}
    void apply(Tag t) {
        if (t.has) xr = (len & 1) ? t.set : 0;
        if (len & 1) xr ^= t.xr;
    }
};
Info operator+(Info a, Info b) {
    a.len += b.len;
    a.xr ^= b.xr;
    return a;
}
// s.range_apply(l,r,Tag::make_xor(v)); s.range_apply(l,r,Tag::assign(v)); s.query(l,r).xr。
} // namespace XorOnly

// 需要其他信息时：合并须满足结合律；apply 须与合并兼容，且 Tag 可正确复合。
// 区间 chmin/chmax + sum 通常需要 Segment Tree Beats，不能只换这里的 Tag。
// 区间取模/开方也不能直接当普通懒标记；要利用最值剪枝、下降到子节点。
// 区间逆序涉及顺序重排，此固定下标框架不能靠交换 Info 首尾完成，通常用隐式 Treap。
using Info = AddSet::Info;
using Tag = AddSet::Tag; // 换方案时两个别名一起改，例如 Affine::Info / Affine::Tag。

// ==================== 使用示例 ====================
int main() {
    using Info = AddSet::Info;
    using Tag = AddSet::Tag;
    vector<Info> a{Info(1), Info(2), Info(3), Info(4)};
    LazySegmentTree<Info, Tag> tree(a);
    tree.range_apply(1, 4, Tag::plus(2));   // [1,4,5,6]
    tree.range_apply(2, 4, Tag::assign(7)); // [1,4,7,7]
    cout << tree.query(0, 4).sum << '\n';   // 输出：19
    auto reaches = [](Info info) { return info.len && info.mx >= 7; };
    cout << tree.find_first(0, 4, reaches) << '\n'; // 输出：2
}
