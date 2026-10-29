/*
算法：通用线段树（单点替换）
简介：通过满足结合律的 Info 合并支持单点替换、区间查询及首末位置查找。
复杂度：时间：建树 O(nC)，修改/查询 O(C log n)；空间 O(nS)，C/S 为选用信息的操作代价/大小。
        首末查找最坏 O(nC)，最值存在性谓词下 O(C log n)。
约定：下标从 0 开始；区间为 [l,r)，边界不得超过原数组；Info{} 表示空区间。
      Info 的 operator+ 须满足结合律，合并严格保持从左到右顺序。
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
template <class I> struct SegmentTree {
    int n = 1, size;
    vector<I> t;
    explicit SegmentTree(const vector<I>& a) : size(a.size()) {
        while (n < (int)a.size()) n <<= 1;
        t.resize(n * 2);
        copy(a.begin(), a.end(), t.begin() + n);
        for (int p = n - 1; p; p--) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    void modify(int p, I v) {
        assert(0 <= p && p < size);
        for (t[p += n] = v; p >>= 1;) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    I query(int l, int r) const {
        assert(0 <= l && l <= r && r <= size);
        I a{}, b{};
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) a = a + t[l++];
            if (r & 1) b = t[--r] + b;
        }
        return a + b;
    }
    // 可选查找段：返回 [l,r) 内首/末个满足 f 的叶子下标，无解返回 -1。
    // f(区间信息)==false 必须保证整段无解；如以 mx>=k 找首/末个值 >=k 的位置。
    template <class F> int find(int l, int r, F f, int d, int p, int s, int e) {
        if (l >= e || r <= s || !f(t[p])) return -1;
        if (e - s == 1) return s;
        int m = (s + e) / 2;
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
// 1. 求和、最值及次数、异或、GCD、按位 AND/OR（有符号 i64 按位运算）。
namespace Basic {

struct Info {
    int len = 0, cmn = 0, cmx = 0;
    i64 sum = 0, mn = LLONG_MAX, mx = LLONG_MIN;
    i64 xr = 0, gc = 0, band = -1, bor = 0;
    Info() = default;
    Info(i64 x)
        : len(1), cmn(1), cmx(1), sum(x), mn(x), mx(x), xr(x), gc(std::gcd(x, 0LL)), band(x),
          bor(x) {}
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    c.cmn = (a.mn == c.mn ? a.cmn : 0) + (b.mn == c.mn ? b.cmn : 0);
    c.cmx = (a.mx == c.mx ? a.cmx : 0) + (b.mx == c.mx ? b.cmx : 0);
    c.xr = a.xr ^ b.xr;
    c.gc = std::gcd(a.gc, b.gc);
    c.band = a.band & b.band;
    c.bor = a.bor | b.bor;
    return c;
}
// s.query(l,r).mx / .mn / .gc / .xr / .sum / .cmx / .cmn / .band / .bor
// 找首个 a[i]>=k：s.find_first(l,r,[&](Info x){return x.len && x.mx>=k;});
} // namespace Basic

// 2. 原始矩：sum=sum(x)，s2=sum(x^2)，s3=sum(x^3)；可用于均值/方差。
namespace Moments {

struct Info {
    i64 len = 0, sum = 0, s2 = 0, s3 = 0;
    Info() = default;
    Info(i64 x) : len(1), sum(x), s2(x * x), s3(x * x * x) {}
};
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.s2 = a.s2 + b.s2;
    c.s3 = a.s3 + b.s3;
    return c;
}
// 整数幂很容易溢出；必要时字段改 __int128，或把每一步改成取模运算。
} // namespace Moments

// 3. 模意义的区间积/和；空区间积为 1。kMod 按题改。
namespace ModProduct {

constexpr i64 kMod = 998244353;
struct Info {
    i64 sum = 0, prod = 1;
    Info() = default;
    Info(i64 x) : sum((x % kMod + kMod) % kMod), prod(sum) {}
};
Info operator+(Info a, Info b) {
    Info c;
    c.sum = (a.sum + b.sum) % kMod;
    c.prod = a.prod * b.prod % kMod;
    return c;
}
} // namespace ModProduct

// 4. LCM（同时带 GCD）；LCM 空单位元为 1，含 0 时 LCM 为 0。
namespace Lcm {

struct Info {
    i64 gc = 0, lc = 1;
    Info() = default;
    Info(i64 x) : gc(std::gcd(x, 0LL)), lc(gc) {}
};
Info operator+(Info a, Info b) {
    Info c;
    c.gc = std::gcd(a.gc, b.gc);
    c.lc = (!a.lc || !b.lc) ? 0 : (i64)((__int128)a.lc / std::gcd(a.lc, b.lc) * b.lc);
    return c;
}
// 前提：每个被维护区间的真实 LCM <= LLONG_MAX；超范围需大整数/专门设计。
} // namespace Lcm

// 5. 非空最大/最小子段和，及最大/最小前缀和、后缀和；合并有方向。
namespace Subarray {

struct Info {
    int len = 0;
    i64 sum = 0, pre = LLONG_MIN, suf = LLONG_MIN, best = LLONG_MIN;
    i64 mpre = LLONG_MAX, msuf = LLONG_MAX, mbest = LLONG_MAX;
    Info() = default;
    Info(i64 x) : len(1), sum(x), pre(x), suf(x), best(x), mpre(x), msuf(x), mbest(x) {}
};
Info operator+(const Info& a, const Info& b) {
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
// ans.best 为非空最大子段和；允许空子段时用 max(0LL,ans.best)。
} // namespace Subarray

// 6. 最大/严格次大、最小/严格次小及各自次数；cx/cn 为 0 表示不存在。
namespace Top2 {

struct Info {
    array<i64, 2> mx{}, mn{};
    array<int, 2> cx{}, cn{};
    Info() = default;
    Info(i64 x) {
        mx[0] = mn[0] = x;
        cx[0] = cn[0] = 1;
    }
};
void pick(array<i64, 2>& v, array<int, 2>& c, array<pair<i64, int>, 4> a, bool desc) {
    sort(a.begin(), a.end(),
         [&](auto x, auto y) { return desc ? x.first > y.first : x.first < y.first; });
    int k = 0;
    for (auto [x, n] : a)
        if (n) {
            if (k && v[k - 1] == x)
                c[k - 1] += n;
            else if (k < 2) {
                v[k] = x;
                c[k++] = n;
            }
        }
}
Info operator+(const Info& a, const Info& b) {
    Info c;
    pick(c.mx, c.cx,
         {{{a.mx[0], a.cx[0]}, {a.mx[1], a.cx[1]}, {b.mx[0], b.cx[0]}, {b.mx[1], b.cx[1]}}}, true);
    pick(c.mn, c.cn,
         {{{a.mn[0], a.cn[0]}, {a.mn[1], a.cn[1]}, {b.mn[0], b.cn[0]}, {b.mn[1], b.cn[1]}}}, false);
    return c;
}
// mx[1] 为严格次大（cx[1]>0 才存在）；第二大允许相等时按 cx[0] 判断。
} // namespace Top2

// 7. 最长连续相同值段；pre/suf 是同值前缀/后缀长度，blocks 是同值段数。
namespace Runs {

struct Info {
    int len = 0, pre = 0, suf = 0, best = 0, blocks = 0;
    i64 first = 0, last = 0;
    Info() = default;
    Info(i64 x) : len(1), pre(1), suf(1), best(1), blocks(1), first(x), last(x) {}
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    bool same = a.last == b.first;
    Info c;
    c.len = a.len + b.len;
    c.first = a.first;
    c.last = b.last;
    c.pre = a.pre + (same && a.pre == a.len ? b.pre : 0);
    c.suf = b.suf + (same && b.suf == b.len ? a.suf : 0);
    c.best = max({a.best, b.best, same ? a.suf + b.pre : 0});
    c.blocks = a.blocks + b.blocks - same;
    return c;
}
} // namespace Runs

// 8. 括号：'(' 记 +1，')' 记 -1；维护含空前缀的最小/最大前缀和。
namespace Brackets {

struct Info {
    int len = 0, sum = 0, mn = 0, mx = 0;
    Info() = default;
    Info(char c) : len(1), sum(c == '(' ? 1 : -1), mn(min(0, sum)), mx(max(0, sum)) {}
};
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.mn = min(a.mn, a.sum + b.mn);
    c.mx = max(a.mx, a.sum + b.mx);
    return c;
}
// a.emplace_back(c); 合法括号串：ans.sum==0 && ans.mn>=0。
// 最少补括号数：ans.sum - 2*ans.mn；此处 mn 包含空前缀，保证 mn<=0。
} // namespace Brackets

// 9. 区间正反多项式哈希：pw=kBase^len，不依赖全局幂表。
namespace Hash {

constexpr i64 kMod = 1000000007, kBase = 911382323;
struct Info {
    int len = 0;
    i64 fwd = 0, rev = 0, pw = 1;
    Info() = default;
    Info(i64 x) : len(1), fwd((x % kMod + kMod) % kMod), rev(fwd), pw(kBase) {}
};
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.pw = a.pw * b.pw % kMod;
    c.fwd = (a.fwd * b.pw + b.fwd) % kMod;
    c.rev = (b.rev * a.pw + a.rev) % kMod;
    return c;
}
// 同长度区间比较 fwd；回文可判 fwd==rev。有碰撞，严格需求可复制一份做双哈希。
} // namespace Hash

// 10. 函数复合：叶子 f(x)=mul*x+add；从左到右依次应用函数，取模。
namespace Affine {

constexpr i64 kMod = 998244353;
struct Info {
    i64 mul = 1, add = 0;
    Info() = default;
    Info(i64 m, i64 b) : mul((m % kMod + kMod) % kMod), add((b % kMod + kMod) % kMod) {}
    i64 eval(i64 x) const { return (mul * ((x % kMod + kMod) % kMod) + add) % kMod; }
};
Info operator+(Info a, Info b) {
    return Info(a.mul * b.mul % kMod, (a.add * b.mul + b.add) % kMod);
}
// a.emplace_back(m,b); s.modify(p,Info(m,b)); s.query(l,r).eval(x) 得 f[r-1](...f[l](x))。
} // namespace Affine

// 11. 2x2 矩阵区间乘积（模意义）；空区间为单位矩阵，方向为 A[l]*...*A[r-1]。
namespace Matrix2 {

constexpr i64 kMod = 998244353;
struct Info {
    i64 a = 1, b = 0, c = 0, d = 1;
    Info() = default;
    Info(i64 a00, i64 a01, i64 a10, i64 a11)
        : a((a00 % kMod + kMod) % kMod), b((a01 % kMod + kMod) % kMod),
          c((a10 % kMod + kMod) % kMod), d((a11 % kMod + kMod) % kMod) {}
};
Info operator+(Info x, Info y) {
    return Info((x.a * y.a + x.b * y.c) % kMod, (x.a * y.b + x.b * y.d) % kMod,
                (x.c * y.a + x.d * y.c) % kMod, (x.c * y.b + x.d * y.d) % kMod);
}
// a.emplace_back(A,B,C,D); 矩阵 DP / 递推转移可按题扩充维度。
} // namespace Matrix2

// 12. 最长严格连续递增/递减段、对应子段数量；不是最长递增子序列 LIS。
namespace Increasing {

struct Info {
    int len = 0, upre = 0, usuf = 0, ubest = 0, dpre = 0, dsuf = 0, dbest = 0;
    i64 first = 0, last = 0, ucnt = 0, dcnt = 0;
    Info() = default;
    Info(i64 x)
        : len(1), upre(1), usuf(1), ubest(1), dpre(1), dsuf(1), dbest(1), first(x), last(x),
          ucnt(1), dcnt(1) {}
};
Info operator+(Info a, Info b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len;
    c.first = a.first;
    c.last = b.last;
    bool up = a.last<b.first, down = a.last> b.first;
    c.upre = a.upre + (up && a.upre == a.len ? b.upre : 0);
    c.usuf = b.usuf + (up && b.usuf == b.len ? a.usuf : 0);
    c.ubest = max({a.ubest, b.ubest, up ? a.usuf + b.upre : 0});
    c.ucnt = a.ucnt + b.ucnt + (up ? 1LL * a.usuf * b.upre : 0);
    c.dpre = a.dpre + (down && a.dpre == a.len ? b.dpre : 0);
    c.dsuf = b.dsuf + (down && b.dsuf == b.len ? a.dsuf : 0);
    c.dbest = max({a.dbest, b.dbest, down ? a.dsuf + b.dpre : 0});
    c.dcnt = a.dcnt + b.dcnt + (down ? 1LL * a.dsuf * b.dpre : 0);
    return c;
}
// 非严格递增/递减时将 < / > 改成 <= / >=；单元素子段计入数量。
} // namespace Increasing

using Info = Basic::Info; // 默认基础统计；按需改为上面任意 namespace::Info。

// ==================== 使用示例 ====================
int main() {
    using Info = Basic::Info;
    vector<Info> a{Info(6), Info(2), Info(6), Info(4)};
    SegmentTree<Info> tree(a);
    tree.modify(1, Info(8));
    auto result = tree.query(0, 4);
    cout << result.sum << ' ' << result.mx << '\n'; // 输出：24 8
    auto reaches = [](Info info) { return info.len && info.mx >= 6; };
    cout << tree.find_first(0, 4, reaches) << ' ' << tree.find_last(0, 4, reaches)
         << '\n'; // 输出：0 2
}
