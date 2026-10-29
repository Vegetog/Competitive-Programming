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
struct PointSegmentTree {
    int n;
    vector<i64> tree;
    explicit PointSegmentTree(const vector<i64>& a) : n(a.size()), tree(4 * n + 4) {
        if (n) build(1, 0, n, a);
    }
    void build(int p, int l, int r, const vector<i64>& a) {
        if (r - l == 1) {
            tree[p] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(p * 2, l, mid, a);
        build(p * 2 + 1, mid, r, a);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    void add(int pos, i64 value) {
        assert(0 <= pos && pos < n);
        add(1, 0, n, pos, value);
    }
    void add(int p, int l, int r, int pos, i64 value) {
        if (r - l == 1) {
            tree[p] += value;
            return;
        }
        int mid = l + (r - l) / 2;
        if (pos < mid)
            add(p * 2, l, mid, pos, value);
        else
            add(p * 2 + 1, mid, r, pos, value);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    i64 query(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return query(1, 0, n, l, r);
    }
    i64 query(int p, int l, int r, int ql, int qr) const {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[p];
        int mid = l + (r - l) / 2;
        return query(p * 2, l, mid, ql, qr) + query(p * 2 + 1, mid, r, ql, qr);
    }
};

// ==================== 使用示例 ====================
int main() {
    PointSegmentTree tree({1, 2, 3, 4});
    tree.add(1, 5);
    cout << tree.query(1, 4) << '\n'; // 输出：14
}
