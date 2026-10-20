#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 0-based, [l,r); I{} 为单位元，operator+ 满足结合律。
// 框架变量：I 为选定 Info 类型；n 是补到 2 的幂后的叶子容量，不是原数组长度。
// t[p] 是节点 p 的区间信息；t[n+i] 对应原下标 i，补齐位置为 I{}。
// 构造参数 a 是叶子信息数组；modify(p,v) 将原下标 p 的整个叶子信息替换成 v。
// query(l,r) 查询 0 下标半开区间 [l,r)，即包含 l、不包含 r，要求 0<=l<=r<=原长度。
// query 的局部 a/b 分别累计从左/右取得的信息，合并顺序始终保持原数组顺序。
// find 的 p 是节点编号，[s,e) 是节点区间；d=0 先找左边，d=1 先找右边。
// findFirst/findLast 的 f 是安全剪枝谓词，返回原数组下标；不存在时为 -1。
template<class I> struct Seg {
    int n = 1;
    vector<I> t;
    Seg(const vector<I>& a) {
        while (n < (int)a.size()) n <<= 1;
        t.resize(n * 2); copy(a.begin(), a.end(), t.begin() + n);
        for (int p = n - 1; p; p--) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    void modify(int p, I v) {
        for (t[p += n] = v; p >>= 1;) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    I query(int l, int r) {
        I a{}, b{};
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) a = a + t[l++];
            if (r & 1) b = t[--r] + b;
        }
        return a + b;
    }
    // 可选查找段：返回 [l,r) 内首/末个满足 f 的叶子下标，无解返回 -1。
    // 要求 f(区间信息)==false 时，该区间所有叶子均无解，如 mx>=k。
    template<class F> int find(int l, int r, F f, int d, int p, int s, int e) {
        if (l >= e || r <= s || !f(t[p])) return -1;
        if (e - s == 1) return s;
        int m = (s + e) / 2;
        int a = find(l, r, f, d, p * 2 + d, d ? m : s, d ? e : m);
        return a != -1 ? a : find(l, r, f, d, p * 2 + !d, d ? s : m, d ? m : e);
    }
    template<class F> int findFirst(int l, int r, F f) { return find(l, r, f, 0, 1, 0, n); }
    template<class F> int findLast(int l, int r, F f) { return find(l, r, f, 1, 1, 0, n); }
};

/* Info 菜单：抄上面的 Seg + 需要的一个 namespace（或去掉 namespace 外壳）。
 * 默认 using Info = Basic::Info；换方案时只改末尾别名，不要把多个 Info 重名粘贴。
 * 单值统计类初始化：vector<Info> a; for (ll x : v) a.emplace_back(x);
 *       Seg<Info> s(a); s.modify(p, Info(x)); auto ans = s.query(l,r);
 * Info{} 是合并单位元；统计类 Info(0) 才是值为 0 的叶子，不能用 Info{} 代替。
 * 矩阵/函数类单位元也可作为有效叶子；字符/多参数类按各块示例初始化。
 * 删除字段时同步删构造与合并。
 * 各块示例保留 namespace，可直接放进 main；若删除 namespace 外壳，
 * 将示例 using I=某方案::Info 改成 using I=Info，Tag 的别名同理。
 * 整数运算要求所有中间值不溢出；gcd/abs 要求绝对值能用 ll 表示。
 * 所有方案均为单点替换 + 区间查询；按题意改 operator+ 可维护其他可结合信息。
 * 目录：Basic 基础统计；Moments 平方/立方和；ModProduct 模积；Lcm 最小公倍数；
 * Subarray 最大/最小子段和；Top2 严格次大/次小；Runs 连续相同段；
 * Brackets 括号；Hash 正反哈希；Affine 函数复合；Matrix2 矩阵乘积；
 * Increasing 最长连续递增/递减段及子段数。
 */

