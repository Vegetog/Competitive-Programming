#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 0-based, [l,r); I{}/T{} 为单位元，旧标记.apply(新标记)。
// 框架变量：I/T 分别为选定 Info/Tag 类型；n 是补到 2 的幂后的叶子容量。
// t[p] 是节点 p 已应用所有修改后的区间信息；z[p] 是尚未下传给孩子的标记。
// 构造参数 a 是叶子信息数组；t[n+i] 对应原下标 i，补齐位置长度为 0。
// apply(p,v) 同时更新节点信息 t[p] 和累计标记 z[p]。
// add(l,r,v) 对 [l,r) 应用标记 v；query(l,r) 返回区间信息，要求边界不超过原长度。
// work 的 v 指向修改标记，nullptr 表示查询；p 为节点编号，[s,e) 为节点区间。
// work 的局部 a 是本次查询/修改区间对应的合并结果；m 是节点区间中点。
// find 的 d=0 先找左边，d=1 先找右边；f 是安全剪枝谓词，返回原下标或 -1。
// 所有 Tag::apply 都按“先已有旧标记，再传入新标记”复合；Info::apply 更新统计量。
template<class I, class T> struct Lazy {
    int n = 1;
    vector<I> t;
    vector<T> z;
    Lazy(const vector<I>& a) {
        while (n < (int)a.size()) n <<= 1;
        t.resize(n * 2); z.resize(n * 2);
        copy(a.begin(), a.end(), t.begin() + n);
        for (int p = n - 1; p; p--) t[p] = t[p * 2] + t[p * 2 + 1];
    }
    void apply(int p, const T& v) { t[p].apply(v); z[p].apply(v); }
    // v 非空则修改，为空则查询。
    I work(int l, int r, const T* v, int p, int s, int e) {
        if (l >= e || r <= s) return {};
        if (l <= s && e <= r) { if (v) apply(p, *v); return t[p]; }
        int m = (s + e) / 2;
        apply(p * 2, z[p]); apply(p * 2 + 1, z[p]); z[p] = {};
        I a = work(l, r, v, p * 2, s, m) + work(l, r, v, p * 2 + 1, m, e);
        if (v) t[p] = t[p * 2] + t[p * 2 + 1];
        return a;
    }
    void add(int l, int r, T v) { work(l, r, &v, 1, 0, n); }
    I query(int l, int r) { return work(l, r, nullptr, 1, 0, n); }
    // 可选查找段：返回 [l,r) 内首/末个满足 f 的叶子下标，无解返回 -1。
    // 要求 f(区间信息)==false 时，该区间所有叶子均无解，如 mx>=k。
    template<class F> int find(int l, int r, F f, int d, int p, int s, int e) {
        if (l >= e || r <= s || !f(t[p])) return -1;
        if (e - s == 1) return s;
        int m = (s + e) / 2;
        apply(p * 2, z[p]); apply(p * 2 + 1, z[p]); z[p] = {};
        int a = find(l, r, f, d, p * 2 + d, d ? m : s, d ? e : m);
        return a != -1 ? a : find(l, r, f, d, p * 2 + !d, d ? s : m, d ? m : e);
    }
    template<class F> int findFirst(int l, int r, F f) { return find(l, r, f, 0, 1, 0, n); }
    template<class F> int findLast(int l, int r, F f) { return find(l, r, f, 1, 1, 0, n); }
};

/* Info + Tag 菜单：抄上面的 Lazy + 需要的一个 namespace（或去掉 namespace 外壳）。
 * 默认用 AddSet；换方案时改末尾两个别名。每一块都是完整且相互配套的组合。
 * 单值统计类初始化：vector<Info> a; for (ll x : v) a.emplace_back(x);
 *       Lazy<Info,Tag> s(a); s.add(l,r,tag); auto ans=s.query(l,r);
 * Info{} 是空区间，不能用它初始化有效元素；单值数值类用 Info(0) 建立 0 叶子。
 * Progression 要传 (值,下标)，Brackets 要传括号字符，详见各块示例。
 * 空叶子长度为 0，不受修改影响。
 * s.add 的含义是“区间应用 Tag”，也可做赋值、乘法、翻转，不限于数值加法。
 * 旧标记.apply(新标记)：先旧后新；不能颠倒，尤其是乘法/赋值。
 * 各块示例保留 namespace，可直接放进 main；若删除 namespace 外壳，
 * 将示例 using I=某方案::Info 改成 using I=Info，Tag 的别名同理。
 * 整数运算要求所有中间值不溢出；gcd/abs/相邻差要求绝对值能用 ll 表示。
 * 目录：AddSet 加/赋值+最值；Affine 加/乘/赋值+平方和/GCD；ModAffine 模仿射；
 * Bitwise AND/OR/XOR/赋值；BinaryRuns 01 赋值/翻转+连续段；
 * AssignSubarray 赋值+最大子段和；Progression 等差数列加法；Brackets 括号赋值/翻转；
 * XorOnly 仅维护区间异或的短版。
 * 不要直接给异或/GCD等字段套 sum 的加法公式；不支持的组合要另设计信息。
 */

