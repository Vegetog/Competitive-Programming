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
template <class I, class T> struct LazySeg {
    int n = 1, sz;
    vector<I> t;
    vector<T> z;
    // 作用：建立懒标记线段树；输入：叶子信息数组 a；输出：节点信息与恒等标记组成的 LazySeg。
    explicit LazySeg(const vector<I>& a) : sz(a.size()) {
        while (n < (int)a.size()) n <<= 1;
        t.resize(n * 2);
        z.resize(n * 2);
        copy(a.begin(), a.end(), t.begin() + n);
        for (int p = n - 1; p; p--) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    // 作用：对节点应用标记；输入：节点 p、新标记 v；输出：更新 t[p] 并按先旧后新复合 z[p]。
    void apply(int p, const T& v) {
        t[p].apply(v);
        z[p].apply(v);
    }
    // v 非空则修改，为空则查询。
    // 作用：递归修改/查询；输入：[l,r)、标记指针 v、节点 p 及区间 [s,e)；输出：交集信息，v 非空时修改区间元素；递归可能下传标记并更新 t/z。
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
    // 作用：区间应用标记；输入：半开区间 [l,r)、标记 v；输出：更新区间信息与懒标记，无返回值。
    void upd(int l, int r, T v) {
        assert(0 <= l && l <= r && r <= sz);
        work(l, r, &v, 1, 0, n);
    }
    // 作用：查询区间信息；输入：半开区间 [l,r)；输出：从左到右合并的 I，空区间返回 I{}；可能下传标记并更新 t/z。
    I qry(int l, int r) {
        assert(0 <= l && l <= r && r <= sz);
        return work(l, r, nullptr, 1, 0, n);
    }
    // 可选查找段：返回 [l,r) 内首/末个满足 f 的叶子下标，无解返回 -1。
    // f(区间信息)==false 必须保证整段无解；如以 mx>=k 找首/末个值 >=k 的位置。
    // 作用：递归查找位置；输入：[l,r)、剪枝谓词 f、方向 d（0 首/1 末）、节点 p 及区间 [s,e)；输出：目标下标，无解 -1；可能下传标记并更新 t/z。
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
    // 作用：找首个符合条件的位置；输入：[l,r)、f（整段为 false 时须保证无解）；输出：最小下标，无解 -1；可能下传标记并更新 t/z。
    template <class F> int first(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= sz);
        return find(l, r, f, 0, 1, 0, n);
    }
    // 作用：找末个符合条件的位置；输入：[l,r)、f（整段为 false 时须保证无解）；输出：最大下标，无解 -1；可能下传标记并更新 t/z。
    template <class F> int last(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= sz);
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
    // 作用：构造加法标记；输入：增量 x；输出：表示每个元素加 x 的 Tag。
    static Tag plus(i64 x) {
        Tag t;
        t.add = x;
        return t;
    }
    // 作用：构造赋值标记；输入：值 x；输出：把整段设为 x 的 Tag。
    static Tag assign(i64 x) {
        Tag t;
        t.has = true;
        t.set = x;
        return t;
    }
    // 作用：复合加法/赋值标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        if (t.has)
            *this = t;
        else
            add += t.add;
    }
};
struct Info {
    i64 len = 0, sum = 0, mn = LLONG_MAX, mx = LLONG_MIN, cmn = 0, cmx = 0;
    // 作用：构造空区间单位元；输入：无；输出：可参与加法/赋值统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：单个值 x；输出：对应的加法/赋值统计 Info。
    Info(i64 x) : len(1), sum(x), mn(x), mx(x), cmn(1), cmx(1) {}
    // 作用：更新区间统计；输入：加法/赋值标记 t；输出：原地更新和、最值及其次数，无返回值。
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
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、和、最值及其次数。
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
// s.upd(l,r,Tag::plus(v)); s.upd(l,r,Tag::assign(v)); s.qry(l,r).sum / .mn / .mx
} // namespace AddSet