// 1. 求和、最值及次数、异或、GCD、按位 AND/OR（有符号 ll 按位运算）。
namespace Basic {
/*
字段含义：
  len：区间元素个数；sum：元素和。
  mn / mx：区间最小 / 最大值；cmn / cmx：最小 / 最大值出现次数。
  xr：所有元素按位异或；gc：所有元素的非负 GCD（全 0 时为 0）。
  band / bor：所有元素按位 AND / OR。
  Info(x) 创建值为 x 的叶子；Info{} 的 len=0，表示空区间。
  空区间 sum=xr=gc=bor=0，band=-1（全 1），mn/mx 为正/负无穷哨兵。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Basic::Info;
  vector<I> a{I(6), I(2), I(6), I(4)};
  Seg<I> s(a);
  auto q = s.query(0, 4); // 查询全部，区间为 [0,4)。
  cout << q.len << ' ' << q.sum << ' ' << q.mn << ' ' << q.cmn << ' '
       << q.mx << ' ' << q.cmx << ' ' << q.xr << ' ' << q.gc << ' '
       << q.band << ' ' << q.bor << '\n'; // 输出：4 18 2 1 6 2 6 2 0 6
  s.modify(1, I(8)); // a[1]=8，数组变为 [6,8,6,4]。
  cout << s.query(0,4).sum << ' ' << s.query(0,4).mx << '\n'; // 输出：24 8
  auto f = [](I x) { return x.len && x.mx >= 6; };
  cout << s.findFirst(0,4,f) << ' ' << s.findLast(0,4,f) << '\n'; // 输出：0 2
*/
struct Info {
    int len = 0, cmn = 0, cmx = 0;
    ll sum = 0, mn = LLONG_MAX, mx = LLONG_MIN;
    ll xr = 0, gc = 0, band = -1, bor = 0;
    Info() = default;
    Info(ll x) : len(1), cmn(1), cmx(1), sum(x), mn(x), mx(x),
                 xr(x), gc(std::gcd(x, 0LL)), band(x), bor(x) {}
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c;
    c.len = a.len + b.len; c.sum = a.sum + b.sum;
    c.mn = min(a.mn, b.mn); c.mx = max(a.mx, b.mx);
    c.cmn = (a.mn == c.mn ? a.cmn : 0) + (b.mn == c.mn ? b.cmn : 0);
    c.cmx = (a.mx == c.mx ? a.cmx : 0) + (b.mx == c.mx ? b.cmx : 0);
    c.xr = a.xr ^ b.xr; c.gc = std::gcd(a.gc, b.gc);
    c.band = a.band & b.band; c.bor = a.bor | b.bor;
    return c;
}
// s.query(l,r).mx / .mn / .gc / .xr / .sum / .cmx / .cmn / .band / .bor
// 找首个 a[i]>=k：s.findFirst(l,r,[&](Info x){return x.len && x.mx>=k;});
}

// 2. 原始矩：sum=sum(x)，s2=sum(x^2)，s3=sum(x^3)；可用于均值/方差。
namespace Moments {
/*
字段含义：
  len：元素个数；sum：sum(x)；s2：sum(x*x)；s3：sum(x*x*x)。
  s2 是“各元素平方后求和”，不是 sum*sum；s3 同理。
  非空区间均值=sum/len，总体方差=s2/len-(sum/len)^2，需浮点除法。
  Info(x) 是一个元素；Info{} 的所有字段为 0，表示空区间。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Moments::Info;
  vector<I> a{I(1), I(2), I(3)};
  Seg<I> s(a);
  auto q = s.query(0,3);
  cout << q.len << ' ' << q.sum << ' ' << q.s2 << ' ' << q.s3 << '\n'; // 输出：3 6 14 36
  double mean = 1.0*q.sum/q.len;
  double variance = 1.0*q.s2/q.len - mean*mean;
  cout << mean << ' ' << variance << '\n'; // 输出：2 0.666667
  s.modify(1, I(-2)); // 数组变为 [1,-2,3]。
  q = s.query(0,3);
  cout << q.sum << ' ' << q.s2 << ' ' << q.s3 << '\n'; // 输出：2 14 20
*/
struct Info {
    ll len = 0, sum = 0, s2 = 0, s3 = 0;
    Info() = default;
    Info(ll x) : len(1), sum(x), s2(x*x), s3(x*x*x) {}
};
Info operator+(Info a, Info b) {
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum;
    c.s2=a.s2+b.s2; c.s3=a.s3+b.s3; return c;
}
// 整数幂很容易溢出；必要时字段改 __int128，或把每一步改成取模运算。
}