// 1. 常用短版：区间加/赋值，查询和、最值及次数。set 标志避免用数值当哨兵。
namespace AddSet {
/*
Tag 字段含义：
  has：是否带赋值操作；set：赋值目标；add：赋值后再加的数。
  has=false 时只做 x+=add；has=true 时做 x=set+add。
  Tag{} 是恒等操作；plus(v) 只加 v；assign(v) 只赋成 v。
  旧 Tag.apply(新 Tag) 表示先旧后新，新赋值会覆盖之前的赋值和加法。
Info 字段含义：
  len：元素个数；sum：元素和；mn / mx：最小 / 最大值。
  cmn / cmx：最小 / 最大值的出现次数。
  Info(x) 是值为 x 的叶子；Info{} 的 len=0，其最值哨兵不作有效查询结果。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = AddSet::Info; using T = AddSet::Tag;
  vector<I> a{I(1), I(2), I(3), I(4)};
  Lazy<I,T> s(a);
  s.add(1,4,T::plus(2));   // [1,4,5,6]。
  s.add(2,4,T::assign(7)); // [1,4,7,7]。
  s.add(3,4,T::plus(-1));  // [1,4,7,6]，先赋值再加。
  auto q = s.query(0,4);
  cout << q.len << ' ' << q.sum << ' ' << q.mn << ' ' << q.mx << ' '
       << q.cmn << ' ' << q.cmx << '\n'; // 输出：4 18 1 7 1 1
  auto f = [](I x) { return x.len && x.mx>=6; };
  cout << s.findFirst(0,4,f) << ' ' << s.findLast(0,4,f) << '\n'; // 输出：2 3
*/
struct Tag {
    bool has = false;
    ll set = 0, add = 0;
    static Tag plus(ll x) { Tag t; t.add=x; return t; }
    static Tag assign(ll x) { Tag t; t.has=true; t.set=x; return t; }
    void apply(Tag t) { if (t.has) *this=t; else add+=t.add; }
};
struct Info {
    ll len = 0, sum = 0, mn = LLONG_MAX, mx = LLONG_MIN, cmn = 0, cmx = 0;
    Info() = default;
    Info(ll x) : len(1), sum(x), mn(x), mx(x), cmn(1), cmx(1) {}
    void apply(Tag t) {
        if (!len) return;
        if (t.has) { sum=t.set*len; mn=mx=t.set; cmn=cmx=len; }
        sum+=t.add*len; mn+=t.add; mx+=t.add;
    }
};
Info operator+(Info a, Info b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum;
    c.mn=min(a.mn,b.mn); c.mx=max(a.mx,b.mx);
    c.cmn=(a.mn==c.mn ? a.cmn : 0)+(b.mn==c.mn ? b.cmn : 0);
    c.cmx=(a.mx==c.mx ? a.cmx : 0)+(b.mx==c.mx ? b.cmx : 0); return c;
}
// s.add(l,r,Tag::plus(v)); s.add(l,r,Tag::assign(v)); s.query(l,r).sum / .mn / .mx
}

