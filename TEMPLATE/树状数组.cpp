/*
算法：树状数组（Fenwick Tree / BIT）
简介：维护单点增量和区间和，并支持非负频次上的前缀选择。
复杂度：时间：初始化 O(n)，修改/查询/选择 O(log n)；空间：O(n)。
约定：下标从 0 开始；区间为 [l,r)；kth(k) 返回前缀和 <= k 的最长前缀长度，要求各点非负、k >= 0。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
template <class T> struct BIT {
    int n;
    vector<T> t;
    // 作用：初始化树状数组；输入：长度 sz（默认 0）；输出：所有元素为 T{} 的 BIT。
    explicit BIT(int sz = 0) : n(sz), t(sz + 1) {}
    // 作用：单点累加；输入：下标 p、增量 v；输出：更新 t，无返回值。
    void add(int p, const T& v) {
        assert(0 <= p && p < n);
        for (int i = p + 1; i <= n; i += i & -i) t[i] += v;
    }
    // 作用：查询前缀和；输入：右端点 r，0 <= r <= n；输出：[0,r) 的和。
    T sum(int r) const {
        assert(0 <= r && r <= n);
        T res{};
        for (int i = r; i > 0; i -= i & -i) res += t[i];
        return res;
    }
    // 作用：查询区间和；输入：半开区间 [l,r)；输出：该区间元素之和。
    T qry(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }
    // 作用：前缀选择；输入：非负阈值 k，要求所有元素非负；输出：和 <= k 的最长前缀长度（0..n）。
    int kth(const T& k) const {
        assert(k >= T{});
        int p = 0, d = 1;
        T sum{};
        while (d <= n / 2) d <<= 1;
        for (; d; d >>= 1) {
            if (p + d <= n && sum + t[p + d] <= k) {
                p += d;
                sum += t[p];
            }
        }
        return p;
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    BIT<i64> bit(4);
    vector<i64> a{1, 2, 3, 4};
    for (int i = 0; i < 4; i++) bit.add(i, a[i]);
    cout << bit.qry(1, 4) << '\n'; // 输出：9
    cout << bit.kth(3) << '\n';    // 输出：2，即前两个元素和 <= 3
}
