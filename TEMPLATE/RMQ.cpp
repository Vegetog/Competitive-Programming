/*
算法：静态区间最值查询（位集分块）
简介：块内使用单调栈位集，块间使用稀疏表；通过比较器切换最小值/最大值。
复杂度：时间：预处理 O(n+(n/64) log(n/64))，查询 O(1)；空间：O(n+(n/64) log(n/64))。
约定：下标从 0 开始；qry(l,r) 查询非空区间 [l,r)；建表后不支持修改。
*/
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
template <class T, class Cmp = less<T>> struct RMQ {
    static constexpr int B = 64;
    int n = 0;
    Cmp cmp;
    vector<vector<T>> st;
    vector<T> pre, suf, val;
    vector<uint64_t> msk;
    // 作用：建立静态最值表；输入：数组 a（默认空）；输出：按 Cmp 比较的 RMQ。
    explicit RMQ(const vector<T>& a = {}) { init(a); }
    // 作用：求二进制最高位；输入：正整数 x；输出：floor(log2(x))。
    static int lg(uint64_t x) { return 63 - __builtin_clzll(x); }
    // 作用：比较两个候选值；输入：a、b；输出：按 Cmp 选出的较优值。
    T best(const T& a, const T& b) const { return cmp(b, a) ? b : a; }
    // 作用：重建最值表；输入：数组 a；输出：更新前后缀、块位集和稀疏表，无返回值。
    void init(const vector<T>& a) {
        n = a.size();
        pre = suf = val = a;
        msk.assign(n, 0);
        st.clear();
        if (!n) return;
        int cnt = (n + B - 1) / B;
        int h = lg(cnt) + 1;
        st.assign(h, vector<T>(cnt));
        for (int i = 0; i < n; i++) {
            if (i % B) pre[i] = best(pre[i - 1], a[i]);
        }
        for (int i = n - 2; i >= 0; i--) {
            if (i % B != B - 1) suf[i] = best(a[i], suf[i + 1]);
        }
        for (int b = 0; b < cnt; b++) {
            int l = b * B, r = min(n, l + B);
            st[0][b] = suf[l];
            uint64_t mask = 0;
            for (int i = l; i < r; i++) {
                while (mask && cmp(a[i], a[l + lg(mask)])) {
                    mask ^= uint64_t{1} << lg(mask);
                }
                mask |= uint64_t{1} << (i - l);
                msk[i] = mask;
            }
        }
        for (int k = 1; k < h; k++) {
            for (int i = 0; i + (1 << k) <= cnt; i++) {
                st[k][i] = best(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    // 作用：查询区间最值；输入：非空区间 [l,r)；输出：默认最小值，Cmp=greater<T> 时为最大值。
    T qry(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        if (l / B == (r - 1) / B) {
            uint64_t mask = msk[r - 1] >> (l % B);
            return val[l + __builtin_ctzll(mask)];
        }
        T res = best(suf[l], pre[r - 1]);
        int first = l / B + 1, last = r / B;
        if (first < last) {
            int k = lg(last - first);
            res = best(res, best(st[k][first], st[k][last - (1 << k)]));
        }
        return res;
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    RMQ<int> mn({5, 2, 4, 1, 3});
    RMQ<int, greater<int>> mx({5, 2, 4, 1, 3});
    cout << mn.qry(1, 4) << ' ' << mx.qry(1, 4) << '\n'; // 输出：1 4
}