// 2. 完整整数仿射：x -> mul*x+add（加、乘、赋值），查询和/平方和/最值/GCD。
// GCD 借助首尾值 + 相邻差 GCD：gc=gcd(first,gd)，加法只改变 first，差不变。
namespace Affine {
/*
Tag 字段含义：
  mul / add：逐元素执行 x=mul*x+add；Tag{}={1,0} 为恒等操作。
  {1,v} 加 v；{v,0} 乘 v；{0,v} 赋值 v；允许负乘数。
  复合顺序先旧后新：(m*x+b) 再应用 (M*x+B)，结果为 M*m*x+M*b+B。
Info 字段含义：
  len：元素个数；sum：元素和；s2：各元素平方和（不是 sum*sum）。
  mn / mx：最小 / 最大值；cmn / cmx：各自出现次数。
  first / last：当前区间首 / 尾元素值，用于合并相邻区间的跨界差。
  gd：区间内部所有相邻差的非负 GCD；单元素/全相等区间的 gd=0。
  gc：区间元素的非负 GCD，等于 gcd(first,gd)；整个区间加 v 时差不变。
  Info(x) 是叶子；Info{} 是 len=0 的空区间，首尾值不使用。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = Affine::Info; using T = Affine::Tag;
  vector<I> a{I(2), I(4), I(6)};
  Lazy<I,T> s(a);
  s.add(0,3,T{1,2});  // [4,6,8]，全部加 2。
  s.add(1,3,T{-1,0}); // [4,-6,-8]，后两个乘 -1。
  auto q = s.query(0,3);
  cout << q.len << ' ' << q.sum << ' ' << q.s2 << ' ' << q.mn << ' ' << q.cmn << ' '
       << q.mx << ' ' << q.cmx << ' ' << q.first << ' ' << q.last << ' '
       << q.gd << ' ' << q.gc << '\n'; // 输出：3 -10 116 -8 1 4 1 4 -8 2 2
  s.add(0,2,T{0,3}); // [3,3,-8]，前两个赋值 3。
  q = s.query(0,3);
  cout << q.sum << ' ' << q.s2 << ' ' << q.gc << ' ' << q.gd << ' '
       << q.mx << ' ' << q.cmx << '\n'; // 输出：-2 82 1 11 3 2
*/
struct Tag {
    ll mul = 1, add = 0;
    void apply(Tag t) { mul*=t.mul; add=add*t.mul+t.add; }
};
struct Info {
    ll len = 0, sum = 0, s2 = 0, mn = LLONG_MAX, mx = LLONG_MIN, cmn = 0, cmx = 0;
    ll first = 0, last = 0, gd = 0, gc = 0;
    Info() = default;
    Info(ll x) : len(1), sum(x), s2(x*x), mn(x), mx(x), cmn(1), cmx(1),
                 first(x), last(x), gc(std::gcd(x,0LL)) {}
    void apply(Tag t) {
        if (!len) return;
        s2=t.mul*t.mul*s2+2*t.mul*t.add*sum+t.add*t.add*len;
        sum=t.mul*sum+t.add*len; // 必须在 s2 后更新，s2 用旧 sum。
        if (t.mul>=0) { mn=mn*t.mul+t.add; mx=mx*t.mul+t.add; }
        else { ll v=mn; mn=mx*t.mul+t.add; mx=v*t.mul+t.add; swap(cmn,cmx); }
        if (!t.mul) cmn=cmx=len;
        first=first*t.mul+t.add; last=last*t.mul+t.add;
        gd*=std::gcd(t.mul,0LL); gc=std::gcd(first,gd);
    }
};
Info operator+(Info a, Info b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum; c.s2=a.s2+b.s2;
    c.mn=min(a.mn,b.mn); c.mx=max(a.mx,b.mx);
    c.cmn=(a.mn==c.mn ? a.cmn : 0)+(b.mn==c.mn ? b.cmn : 0);
    c.cmx=(a.mx==c.mx ? a.cmx : 0)+(b.mx==c.mx ? b.cmx : 0);
    c.first=a.first; c.last=b.last;
    c.gd=std::gcd(std::gcd(a.gd,b.gd),b.first-a.last); c.gc=std::gcd(c.first,c.gd);
    return c;
}
// 加 v：{1,v}；乘 v：{v,0}；赋值 v：{0,v}。乘负数会交换最小/最大及次数。
// s.add(l,r,{1,v}); s.query(l,r).gc / .s2 / .sum / .mn / .mx
// 不需要平方和/GCD时删对应字段及构造、合并、apply，省抄写和溢出风险。
}

