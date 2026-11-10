/*
算法：线段树（区间加、区间和）
简介：使用加法懒标记，将整段修改推迟到访问子区间时处理。
复杂度：时间：建树 O(n)，单点/区间修改及查询 O(log n)；空间：O(n)。
约定：下标从 0 开始；区间为 [l,r)，允许空数组/空区间；中间乘积及和须在 i64 范围内。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct LazySeg {
    int n;
    vector<i64> t, tag;
    // 作用：建立区间加线段树；输入：数组 a；输出：维护区间和及零加法标记的 LazySeg。
    explicit LazySeg(const vector<i64>& a) : n(a.size()), t(4 * n + 4), tag(4 * n + 4) {
        if (n) build(1, 0, n, a);
    }
    // 作用：递归建树；输入：节点 p、对应区间 [l,r)、原数组 a；输出：填充该子树的区间和。
    void build(int p, int l, int r, const vector<i64>& a) {
        if (r - l == 1) {
            t[p] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(p * 2, l, mid, a);
        build(p * 2 + 1, mid, r, a);
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
    // 作用：对整段加值；输入：节点 p、区间长度 len、增量 v；输出：更新 t[p] 与 tag[p]，无返回值。
    void apply(int p, int len, i64 v) {
        t[p] += v * len;
        tag[p] += v;
    }
    // 作用：下传加法标记；输入：节点 p 及其区间 [l,r)；输出：更新两个孩子并清空 tag[p]。
    void push(int p, int l, int r) {
        int mid = l + (r - l) / 2;
        apply(p * 2, mid - l, tag[p]);
        apply(p * 2 + 1, r - mid, tag[p]);
        tag[p] = 0;
    }
    // 作用：区间累加；输入：半开区间 [l,r)、增量 v；输出：更新区间和与懒标记，无返回值。
    void add(int l, int r, i64 v) {
        assert(0 <= l && l <= r && r <= n);
        add(1, 0, n, l, r, v);
    }
    // 作用：单点累加；输入：下标 i、增量 v；输出：更新该点及区间和，无返回值。
    void add(int i, i64 v) {
        assert(0 <= i && i < n);
        add(i, i + 1, v);
    }
    // 作用：递归区间累加；输入：节点 p、区间 [l,r)、目标 [ql,qr)、增量 v；输出：更新该子树，无返回值。
    void add(int p, int l, int r, int ql, int qr, i64 v) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            apply(p, r - l, v);
            return;
        }
        push(p, l, r);
        int mid = l + (r - l) / 2;
        add(p * 2, l, mid, ql, qr, v);
        add(p * 2 + 1, mid, r, ql, qr, v);
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
    // 作用：查询区间和；输入：半开区间 [l,r)；输出：区间元素和，空区间为 0。
    i64 qry(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return qry(1, 0, n, l, r);
    }
    // 作用：递归查询并下传标记；输入：节点 p、区间 [l,r)、目标 [ql,qr)；输出：交集内的元素和。
    i64 qry(int p, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return t[p];
        push(p, l, r);
        int mid = l + (r - l) / 2;
        return qry(p * 2, l, mid, ql, qr) + qry(p * 2 + 1, mid, r, ql, qr);
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    LazySeg t({1, 2, 3, 4});
    t.add(0, 4, 2);
    t.add(1, 3);
    cout << t.qry(1, 3) << '\n'; // 输出：12
}
