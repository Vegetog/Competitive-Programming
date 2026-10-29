/*
算法：静态区间最值查询（位集分块）
简介：块内使用单调栈位集，块间使用稀疏表；通过比较器切换最小值/最大值。
复杂度：时间：预处理 O(n+(n/64) log(n/64))，查询 O(1)；空间：O(n+(n/64) log(n/64))。
约定：下标从 0 开始；query(l,r) 查询非空区间 [l,r)；建表后不支持修改。
*/
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
template <class T, class Compare = less<T>> struct Rmq {
    static constexpr int kBlockSize = 64;
    int n = 0;
    Compare compare;
    vector<vector<T>> table;
    vector<T> prefix, suffix, values;
    vector<uint64_t> masks;
    explicit Rmq(const vector<T>& a = {}) { init(a); }
    static int floor_log2(uint64_t x) { return 63 - __builtin_clzll(x); }
    T better(const T& a, const T& b) const { return compare(b, a) ? b : a; }
    void init(const vector<T>& a) {
        n = a.size();
        prefix = suffix = values = a;
        masks.assign(n, 0);
        table.clear();
        if (!n) return;
        int blocks = (n + kBlockSize - 1) / kBlockSize;
        int levels = floor_log2(blocks) + 1;
        table.assign(levels, vector<T>(blocks));
        for (int i = 0; i < n; i++) {
            if (i % kBlockSize) prefix[i] = better(prefix[i - 1], a[i]);
        }
        for (int i = n - 2; i >= 0; i--) {
            if (i % kBlockSize != kBlockSize - 1) suffix[i] = better(a[i], suffix[i + 1]);
        }
        for (int block = 0; block < blocks; block++) {
            int l = block * kBlockSize, r = min(n, l + kBlockSize);
            table[0][block] = suffix[l];
            uint64_t mask = 0;
            for (int i = l; i < r; i++) {
                while (mask && compare(a[i], a[l + floor_log2(mask)])) {
                    mask ^= uint64_t{1} << floor_log2(mask);
                }
                mask |= uint64_t{1} << (i - l);
                masks[i] = mask;
            }
        }
        for (int level = 1; level < levels; level++) {
            for (int i = 0; i + (1 << level) <= blocks; i++) {
                table[level][i] =
                    better(table[level - 1][i], table[level - 1][i + (1 << (level - 1))]);
            }
        }
    }
    T query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        if (l / kBlockSize == (r - 1) / kBlockSize) {
            uint64_t mask = masks[r - 1] >> (l % kBlockSize);
            return values[l + __builtin_ctzll(mask)];
        }
        T result = better(suffix[l], prefix[r - 1]);
        int first = l / kBlockSize + 1, last = r / kBlockSize;
        if (first < last) {
            int level = floor_log2(last - first);
            result = better(result, better(table[level][first], table[level][last - (1 << level)]));
        }
        return result;
    }
};

// ==================== 使用示例 ====================
int main() {
    Rmq<int> minimum({5, 2, 4, 1, 3});
    Rmq<int, greater<int>> maximum({5, 2, 4, 1, 3});
    cout << minimum.query(1, 4) << ' ' << maximum.query(1, 4) << '\n'; // 输出：1 4
}