// 2. 完整整数仿射：x -> mul*x+add（加、乘、赋值），查询和/平方和/最值/GCD。
// GCD 借助首尾值 + 相邻差 GCD：gc=gcd(first,gd)，加法只改变 first，差不变。
namespace Affine {

struct Tag {
    i64 mul = 1, add = 0;
    // 作用：复合整数仿射变换 x→mul*x+add标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        mul *= t.mul;
        add = add * t.mul + t.add;
    }
};
struct Info {
    i64 len = 0, sum = 0, s2 = 0, mn = LLONG_MAX, mx = LLONG_MIN, cmn = 0, cmx = 0;
    i64 first = 0, last = 0, gd = 0, gc = 0;
    // 作用：构造空区间单位元；输入：无；输出：可参与整数仿射统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：单个值 x；输出：对应的整数仿射统计 Info。
    Info(i64 x)
        : len(1), sum(x), s2(x * x), mn(x), mx(x), cmn(1), cmx(1), first(x), last(x),
          gc(std::gcd(x, 0LL)) {}
    // 作用：更新区间统计；输入：整数仿射变换 x→mul*x+add标记 t；输出：原地更新和、平方和、最值及次数、首尾值、差分 GCD 与元素 GCD，无返回值。
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
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、和、平方和、最值及次数、首尾值、差分 GCD 与元素 GCD。
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
// s.upd(l,r,{1,v}); s.qry(l,r).gc / .s2 / .sum / .mn / .mx
// 不需要平方和/GCD时删对应字段及构造、合并、apply，省抄写和溢出风险。
} // namespace Affine