// 3. 模仿射：区间加/乘/赋值，维护 sum 和平方和；模运算下不维护大小/GCD。
namespace ModAffine {
/*
公共变量 / 函数：
  MOD：模数；norm(x)：把整数规范到 [0,MOD)。
Tag 字段含义：
  mul / add：逐元素做 x=(mul*x+add)%MOD；Tag(m,b) 会规范两个系数。
  Tag{} 是恒等；Tag(1,v) 加 v，Tag(v,0) 乘 v，Tag(0,v) 赋值 v。
Info 字段含义：
  len：实际元素个数，不是模意义的长度；sum：元素和取模；s2：平方和取模。
  Info(x) 规范叶子值；Info{} 的所有字段为 0，表示空区间。

使用示例（放进 main()，需先复制 Lazy 和本方案，norm 也要抄）：
  using I = ModAffine::Info; using T = ModAffine::Tag;
  vector<I> a{I(1), I(2), I(3)};
  Lazy<I,T> s(a);
  s.add(0,3,T(1,2)); // [3,4,5]。
  s.add(1,3,T(3,0)); // [3,12,15]。
  s.add(0,1,T(0,ModAffine::MOD+1)); // [1,12,15]，赋值后按模数规范。
  auto q = s.query(0,3);
  cout << q.len << ' ' << q.sum << ' ' << q.s2 << '\n'; // 输出：3 28 370
  q = s.query(1,3);
  cout << q.sum << ' ' << q.s2 << '\n'; // 输出：27 369
*/
constexpr ll MOD = 998244353;
ll norm(ll x) { return (x%MOD+MOD)%MOD; }
struct Tag {
    ll mul = 1, add = 0;
    Tag() = default;
    Tag(ll m,ll b) : mul(norm(m)),add(norm(b)) {}
    void apply(Tag t) { mul=mul*t.mul%MOD; add=(add*t.mul+t.add)%MOD; }
};
struct Info {
    ll len = 0, sum = 0, s2 = 0;
    Info() = default;
    Info(ll x) : len(1),sum(norm(x)),s2(sum*sum%MOD) {}
    void apply(Tag t) {
        s2=(t.mul*t.mul%MOD*s2%MOD+2*t.mul*t.add%MOD*sum%MOD+t.add*t.add%MOD*(len%MOD)%MOD)%MOD;
        sum=(sum*t.mul+t.add*(len%MOD))%MOD;
    }
};
Info operator+(Info a, Info b) {
    Info c; c.len=a.len+b.len; c.sum=(a.sum+b.sum)%MOD; c.s2=(a.s2+b.s2)%MOD; return c;
}
// s.add(l,r,Tag(1,v)); Tag(v,0) 乘 v；Tag(0,v) 赋值 v。
// MOD 默认约 1e9，修改得很大时乘法须使用 __int128。
}

// 4. 位运算：区间 AND/OR/XOR/赋值；逐位维护 1 的个数，查询和/异或/AND/OR。
// B 按题改（1<=B<=63），值/掩码必须是非负且小于 2^B。每次操作 O(B log n)。
namespace Bitwise {
/*
公共变量：
  ull：无符号 64 位整数；B：维护的二进制位数；MASK：低 B 位全 1 的掩码。
  位下标 i 从最低位 0 开始；所有值/掩码要求在 [0,2^B) 内。
Tag 字段含义：
  zero / one：两个 B 位掩码；原位为 0 / 1 时，分别变成对应掩码的这一位。
  对每一位 (zero_i,one_i)：(0,1) 不变，(1,0) 翻转，(0,0)/(1,1) 赋 0/1。
  Tag{} 不改变元素；Xor/And/Or/assign 分别创建逐元素异或/与/或/赋值操作。
Info 字段含义：
  len：元素个数；cnt[i]：区间中二进制第 i 位为 1 的元素个数。
  sum()：元素和，返回 __int128；xr()/band()/bor()：区间 XOR/AND/OR。
  这些是查询方法，调用时带括号；这里未维护最大值或最小值。
  Info(x) 是叶子；Info{} 长度/计数为 0，空区间 AND 为 MASK，其他结果为 0。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = Bitwise::Info; using T = Bitwise::Tag;
  vector<I> a{I(1), I(2), I(3)};
  Lazy<I,T> s(a);
  s.add(0,2,T::Xor(3)); // [2,1,3]。
  s.add(1,3,T::Or(4));  // [2,5,7]。
  s.add(0,3,T::And(6)); // [2,4,6]。
  auto q = s.query(0,3);
  // 本例和很小可转 ll 输出；真实题目若超过 ll，需使用 __int128 输出函数。
  cout << q.len << ' ' << (ll)q.sum() << ' ' << q.xr() << ' ' << q.band() << ' '
       << q.bor() << ' ' << q.cnt[0] << ' ' << q.cnt[1] << ' ' << q.cnt[2] << '\n'; // 输出：3 12 0 0 6 0 2 2
  s.add(1,3,T::assign(1)); // [2,1,1]。
  q = s.query(0,3);
  cout << (ll)q.sum() << ' ' << q.xr() << ' ' << q.band() << ' ' << q.bor() << '\n'; // 输出：4 2 0 3
*/
using ull = unsigned long long;
constexpr int B = 30;
constexpr ull MASK = (1ULL<<B)-1;
struct Tag {
    ull zero = 0, one = MASK; // 原位 0 -> zero 的该位，原位 1 -> one 的该位。
    static Tag Xor(ull x) { return {x,MASK^x}; }
    static Tag And(ull x) { return {0,x}; }
    static Tag Or(ull x) { return {x,MASK}; }
    static Tag assign(ull x) { return {x,x}; }
    void apply(Tag t) {
        zero=((~zero&t.zero)|(zero&t.one))&MASK;
        one=((~one&t.zero)|(one&t.one))&MASK;
    }
};
struct Info {
    int len = 0;
    array<int,B> cnt{};
    Info() = default;
    Info(ull x) : len(1) { for (int i=0;i<B;i++) cnt[i]=x>>i&1; }
    void apply(Tag t) {
        for (int i=0;i<B;i++) {
            int z=t.zero>>i&1, o=t.one>>i&1;
            cnt[i]=z*(len-cnt[i])+o*cnt[i];
        }
    }
    __int128 sum() const { // B 较大时区间和可能超出 ull，统一用 __int128。
        __int128 ans=0; for(int i=0;i<B;i++) ans+=(__int128)cnt[i]<<i; return ans;
    }
    ull xr() const { ull x=0; for(int i=0;i<B;i++) if(cnt[i]&1) x|=1ULL<<i; return x; }
    ull band() const { ull x=0; for(int i=0;i<B;i++) if(cnt[i]==len) x|=1ULL<<i; return x; }
    ull bor() const { ull x=0; for(int i=0;i<B;i++) if(cnt[i]) x|=1ULL<<i; return x; }
};
Info operator+(Info a, Info b) {
    a.len+=b.len; for(int i=0;i<B;i++) a.cnt[i]+=b.cnt[i]; return a;
}
// s.add(l,r,Tag::Xor(v)); 也可 And/Or/assign；ans.sum()/xr()/band()/bor()。
// B=30、n=2e5 时 cnt 数组内存较大；只需异或查询+异或修改时可简化为 xr+len。
}

