/*
算法：树状数组（Fenwick Tree）
简介：维护单点增量和区间和，并支持非负频次上的前缀选择。
复杂度：时间：初始化 O(n)，修改/查询/选择 O(log n)；空间：O(n)。
约定：下标从 0 开始；区间为 [l,r)；select(k) 返回前缀和 <= k 的最长前缀长度，要求各点非负、k >= 0。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
template <class T> struct Fenwick {
    int n;
    vector<T> tree;
    explicit Fenwick(int size = 0) : n(size), tree(size + 1) {}
    void add(int pos, const T& value) {
        assert(0 <= pos && pos < n);
        for (int i = pos + 1; i <= n; i += i & -i) tree[i] += value;
    }
    T prefix_sum(int end) const {
        assert(0 <= end && end <= n);
        T result{};
        for (int i = end; i > 0; i -= i & -i) result += tree[i];
        return result;
    }
    T range_sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return prefix_sum(r) - prefix_sum(l);
    }
    int select(const T& k) const {
        assert(k >= T{});
        int pos = 0, step = 1;
        T sum{};
        while (step <= n / 2) step <<= 1;
        for (; step; step >>= 1) {
            if (pos + step <= n && sum + tree[pos + step] <= k) {
                pos += step;
                sum += tree[pos];
            }
        }
        return pos;
    }
};

// ==================== 使用示例 ====================
int main() {
    Fenwick<i64> fenwick(4);
    vector<i64> a{1, 2, 3, 4};
    for (int i = 0; i < 4; i++) fenwick.add(i, a[i]);
    cout << fenwick.range_sum(1, 4) << '\n'; // 输出：9
    cout << fenwick.select(3) << '\n';       // 输出：2，即前两个元素和 <= 3
}