// 3. 模仿射：区间加/乘/赋值，维护 sum 和平方和；模运算下不维护大小/GCD。
namespace ModAffine {

constexpr i64 kMod = 998244353;
// 作用：规范化模数值；输入：整数 x；输出：[0,kMod) 内与 x 同余的值。
i64 norm(i64 x) {
    return (x % kMod + kMod) % kMod;
}
struct Tag {
    i64 mul = 1, add = 0;
    // 作用：构造恒等标记；输入：无；输出：不改变元素的模仿射 Tag。
    Tag() = default;
    // 作用：构造模仿射标记；输入：系数 m、b；输出：表示 x→m*x+b 的 Tag（系数归一化）。
    Tag(i64 m, i64 b) : mul(norm(m)), add(norm(b)) {}
    // 作用：复合模仿射变换 x→mul*x+add标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        mul = mul * t.mul % kMod;
        add = (add * t.mul + t.add) % kMod;
    }
};
struct Info {
    i64 len = 0, sum = 0, s2 = 0;
    // 作用：构造空区间单位元；输入：无；输出：可参与模仿射统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：单个值 x；输出：对应的模仿射统计 Info。
    Info(i64 x) : len(1), sum(norm(x)), s2(sum * sum % kMod) {}
    // 作用：更新区间统计；输入：模仿射变换 x→mul*x+add标记 t；输出：原地更新模和与模平方和，无返回值。
    void apply(Tag t) {
        s2 = (t.mul * t.mul % kMod * s2 % kMod + 2 * t.mul * t.add % kMod * sum % kMod +
              t.add * t.add % kMod * (len % kMod) % kMod) %
             kMod;
        sum = (sum * t.mul + t.add * (len % kMod)) % kMod;
    }
};
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、模和与模平方和。
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = (a.sum + b.sum) % kMod;
    c.s2 = (a.s2 + b.s2) % kMod;
    return c;
}
// s.upd(l,r,Tag(1,v)); Tag(v,0) 乘 v；Tag(0,v) 赋值 v。
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
    // 作用：构造异或标记；输入：异或值 x；输出：逐元素异或 x 的 Tag。
    static Tag xor_tag(u64 x) { return {x, kMask ^ x}; }
    // 作用：构造按位与标记；输入：掩码 x；输出：逐元素按位与 x 的 Tag。
    static Tag and_tag(u64 x) { return {0, x}; }
    // 作用：构造按位或标记；输入：掩码 x；输出：逐元素按位或 x 的 Tag。
    static Tag or_tag(u64 x) { return {x, kMask}; }
    // 作用：构造赋值标记；输入：值 x；输出：把整段设为 x 的 Tag。
    static Tag assign(u64 x) { return {x, x}; }
    // 作用：复合按位映射 0→zero、1→one标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        zero = ((~zero & t.zero) | (zero & t.one)) & kMask;
        one = ((~one & t.zero) | (one & t.one)) & kMask;
    }
};
struct Info {
    int len = 0;
    array<int, kBits> cnt{};
    // 作用：构造空区间单位元；输入：无；输出：可参与逐位统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：0 <= x < 2^kBits 的单个值 x；输出：对应的逐位统计 Info。
    Info(u64 x) : len(1) {
        for (int i = 0; i < kBits; i++) cnt[i] = x >> i & 1;
    }
    // 作用：更新区间统计；输入：按位映射 0→zero、1→one标记 t；输出：原地更新各位 1 的个数，无返回值。
    void apply(Tag t) {
        for (int i = 0; i < kBits; i++) {
            int z = t.zero >> i & 1, o = t.one >> i & 1;
            cnt[i] = z * (len - cnt[i]) + o * cnt[i];
        }
    }
    // 作用：恢复区间和；输入：当前各位计数；输出：__int128 类型的区间元素和。
    __int128 sum() const { // kBits 较大时区间和可能超出 u64，统一用 __int128。
        __int128 ans = 0;
        for (int i = 0; i < kBits; i++) ans += (__int128)cnt[i] << i;
        return ans;
    }
    // 作用：恢复区间异或和；输入：当前各位计数；输出：所有元素的按位异或。
    u64 xr() const {
        u64 x = 0;
        for (int i = 0; i < kBits; i++)
            if (cnt[i] & 1) x |= 1ULL << i;
        return x;
    }
    // 作用：恢复区间按位与；输入：当前各位计数；输出：所有元素的按位与，空区间为 kMask。
    u64 band() const {
        u64 x = 0;
        for (int i = 0; i < kBits; i++)
            if (cnt[i] == len) x |= 1ULL << i;
        return x;
    }
    // 作用：恢复区间按位或；输入：当前各位计数；输出：所有元素的按位或，空区间为 0。
    u64 bor() const {
        u64 x = 0;
        for (int i = 0; i < kBits; i++)
            if (cnt[i]) x |= 1ULL << i;
        return x;
    }
};
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度与各位 1 的个数。
Info operator+(Info a, Info b) {
    a.len += b.len;
    for (int i = 0; i < kBits; i++) a.cnt[i] += b.cnt[i];
    return a;
}
// s.upd(l,r,Tag::xor_tag(v)); 也可 and_tag/or_tag/assign；ans.sum()/xr()/band()/bor()。
// kBits=30、n=2e5 时 cnt 数组内存较大；只需异或查询+异或修改时可简化为 xr+len。
} // namespace Bitwise

