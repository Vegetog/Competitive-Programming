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
struct RangeSegmentTree {
    int n;
    vector<i64> tree, lazy;
    explicit RangeSegmentTree(const vector<i64>& a)
        : n(a.size()), tree(4 * n + 4), lazy(4 * n + 4) {
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
    void apply(int p, int len, i64 value) {
        tree[p] += value * len;
        lazy[p] += value;
    }
    void push_down(int p, int l, int r) {
        int mid = l + (r - l) / 2;
        apply(p * 2, mid - l, lazy[p]);
        apply(p * 2 + 1, r - mid, lazy[p]);
        lazy[p] = 0;
    }
    void range_add(int l, int r, i64 value) {
        assert(0 <= l && l <= r && r <= n);
        range_add(1, 0, n, l, r, value);
    }
    void add(int pos, i64 value) {
        assert(0 <= pos && pos < n);
        range_add(pos, pos + 1, value);
    }
    void range_add(int p, int l, int r, int ql, int qr, i64 value) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            apply(p, r - l, value);
            return;
        }
        push_down(p, l, r);
        int mid = l + (r - l) / 2;
        range_add(p * 2, l, mid, ql, qr, value);
        range_add(p * 2 + 1, mid, r, ql, qr, value);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    i64 query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return query(1, 0, n, l, r);
    }
    i64 query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[p];
        push_down(p, l, r);
        int mid = l + (r - l) / 2;
        return query(p * 2, l, mid, ql, qr) + query(p * 2 + 1, mid, r, ql, qr);
    }
};

// ==================== 使用示例 ====================
int main() {
    RangeSegmentTree tree({1, 2, 3, 4});
    tree.range_add(0, 4, 2);
    tree.add(1, 3);
    cout << tree.query(1, 3) << '\n'; // 输出：12
}