// 3. 模意义的区间积/和；空区间积为 1。MOD 按题改。
namespace ModProduct {
/*
字段含义：
  MOD：模数；sum：区间和取模；prod：区间积取模。
  Info(x) 会把负数也规范到 [0,MOD)；Info{} 是空区间，sum=0、prod=1。
  MOD 应按题修改；prod 不保存未经取模的真实乘积。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = ModProduct::Info;
  vector<I> a{I(2), I(3), I(4)};
  Seg<I> s(a);
  auto q = s.query(0,3);
  cout << q.sum << ' ' << q.prod << '\n'; // 输出：9 24
  s.modify(1, I(-1)); // [2,-1,4]；积为 -8，模 MOD 后是 MOD-8。
  q = s.query(0,3);
  cout << q.sum << ' ' << q.prod << '\n'; // 输出：5 998244345
*/
constexpr ll MOD = 998244353;
struct Info {
    ll sum = 0, prod = 1;
    Info() = default;
    Info(ll x) : sum((x%MOD+MOD)%MOD), prod(sum) {}
};
Info operator+(Info a, Info b) {
    Info c; c.sum=(a.sum+b.sum)%MOD; c.prod=a.prod*b.prod%MOD; return c;
}
}

// 4. LCM（同时带 GCD）；LCM 空单位元为 1，含 0 时 LCM 为 0。
namespace Lcm {
/*
字段含义：
  gc：元素绝对值的最大公约数；lc：元素绝对值的最小公倍数。
  含 0 时 lc=0；gc(0,x)=abs(x)。Info(x) 创建叶子。
  空区间 Info{} 的 gc=0、lc=1，分别是 GCD/LCM 合并的单位元。
  这里返回精确整数 LCM，要求每个维护区间的结果都能放进 ll。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Lcm::Info;
  vector<I> a{I(6), I(10), I(15)};
  Seg<I> s(a);
  auto q = s.query(0,3);
  cout << q.gc << ' ' << q.lc << '\n'; // 输出：1 30
  s.modify(1, I(0)); // 数组变为 [6,0,15]。
  q = s.query(0,3);
  cout << q.gc << ' ' << q.lc << '\n'; // 输出：3 0
*/
struct Info {
    ll gc = 0, lc = 1;
    Info() = default;
    Info(ll x) : gc(std::gcd(x, 0LL)), lc(gc) {}
};
Info operator+(Info a, Info b) {
    Info c; c.gc=std::gcd(a.gc,b.gc);
    c.lc=(!a.lc || !b.lc) ? 0 : (ll)((__int128)a.lc/std::gcd(a.lc,b.lc)*b.lc);
    return c;
}
// 前提：每个被维护区间的真实 LCM <= LLONG_MAX；超范围需大整数/专门设计。
}

// 5. 非空最大/最小子段和，及最大/最小前缀和、后缀和；合并有方向。
namespace Subarray {
/*
字段含义（以下“子段”都连续且非空）：
  len：元素个数；sum：整个区间的和。
  pre / suf：最大前缀和 / 最大后缀和；best：最大子段和。
  mpre / msuf：最小前缀和 / 最小后缀和；mbest：最小子段和。
  前缀必须从区间左端开始，后缀必须在右端结束，子段可在内部任意位置。
  pre/suf 是“和”，不是长度；合并时 a 在左、b 在右。
  Info(x) 创建叶子；空区间 len=0，最大类为负无穷、最小类为正无穷。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Subarray::Info;
  vector<I> a{I(-2), I(3), I(-1), I(4), I(-5)};
  Seg<I> s(a);
  auto q = s.query(0,5); // 最大子段 [3,-1,4]，和为 6。
  cout << q.sum << ' ' << q.pre << ' ' << q.suf << ' ' << q.best << ' '
       << q.mpre << ' ' << q.msuf << ' ' << q.mbest << '\n'; // 输出：-1 4 1 6 -2 -5 -5
  s.modify(0, I(2)); // [2,3,-1,4,-5]；最大子段 [2,3,-1,4]。
  cout << s.query(0,5).best << '\n'; // 输出：8
*/
struct Info {
    int len = 0;
    ll sum = 0, pre = LLONG_MIN, suf = LLONG_MIN, best = LLONG_MIN;
    ll mpre = LLONG_MAX, msuf = LLONG_MAX, mbest = LLONG_MAX;
    Info() = default;
    Info(ll x) : len(1), sum(x), pre(x), suf(x), best(x), mpre(x), msuf(x), mbest(x) {}
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum;
    c.pre=max(a.pre,a.sum+b.pre); c.suf=max(b.suf,b.sum+a.suf);
    c.best=max({a.best,b.best,a.suf+b.pre});
    c.mpre=min(a.mpre,a.sum+b.mpre); c.msuf=min(b.msuf,b.sum+a.msuf);
    c.mbest=min({a.mbest,b.mbest,a.msuf+b.mpre}); return c;
}
// ans.best 为非空最大子段和；允许空子段时用 max(0LL,ans.best)。
}