// 5. 01 串区间赋 0/1、翻转；查询 1 的个数、连续段、交替段、同值段数、逆序对。
namespace BinaryRuns {

struct Tag {
    int zero = 0, one = 1;
    // 作用：构造翻转标记；输入：无；输出：翻转 0/1 的 Tag。
    static Tag flip() { return {1, 0}; }
    // 作用：构造赋值标记；输入：x（0 或 1）；输出：把整段设为 x 的 Tag。
    static Tag assign(int x) { return {x, x}; }
    // 作用：复合01 赋值/翻转标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
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
    // 作用：构造空区间单位元；输入：无；输出：可参与01 串统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：单个值 x（0 或 1）；输出：对应的01 串统计 Info。
    Info(int x) : len(1), sum(x), first(x), last(x), blocks(1), apre(1), asuf(1), abest(1) {
        pre[x] = suf[x] = best[x] = 1;
    }
    // 作用：更新区间统计；输入：01 赋值/翻转标记 t；输出：原地更新1 的个数、同值段/交替段统计及逆序对数，无返回值。
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
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、1 的个数、同值段/交替段统计及逆序对数。
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
// s.upd(l,r,Tag::flip()); s.upd(l,r,Tag::assign(0));
// ans.best[1]/sum/abest/blocks/inv。
} // namespace BinaryRuns

// 6. 区间赋值，查询非空最大/最小子段和；这里不能直接加入区间加法标记。
namespace AssignSubarray {

struct Tag {
    bool has = false;
    i64 value = 0;
    // 作用：构造赋值标记；输入：值 x；输出：把整段设为 x 的 Tag。
    static Tag assign(i64 x) { return {true, x}; }
    // 作用：复合整段赋值标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        if (t.has) *this = t;
    }
};
struct Info {
    i64 len = 0, sum = 0, pre = LLONG_MIN, suf = LLONG_MIN, best = LLONG_MIN;
    i64 mpre = LLONG_MAX, msuf = LLONG_MAX, mbest = LLONG_MAX;
    // 作用：构造空区间单位元；输入：无；输出：可参与子段和统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：单个值 x；输出：对应的子段和统计 Info。
    Info(i64 x) : len(1), sum(x), pre(x), suf(x), best(x), mpre(x), msuf(x), mbest(x) {}
    // 作用：更新区间统计；输入：整段赋值标记 t；输出：原地更新和、非空最大/最小前后缀和与子段和，无返回值。
    void apply(Tag t) {
        if (!len || !t.has) return;
        sum = t.value * len;
        pre = suf = best = max(t.value, sum);
        mpre = msuf = mbest = min(t.value, sum);
    }
};
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、和、非空最大/最小前后缀和与子段和。
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
// s.upd(l,r,Tag::assign(v)); ans.best / .mbest；允许空子段时取 max(0LL,ans.best)。
} // namespace AssignSubarray

// 7. 等差加法：对全局下标 i 加 k*i+b；维护区间和。不需要按左右子段调整 Tag。
namespace Progression {

struct Tag {
    i64 k = 0, b = 0;
    // 作用：复合等差加法标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        k += t.k;
        b += t.b;
    }
};
struct Info {
    i64 len = 0, sum = 0, idx = 0;
    // 作用：构造空区间单位元；输入：无；输出：可参与等差加法统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：值 x 及全局下标 i；输出：对应的等差加法统计 Info。
    Info(i64 x, i64 i) : len(1), sum(x), idx(i) {}
    // 作用：更新区间统计；输入：表示对全局下标 i 加 k*i+b 的标记 t；输出：原地更新元素和 sum，无返回值。
    void apply(Tag t) { sum += t.k * idx + t.b * len; }
};
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、元素和与全局下标和。
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.idx = a.idx + b.idx;
    return c;
}
// 初始化 a.emplace_back(v[i],i)，idx 是全局下标和，不是当前区间的相对位置。
// 在 [l,r) 加首项 A、公差 D：s.upd(l,r,{D,A-D*l}); ans.sum。
// 可扩展为多项式加法：额外存 sum(i^2)、sum(i^3)...，Tag 存对应系数。
} // namespace Progression