// 5. 01 串区间赋 0/1、翻转；查询 1 的个数、连续段、交替段、同值段数、逆序对。
namespace BinaryRuns {
/*
Tag 字段含义：
  zero / one：原来为 0 / 1 的元素分别变成什么（只能是 0 或 1）。
  Tag{}={0,1} 不变；flip()={1,0} 翻转；assign(x)={x,x} 全赋成 x。
Info 字段含义：
  len：元素个数；sum：1 的个数，0 的个数为 len-sum；first / last：首 / 尾 01 值。
  pre[x] / suf[x] / best[x]：连续 x 的前缀 / 后缀 / 最长段长度，x 取 0 或 1。
  apre / asuf / abest：相邻元素不同的交替前缀 / 后缀 / 最长段长度。
  blocks：极大连续同值段数；inv：逆序对数，即 i<j 且 a[i]=1、a[j]=0 的对数。
  Info(x) 只接受整数 0/1；字符 '0'/'1' 应先减去 '0'。
  Info{} 是空区间，长度/计数全为 0，首尾值不使用。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = BinaryRuns::Info; using T = BinaryRuns::Tag;
  string str = "11001";
  vector<I> a; for(char c : str) a.emplace_back(c-'0');
  Lazy<I,T> s(a);
  auto q = s.query(0,5);
  cout << q.len << ' ' << q.sum << ' ' << q.best[0] << ' ' << q.best[1] << ' '
       << q.abest << ' ' << q.blocks << ' ' << q.inv << '\n'; // 输出：5 3 2 2 2 3 4
  s.add(1,4,T::flip()); // 变成 "10111"。
  q = s.query(0,5);
  cout << q.sum << ' ' << q.best[1] << ' ' << q.apre << ' ' << q.asuf << ' '
       << q.abest << ' ' << q.inv << '\n'; // 输出：4 3 3 1 3 1
  s.add(0,2,T::assign(0)); // 变成 "00111"。
  q = s.query(0,5);
  cout << q.pre[0] << ' ' << q.suf[1] << ' ' << q.blocks << ' ' << q.inv << '\n'; // 输出：2 3 2 0
*/
struct Tag {
    int zero = 0, one = 1;
    static Tag flip() { return {1,0}; }
    static Tag assign(int x) { return {x,x}; }
    void apply(Tag t) { zero=zero ? t.one : t.zero; one=one ? t.one : t.zero; }
};
struct Info {
    int len = 0, sum = 0, first = 0, last = 0, blocks = 0;
    ll inv = 0; // 01 逆序对：前面的 1 与后面的 0。
    array<int,2> pre{}, suf{}, best{};
    int apre = 0, asuf = 0, abest = 0;
    Info() = default;
    Info(int x) : len(1),sum(x),first(x),last(x),blocks(1),apre(1),asuf(1),abest(1) {
        pre[x]=suf[x]=best[x]=1;
    }
    void apply(Tag t) {
        if (!len) return;
        if (t.zero==t.one) {
            int x=t.zero; sum=x*len; first=last=x; blocks=1; inv=0;
            pre=suf=best={0,0}; pre[x]=suf[x]=best[x]=len;
            apre=asuf=abest=1;
        } else if (t.zero==1) {
            inv=1LL*sum*(len-sum)-inv;
            sum=len-sum; first^=1; last^=1;
            swap(pre[0],pre[1]); swap(suf[0],suf[1]); swap(best[0],best[1]);
        }
    }
};
Info operator+(const Info& a, const Info& b) {
    if (!a.len) return b;
    if (!b.len) return a;
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum; c.first=a.first; c.last=b.last;
    c.inv=a.inv+b.inv+1LL*a.sum*(b.len-b.sum);
    c.blocks=a.blocks+b.blocks-(a.last==b.first);
    for(int x=0;x<2;x++) {
        c.pre[x]=a.pre[x]+(a.pre[x]==a.len ? b.pre[x] : 0);
        c.suf[x]=b.suf[x]+(b.suf[x]==b.len ? a.suf[x] : 0);
        c.best[x]=max({a.best[x],b.best[x],a.suf[x]+b.pre[x]});
    }
    bool alt=a.last!=b.first;
    c.apre=a.apre+(alt && a.apre==a.len ? b.apre : 0);
    c.asuf=b.asuf+(alt && b.asuf==b.len ? a.asuf : 0);
    c.abest=max({a.abest,b.abest,alt ? a.asuf+b.apre : 0}); return c;
}
// s.add(l,r,Tag::flip()); s.add(l,r,Tag::assign(0)); ans.best[1]/sum/abest/blocks/inv。
}