// 6. 最大/严格次大、最小/严格次小及各自次数；cx/cn 为 0 表示不存在。
namespace Top2 {
/*
字段含义：
  mx[0] / mx[1]：最大值 / 严格次大值；cx[0] / cx[1]：对应出现次数。
  mn[0] / mn[1]：最小值 / 严格次小值；cn[0] / cn[1]：对应出现次数。
  “严格次大”必须小于最大值，例如 [5,5,3] 的严格次大是 3，不是 5。
  cx[k] 或 cn[k] 为 0 时该排名不存在，此时对应值不能当有效结果使用。
  若要允许重复的第二大：cx[0]>=2 时为 mx[0]，否则存在时取 mx[1]。
  Info(x) 创建叶子；Info{} 的次数全为 0。pick 收集四个候选值，合并同值次数。

使用示例（放进 main()，需先复制 Seg 和本方案，pick 也要抄）：
  using I = Top2::Info;
  vector<I> a{I(5), I(5), I(3), I(1)};
  Seg<I> s(a);
  auto q = s.query(0,4);
  cout << q.mx[0] << ' ' << q.cx[0] << ' ' << q.mx[1] << ' ' << q.cx[1] << '\n'; // 输出：5 2 3 1
  cout << q.mn[0] << ' ' << q.cn[0] << ' ' << q.mn[1] << ' ' << q.cn[1] << '\n'; // 输出：1 1 3 1
  s.modify(2, I(5)); // [5,5,5,1]；严格次大变成 1。
  q = s.query(0,4);
  if (q.cx[1]) cout << q.mx[1] << ' ' << q.cx[1] << '\n'; // 输出：1 1
*/
struct Info {
    array<ll,2> mx{}, mn{};
    array<int,2> cx{}, cn{};
    Info() = default;
    Info(ll x) { mx[0]=mn[0]=x; cx[0]=cn[0]=1; }
};
void pick(array<ll,2>& v, array<int,2>& c, array<pair<ll,int>,4> a, bool desc) {
    sort(a.begin(),a.end(),[&](auto x,auto y){return desc ? x.first>y.first : x.first<y.first;});
    int k=0;
    for (auto [x,n] : a) if (n) {
        if (k && v[k-1]==x) c[k-1]+=n;
        else if (k<2) { v[k]=x; c[k++]=n; }
    }
}
Info operator+(const Info& a, const Info& b) {
    Info c;
    pick(c.mx,c.cx,{{{a.mx[0],a.cx[0]},{a.mx[1],a.cx[1]},{b.mx[0],b.cx[0]},{b.mx[1],b.cx[1]}}},true);
    pick(c.mn,c.cn,{{{a.mn[0],a.cn[0]},{a.mn[1],a.cn[1]},{b.mn[0],b.cn[0]},{b.mn[1],b.cn[1]}}},false);
    return c;
}
// mx[1] 为严格次大（cx[1]>0 才存在）；第二大允许相等时按 cx[0] 判断。
}

