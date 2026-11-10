/*
算法：线段树（单点加、区间和）
简介：二叉划分区间，维护每个节点的区间和。
复杂度：时间：建树 O(n)，单点修改/区间查询 O(log n)；空间：O(n)。
约定：下标从 0 开始；查询为 [l,r)，允许空数组/空区间；中间和须在 i64 范围内。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct Seg {
    int n;
    vector<i64> t;
    // 作用：建立求和线段树；输入：数组 a；输出：维护 a 的线段树。
    explicit Seg(const vector<i64>& a) : n(a.size()), t(4 * n + 4) {
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
    // 作用：单点累加；输入：下标 i、增量 v；输出：更新该点及祖先的区间和，无返回值。
    void add(int i, i64 v) {
        assert(0 <= i && i < n);
        add(1, 0, n, i, v);
    }
    // 作用：递归单点累加；输入：节点 p、区间 [l,r)、目标 i、增量 v；输出：更新该子树，无返回值。
    void add(int p, int l, int r, int i, i64 v) {
        if (r - l == 1) {
            t[p] += v;
            return;
        }
        int mid = l + (r - l) / 2;
        if (i < mid)
            add(p * 2, l, mid, i, v);
        else
            add(p * 2 + 1, mid, r, i, v);
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
    // 作用：查询区间和；输入：半开区间 [l,r)；输出：区间元素和，空区间为 0。
    i64 qry(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return qry(1, 0, n, l, r);
    }
    // 作用：递归查询；输入：节点 p、区间 [l,r)、目标 [ql,qr)；输出：两区间交集的元素和。
    i64 qry(int p, int l, int r, int ql, int qr) const {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return t[p];
        int mid = l + (r - l) / 2;
        return qry(p * 2, l, mid, ql, qr) + qry(p * 2 + 1, mid, r, ql, qr);
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    Seg t({1, 2, 3, 4});
    t.add(1, 5);
    cout << t.qry(1, 4) << '\n'; // 输出：14
}