// 6. 区间赋值，查询非空最大/最小子段和；这里不能直接加入区间加法标记。
namespace AssignSubarray {
/*
Tag 字段含义：
  has：是否赋值；value：赋值目标；assign(v) 创建赋值标记。
  Tag{} 不操作；旧标记.apply(新标记) 中，新赋值覆盖旧赋值。
Info 字段含义（子段连续且非空）：
  len：元素个数；sum：整个区间的和。
  pre / suf / best：最大前缀和 / 最大后缀和 / 最大子段和。
  mpre / msuf / mbest：最小前缀和 / 最小后缀和 / 最小子段和。
  前缀起点固定在左端，后缀终点固定在右端；上述字段保存和，不保存长度。
  Info(x) 为叶子；Info{} 的 len=0，最大类为负无穷、最小类为正无穷。
  全部赋成负数 v 后，最大非空子段只取一个元素，best=v。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = AssignSubarray::Info; using T = AssignSubarray::Tag;
  vector<I> a{I(-2), I(3), I(-1), I(4), I(-5)};
  Lazy<I,T> s(a);
  s.add(1,4,T::assign(2)); // [-2,2,2,2,-5]。
  auto q = s.query(0,5);
  cout << q.sum << ' ' << q.pre << ' ' << q.suf << ' ' << q.best << ' '
       << q.mpre << ' ' << q.msuf << ' ' << q.mbest << '\n'; // 输出：-1 4 1 6 -2 -5 -5
  s.add(0,5,T::assign(-3)); // [-3,-3,-3,-3,-3]。
  q = s.query(0,5);
  cout << q.sum << ' ' << q.best << ' ' << q.mbest << '\n'; // 输出：-15 -3 -15
*/
struct Tag {
    bool has = false;
    ll value = 0;
    static Tag assign(ll x) { return {true,x}; }
    void apply(Tag t) { if(t.has) *this=t; }
};
struct Info {
    ll len = 0, sum = 0, pre = LLONG_MIN, suf = LLONG_MIN, best = LLONG_MIN;
    ll mpre = LLONG_MAX, msuf = LLONG_MAX, mbest = LLONG_MAX;
    Info() = default;
    Info(ll x) : len(1),sum(x),pre(x),suf(x),best(x),mpre(x),msuf(x),mbest(x) {}
    void apply(Tag t) {
        if(!len || !t.has) return;
        sum=t.value*len; pre=suf=best=max(t.value,sum); mpre=msuf=mbest=min(t.value,sum);
    }
};
Info operator+(Info a, Info b) {
    if(!a.len) return b;
    if(!b.len) return a;
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum;
    c.pre=max(a.pre,a.sum+b.pre); c.suf=max(b.suf,b.sum+a.suf);
    c.best=max({a.best,b.best,a.suf+b.pre});
    c.mpre=min(a.mpre,a.sum+b.mpre); c.msuf=min(b.msuf,b.sum+a.msuf);
    c.mbest=min({a.mbest,b.mbest,a.msuf+b.mpre}); return c;
}
// s.add(l,r,Tag::assign(v)); ans.best / .mbest；允许空子段时取 max(0LL,ans.best)。
}