// 7. 最长连续相同值段；pre/suf 是同值前缀/后缀长度，blocks 是同值段数。
namespace Runs {
/*
字段含义：
  len：元素个数；first / last：区间首 / 尾元素的值。
  pre：从左端开始连续相同值的长度；suf：到右端结束连续相同值的长度。
  best：任意位置最长的连续相同值段长度；blocks：极大连续同值段数量。
  例如 [2,2,1,1,1,2] 分为 [2,2]、[1,1,1]、[2]，blocks=3、best=3。
  Info(x) 创建长度为 1 的叶子；Info{} 长度/段数为 0，首尾值不使用。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Runs::Info;
  vector<I> a{I(2), I(2), I(1), I(1), I(1), I(2)};
  Seg<I> s(a);
  auto q = s.query(0,6);
  cout << q.len << ' ' << q.first << ' ' << q.last << ' ' << q.pre << ' '
       << q.suf << ' ' << q.best << ' ' << q.blocks << '\n'; // 输出：6 2 2 2 1 3 3
  s.modify(5, I(1)); // [2,2,1,1,1,1]。
  q = s.query(0,6);
  cout << q.pre << ' ' << q.suf << ' ' << q.best << ' ' << q.blocks << '\n'; // 输出：2 4 4 2
*/
struct Info {
    int len = 0, pre = 0, suf = 0, best = 0, blocks = 0;
    ll first = 0, last = 0;
    Info() = default;
    Info(ll x) : len(1), pre(1), suf(1), best(1), blocks(1), first(x), last(x) {}
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    bool same=a.last==b.first;
    Info c; c.len=a.len+b.len; c.first=a.first; c.last=b.last;
    c.pre=a.pre+(same && a.pre==a.len ? b.pre : 0);
    c.suf=b.suf+(same && b.suf==b.len ? a.suf : 0);
    c.best=max({a.best,b.best,same ? a.suf+b.pre : 0});
    c.blocks=a.blocks+b.blocks-same; return c;
}
}

// 8. 括号：'(' 记 +1，')' 记 -1；维护含空前缀的最小/最大前缀和。
namespace Brackets {
/*
字段含义：
  len：括号个数；sum：把 '(' 记 +1、')' 记 -1 后的区间和。
  mn / mx：从当前查询区间左端开始，所有前缀和的最小 / 最大值。
  包含长度为 0 的空前缀（和为 0），所以 mn<=0、mx>=0。
  sum==0 且 mn>=0 表示合法括号串；sum-2*mn 是补成合法串的最少括号数。
  Info(c) 接收 '(' 或 ')'；Info{} 为空串，所有字段为 0。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Brackets::Info;
  string str = "())(";
  vector<I> a; for (char c : str) a.emplace_back(c);
  Seg<I> s(a);
  auto q = s.query(0,4);
  cout << q.len << ' ' << q.sum << ' ' << q.mn << ' ' << q.mx << ' '
       << (q.sum==0 && q.mn>=0) << ' ' << q.sum-2*q.mn << '\n'; // 输出：4 0 -1 1 0 2
  s.modify(2, I('(')); s.modify(3, I(')')); // 变成 "()()"。
  q = s.query(0,4);
  cout << (q.sum==0 && q.mn>=0) << '\n'; // 输出：1
*/
struct Info {
    int len = 0, sum = 0, mn = 0, mx = 0;
    Info() = default;
    Info(char c) : len(1), sum(c=='(' ? 1 : -1), mn(min(0,sum)), mx(max(0,sum)) {}
};
Info operator+(Info a, Info b) {
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum;
    c.mn=min(a.mn,a.sum+b.mn); c.mx=max(a.mx,a.sum+b.mx); return c;
}
// a.emplace_back(c); 合法括号串：ans.sum==0 && ans.mn>=0。
// 最少补括号数：ans.sum - 2*ans.mn；此处 mn 包含空前缀，保证 mn<=0。
}