// 8. 括号区间赋 '(' / ')'、翻转左右括号；维护含空前缀的最小/最大前缀和。
namespace Brackets {

struct Tag {
    int mul = 1, add = 0; // 只使用恒等 {1,0}、翻转 {-1,0}、赋值 {0,+/-1}。
    // 作用：构造翻转标记；输入：无；输出：交换 '(' 与 ')' 的 Tag。
    static Tag flip() { return {-1, 0}; }
    // 作用：构造赋值标记；输入：括号 c（'(' 或 ')'）；输出：把整段设为 c 的 Tag。
    static Tag assign(char c) { return {0, c == '(' ? 1 : -1}; }
    // 作用：复合括号赋值/翻转标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
    void apply(Tag t) {
        mul *= t.mul;
        add = add * t.mul + t.add;
    }
};
struct Info {
    int len = 0, sum = 0, mn = 0, mx = 0;
    // 作用：构造空区间单位元；输入：无；输出：可参与括号前缀统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：括号字符 c（'(' 或 ')'）；输出：对应的括号前缀统计 Info。
    Info(char c) : len(1), sum(c == '(' ? 1 : -1), mn(min(0, sum)), mx(max(0, sum)) {}
    // 作用：更新区间统计；输入：括号赋值/翻转标记 t；输出：原地更新总和及含空前缀的最小/最大前缀和，无返回值。
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
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度、总和及含空前缀的最小/最大前缀和。
Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.mn = min(a.mn, a.sum + b.mn);
    c.mx = max(a.mx, a.sum + b.mx);
    return c;
}
// a.emplace_back(c); s.upd(l,r,Tag::flip()); s.upd(l,r,Tag::assign('('));
// 合法括号串：ans.sum==0 && ans.mn>=0；最少补括号数：ans.sum-2*ans.mn。
} // namespace Brackets

// 9. 短版：区间逐元素异或/赋值，只查询区间异或。不查询区间和时无需逐位计数。
namespace XorOnly {

struct Tag {
    bool has = false;
    i64 set = 0, xr = 0;
    // 作用：构造异或标记；输入：异或值 x；输出：逐元素异或 x 的 Tag。
    static Tag xor_tag(i64 x) {
        Tag t;
        t.xr = x;
        return t;
    }
    // 作用：构造赋值标记；输入：值 x；输出：把整段设为 x 的 Tag。
    static Tag assign(i64 x) { return {true, x, 0}; }
    // 作用：复合逐元素异或/赋值标记；输入：后施加的标记 t；输出：原地得到先当前、后 t 的复合标记。
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
    // 作用：构造空区间单位元；输入：无；输出：可参与区间异或统计合并的空 Info。
    Info() = default;
    // 作用：构造叶子信息；输入：单个值 x；输出：对应的区间异或统计 Info。
    Info(i64 x) : len(1), xr(x) {}
    // 作用：更新区间统计；输入：逐元素异或/赋值标记 t；输出：原地更新区间异或和，无返回值。
    void apply(Tag t) {
        if (t.has) xr = (len & 1) ? t.set : 0;
        if (len & 1) xr ^= t.xr;
    }
};
// 作用：按左右顺序合并区间；输入：左区间 a、右区间 b；输出：合并后的长度与区间异或和。
Info operator+(Info a, Info b) {
    a.len += b.len;
    a.xr ^= b.xr;
    return a;
}
// s.upd(l,r,Tag::xor_tag(v)); s.upd(l,r,Tag::assign(v)); s.qry(l,r).xr。
} // namespace XorOnly

// 需要其他信息时：合并须满足结合律；apply 须与合并兼容，且 Tag 可正确复合。
// 区间 chmin/chmax + sum 通常需要 Segment Tree Beats，不能只换这里的 Tag。
// 区间取模/开方也不能直接当普通懒标记；要利用最值剪枝、下降到子节点。
// 区间逆序涉及顺序重排，此固定下标框架不能靠交换 Info 首尾完成，通常用隐式 Treap。
using Info = AddSet::Info;
using Tag = AddSet::Tag; // 换方案时两个别名一起改，例如 Affine::Info / Affine::Tag。

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    using Info = AddSet::Info;
    using Tag = AddSet::Tag;
    vector<Info> a{Info(1), Info(2), Info(3), Info(4)};
    LazySeg<Info, Tag> s(a);
    s.upd(1, 4, Tag::plus(2));       // [1,4,5,6]
    s.upd(2, 4, Tag::assign(7));     // [1,4,7,7]
    cout << s.qry(0, 4).sum << '\n'; // 输出：19
    // 作用：判断区间能否含目标；输入：区间信息 info；输出：区间非空且最大值达到示例阈值。
    auto ok = [](Info info) { return info.len && info.mx >= 7; };
    cout << s.first(0, 4, ok) << '\n'; // 输出：2
}