// 7. 等差加法：对全局下标 i 加 k*i+b；维护区间和。不需要按左右子段调整 Tag。
namespace Progression {
/*
Tag 字段含义：
  k / b：对全局下标 i 的元素加 k*i+b；Tag{}={0,0} 不操作。
  在 [l,r) 加首项 A、公差 D 的数列，即对 i 加 A+D*(i-l)，对应 {D,A-D*l}。
  标记中没有保存 l；换成全局下标表达式后，下传到左右子树无需修改标记。
Info 字段含义：
  len：元素个数；sum：元素和；idx：区间所有全局下标之和，不随元素修改变化。
  Info(x,i)：下标 i 处值为 x 的叶子；必须传两个参数，不能只传 x。
  Info{} 为空区间，全部为 0；整段变化量为 k*idx+b*len。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = Progression::Info; using T = Progression::Tag;
  vector<ll> v(5,0);
  vector<I> a; for(int i=0;i<(int)v.size();i++) a.emplace_back(v[i],i);
  Lazy<I,T> s(a);
  ll l=1, r=5, A=3, D=2;
  s.add(l,r,T{D,A-D*l}); // 加 [3,5,7,9]，数组变成 [0,3,5,7,9]。
  auto q = s.query(0,5);
  cout << q.len << ' ' << q.sum << ' ' << q.idx << '\n'; // 输出：5 24 10
  q = s.query(2,4); // 下标 2+3=5，值 5+7=12。
  cout << q.len << ' ' << q.sum << ' ' << q.idx << '\n'; // 输出：2 12 5
  l=0; r=3; A=2; D=1;
  s.add(l,r,T{D,A-D*l}); // 再加 [2,3,4]，数组变成 [2,6,9,7,9]。
  cout << s.query(0,5).sum << '\n'; // 输出：33
*/
struct Tag {
    ll k = 0, b = 0;
    void apply(Tag t) { k+=t.k; b+=t.b; }
};
struct Info {
    ll len = 0, sum = 0, idx = 0;
    Info() = default;
    Info(ll x,ll i) : len(1),sum(x),idx(i) {}
    void apply(Tag t) { sum+=t.k*idx+t.b*len; }
};
Info operator+(Info a, Info b) {
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum; c.idx=a.idx+b.idx; return c;
}
// 初始化 a.emplace_back(v[i],i)，idx 是全局下标和，不是当前区间的相对位置。
// 在 [l,r) 加首项 A、公差 D：s.add(l,r,{D,A-D*l}); ans.sum。
// 可扩展为多项式加法：额外存 sum(i^2)、sum(i^3)...，Tag 存对应系数。
}