// 9. 区间正反多项式哈希：pw=BASE^len，不依赖全局幂表。
namespace Hash {
/*
字段含义：
  MOD：模数；BASE：多项式底数；len：区间长度。
  fwd：从左到右的哈希 x[0]*BASE^(len-1)+...+x[len-1]，对 MOD 取模。
  rev：把区间倒过来后的同一哈希；pw：BASE^len % MOD，用于拼接。
  Info(x) 编码一个元素；Info{} 为空串，len=fwd=rev=0、pw=1。
  比较区间相等需长度相同且 fwd 相同；回文可比较 fwd 与 rev（有碰撞概率）。
  字符可用 unsigned char 编码；也能对整数数组做哈希。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Hash::Info;
  string str = "abacaba";
  vector<I> a; for (unsigned char c : str) a.emplace_back(c);
  Seg<I> s(a);
  auto q = s.query(0,7), left = s.query(0,3), right = s.query(4,7);
  cout << (q.fwd==q.rev) << ' ' << (left.len==right.len && left.fwd==right.fwd) << '\n'; // 输出：1 1
  s.modify(0, I('x')); // "xbacaba"，不再是回文。
  q = s.query(0,7);
  cout << (q.fwd==q.rev) << '\n'; // 输出：0
*/
constexpr ll MOD = 1000000007, BASE = 911382323;
struct Info {
    int len = 0;
    ll fwd = 0, rev = 0, pw = 1;
    Info() = default;
    Info(ll x) : len(1), fwd((x%MOD+MOD)%MOD), rev(fwd), pw(BASE) {}
};
Info operator+(Info a, Info b) {
    Info c; c.len=a.len+b.len; c.pw=a.pw*b.pw%MOD;
    c.fwd=(a.fwd*b.pw+b.fwd)%MOD; c.rev=(b.rev*a.pw+a.rev)%MOD; return c;
}
// 同长度区间比较 fwd；回文可判 fwd==rev。有碰撞，严格需求可复制一份做双哈希。
}

// 10. 函数复合：叶子 f(x)=mul*x+add；从左到右依次应用函数，取模。
namespace Affine {
/*
字段含义：
  MOD：模数；mul / add：整个区间复合函数 F(x)=mul*x+add 的两个系数。
  Info(m,b) 是叶子函数 f(x)=m*x+b；Info{} 是恒等函数 f(x)=x。
  eval(x)：把 x 代入当前复合函数，返回模 MOD 的结果。
  合并 a+b 表示先执行左区间函数 a，再执行右区间函数 b，即 b(a(x))。
  这组 Info 保存的是函数，不是数值区间的和；与 Lazy 的仿射 Tag 含义不同。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Affine::Info;
  vector<I> a{I(2,1), I(3,4)}; // f0(x)=2x+1，f1(x)=3x+4。
  Seg<I> s(a);
  auto q = s.query(0,2); // f1(f0(x))=6x+7。
  cout << q.mul << ' ' << q.add << ' ' << q.eval(5) << '\n'; // 输出：6 7 37
  s.modify(0, I(1,0)); // 将 f0 改成恒等函数。
  cout << s.query(0,2).eval(5) << '\n'; // 输出：19
*/
constexpr ll MOD = 998244353;
struct Info {
    ll mul = 1, add = 0;
    Info() = default;
    Info(ll m,ll b) : mul((m%MOD+MOD)%MOD), add((b%MOD+MOD)%MOD) {}
    ll eval(ll x) const { return (mul*((x%MOD+MOD)%MOD)+add)%MOD; }
};
Info operator+(Info a, Info b) { return Info(a.mul*b.mul%MOD,(a.add*b.mul+b.add)%MOD); }
// a.emplace_back(m,b); s.modify(p,Info(m,b)); s.query(l,r).eval(x) 得 f[r-1](...f[l](x))。
}

// 11. 2x2 矩阵区间乘积（模意义）；空区间为单位矩阵，方向为 A[l]*...*A[r-1]。
namespace Matrix2 {
/*
字段含义：
  MOD：矩阵元素运算的模数；a,b,c,d：矩阵 [[a,b],[c,d]] 的四个位置。
  Info(A,B,C,D) 创建一片叶子的矩阵；Info{} 是单位矩阵 [[1,0],[0,1]]。
  查询返回 A[l]*A[l+1]*...*A[r-1]，矩阵乘法有方向，不能交换顺序。
  若用于列向量转移，右侧矩阵先作用；按题目所需顺序设计叶子与合并。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Matrix2::Info;
  vector<I> a{I(1,2,3,4), I(0,1,1,0)};
  Seg<I> s(a);
  auto q = s.query(0,2); // [[1,2],[3,4]] * [[0,1],[1,0]]。
  cout << q.a << ' ' << q.b << ' ' << q.c << ' ' << q.d << '\n'; // 输出：2 1 4 3
  s.modify(0, I()); // 这里 I{} 正好也是单位矩阵，可作为有效叶子矩阵。
  q = s.query(0,2);
  cout << q.a << ' ' << q.b << ' ' << q.c << ' ' << q.d << '\n'; // 输出：0 1 1 0
*/
constexpr ll MOD = 998244353;
struct Info {
    ll a=1,b=0,c=0,d=1;
    Info() = default;
    Info(ll A,ll B,ll C,ll D) : a((A%MOD+MOD)%MOD),b((B%MOD+MOD)%MOD),
                               c((C%MOD+MOD)%MOD),d((D%MOD+MOD)%MOD) {}
};
Info operator+(Info x, Info y) {
    return Info((x.a*y.a+x.b*y.c)%MOD,(x.a*y.b+x.b*y.d)%MOD,
                (x.c*y.a+x.d*y.c)%MOD,(x.c*y.b+x.d*y.d)%MOD);
}
// a.emplace_back(A,B,C,D); 矩阵 DP / 递推转移可按题扩充维度。
}