// 8. 括号区间赋 '(' / ')'、翻转左右括号；维护含空前缀的最小/最大前缀和。
namespace Brackets {
/*
Tag 字段含义：
  mul / add：对 +/-1 括号编码的变换 x=mul*x+add。
  只允许恒等 {1,0}、翻转 {-1,0}、赋 '(' 的 {0,1}、赋 ')' 的 {0,-1}。
  flip() 翻转左右括号；assign(c) 全赋成 c；不要使用任意数值加法标记。
Info 字段含义：
  len：括号个数；sum：'('=+1、')'=-1 后的区间和。
  mn / mx：从查询区间左端开始的最小 / 最大前缀和，包含和为 0 的空前缀。
  sum==0 且 mn>=0 为合法串；sum-2*mn 是补成合法串的最少括号数。
  Info(c) 接受 '(' 或 ')'；Info{} 为空串，全部为 0。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = Brackets::Info; using T = Brackets::Tag;
  string str = "(()())";
  vector<I> a; for(char c : str) a.emplace_back(c);
  Lazy<I,T> s(a);
  auto q = s.query(0,6);
  cout << q.len << ' ' << q.sum << ' ' << q.mn << ' ' << q.mx << ' '
       << (q.sum==0 && q.mn>=0) << '\n'; // 输出：6 0 0 2 1
  s.add(1,5,T::flip()); // 变成 "()()()"。
  q = s.query(0,6);
  cout << q.mx << ' ' << (q.sum==0 && q.mn>=0) << '\n'; // 输出：1 1
  s.add(0,3,T::assign('(')); // 变成 "((()()"。
  q = s.query(0,6);
  cout << q.sum << ' ' << q.mn << ' ' << q.mx << ' ' << q.sum-2*q.mn << '\n'; // 输出：2 0 3 2
*/
struct Tag {
    int mul = 1, add = 0; // 只使用恒等 {1,0}、翻转 {-1,0}、赋值 {0,+/-1}。
    static Tag flip() { return {-1,0}; }
    static Tag assign(char c) { return {0,c=='(' ? 1 : -1}; }
    void apply(Tag t) { mul*=t.mul; add=add*t.mul+t.add; }
};
struct Info {
    int len = 0, sum = 0, mn = 0, mx = 0;
    Info() = default;
    Info(char c) : len(1),sum(c=='(' ? 1 : -1),mn(min(0,sum)),mx(max(0,sum)) {}
    void apply(Tag t) {
        if(!len) return;
        if(!t.mul) { sum=t.add*len; mn=min(0,sum); mx=max(0,sum); }
        else if(t.mul==-1) { sum=-sum; int old=mn; mn=-mx; mx=-old; }
    }
};
Info operator+(Info a, Info b) {
    Info c; c.len=a.len+b.len; c.sum=a.sum+b.sum;
    c.mn=min(a.mn,a.sum+b.mn); c.mx=max(a.mx,a.sum+b.mx); return c;
}
// a.emplace_back(c); s.add(l,r,Tag::flip()); s.add(l,r,Tag::assign('('));
// 合法括号串：ans.sum==0 && ans.mn>=0；最少补括号数：ans.sum-2*ans.mn。
}

// 9. 短版：区间逐元素异或/赋值，只查询区间异或。不查询区间和时无需逐位计数。
namespace XorOnly {
/*
Tag 字段含义：
  has：是否赋值；set：赋值目标；xr：赋值后再异或的数。
  has=false 时 x^=xr；has=true 时 x=set^xr。
  Xor(v) 只异或 v；assign(v) 全赋成 v；Tag{} 为恒等操作。
Info 字段含义：
  len：元素个数；xr：区间所有元素的异或值。
  对整段异或 v 时，长度为偶数则 xr 不变，奇数则 xr^=v。
  Info(x) 创建叶子；Info{} 为空区间，len=xr=0。
  Tag.xr 是修改量，Info.xr 是查询结果，两者含义不同。

使用示例（放进 main()，需先复制 Lazy 和本方案）：
  using I = XorOnly::Info; using T = XorOnly::Tag;
  vector<I> a{I(1), I(2), I(3), I(4)};
  Lazy<I,T> s(a);
  s.add(0,4,T::Xor(5)); // [4,7,6,1]；长度 4，整段异或仍为原来的 4。
  cout << s.query(0,4).xr << ' ' << s.query(0,3).xr << '\n'; // 输出：4 5
  s.add(1,4,T::assign(2)); // [4,2,2,2]。
  cout << s.query(0,4).len << ' ' << s.query(0,4).xr << '\n'; // 输出：4 6
  s.add(1,4,T::Xor(3)); // [4,1,1,1]。
  cout << s.query(0,4).xr << '\n'; // 输出：5
*/
struct Tag {
    bool has = false;
    ll set = 0, xr = 0;
    static Tag Xor(ll x) { Tag t; t.xr=x; return t; }
    static Tag assign(ll x) { return {true,x,0}; }
    void apply(Tag t) { if(t.has) *this=t; else xr^=t.xr; }
};
struct Info {
    int len = 0;
    ll xr = 0;
    Info() = default;
    Info(ll x) : len(1),xr(x) {}
    void apply(Tag t) {
        if(t.has) xr=(len&1) ? t.set : 0;
        if(len&1) xr^=t.xr;
    }
};
Info operator+(Info a, Info b) { a.len+=b.len; a.xr^=b.xr; return a; }
// s.add(l,r,Tag::Xor(v)); s.add(l,r,Tag::assign(v)); s.query(l,r).xr。
}

// 需要其他信息时：合并须满足结合律；apply 须与合并兼容，且 Tag 可正确复合。
// 区间 chmin/chmax + sum 通常需要 Segment Tree Beats，不能只换这里的 Tag。
// 区间取模/开方也不能直接当普通懒标记；要利用最值剪枝、下降到子节点。
// 区间逆序涉及顺序重排，此固定下标框架不能靠交换 Info 首尾完成，通常用隐式 Treap。
using Info = AddSet::Info;
using Tag = AddSet::Tag; // 换方案时两个别名一起改，例如 Affine::Info / Affine::Tag。