// 12. 最长严格连续递增/递减段、对应子段数量；不是最长递增子序列 LIS。
namespace Increasing {
/*
字段含义（均指连续子段，单元素也算一段）：
  len：元素个数；first / last：首 / 尾元素值。
  upre / usuf / ubest：严格递增前缀 / 后缀 / 最长子段的长度。
  dpre / dsuf / dbest：严格递减前缀 / 后缀 / 最长子段的长度。
  ucnt / dcnt：严格递增 / 递减的非空连续子段总数，不是最长段的个数。
  Info(x) 是叶子，长度类和计数类都为 1；Info{} 是空区间，长度/计数为 0。
  例如 [1,2,3] 有 3 个单元素、2 个长度 2、1 个长度 3 的递增段，ucnt=6。

使用示例（放进 main()，需先复制 Seg 和本方案）：
  using I = Increasing::Info;
  vector<I> a{I(1), I(2), I(3), I(2), I(1)};
  Seg<I> s(a);
  auto q = s.query(0,5);
  cout << q.len << ' ' << q.first << ' ' << q.last << ' ' << q.upre << ' '
       << q.usuf << ' ' << q.ubest << ' ' << q.ucnt << ' ' << q.dpre << ' '
       << q.dsuf << ' ' << q.dbest << ' ' << q.dcnt << '\n'; // 输出：5 1 1 3 1 3 8 1 3 3 8
  s.modify(3, I(4)); // [1,2,3,4,1]。
  q = s.query(0,5);
  cout << q.ubest << ' ' << q.dbest << ' ' << q.ucnt << ' ' << q.dcnt << '\n'; // 输出：4 2 11 6
*/
struct Info {
    int len = 0, upre = 0, usuf = 0, ubest = 0, dpre = 0, dsuf = 0, dbest = 0;
    ll first = 0, last = 0, ucnt = 0, dcnt = 0;
    Info() = default;
    Info(ll x) : len(1),upre(1),usuf(1),ubest(1),dpre(1),dsuf(1),dbest(1),
                 first(x),last(x),ucnt(1),dcnt(1) {}
};
Info operator+(Info a, Info b) {
    if(!a.len) return b;
    if(!b.len) return a;
    Info c; c.len=a.len+b.len; c.first=a.first; c.last=b.last;
    bool up=a.last<b.first, down=a.last>b.first;
    c.upre=a.upre+(up && a.upre==a.len ? b.upre : 0);
    c.usuf=b.usuf+(up && b.usuf==b.len ? a.usuf : 0);
    c.ubest=max({a.ubest,b.ubest,up ? a.usuf+b.upre : 0});
    c.ucnt=a.ucnt+b.ucnt+(up ? 1LL*a.usuf*b.upre : 0);
    c.dpre=a.dpre+(down && a.dpre==a.len ? b.dpre : 0);
    c.dsuf=b.dsuf+(down && b.dsuf==b.len ? a.dsuf : 0);
    c.dbest=max({a.dbest,b.dbest,down ? a.dsuf+b.dpre : 0});
    c.dcnt=a.dcnt+b.dcnt+(down ? 1LL*a.dsuf*b.dpre : 0); return c;
}
// 非严格递增/递减时将 < / > 改成 <= / >=；单元素子段计入数量。
}

using Info = Basic::Info; // 默认基础统计；按需改为上面任意 namespace::Info。
