/*
算法：分块（区间加、区间和）
简介：每块维护不含懒标记的元素和，整块修改累计加法标记。
复杂度：时间：建表 O(n)，每次修改/查询 O(√n)；空间：O(n)。
约定：下标从 0 开始；区间为 [l,r)，允许空区间；所有元素和及修改中间值须在 i64 范围内。
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct Block {
    int n, B;
    vector<i64> a, sum, tag;
    // 作用：建立分块；输入：数组 a；输出：保存元素、块和及零加法标记的 Block。
    explicit Block(const vector<i64>& a)
        : n(a.size()), B(max(1, static_cast<int>(sqrt(n)))), a(a), sum((n + B - 1) / B),
          tag(sum.size()) {
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }
    // 作用：区间累加；输入：半开区间 [l,r)、增量 v；输出：更新元素/块和/标记，无返回值。
    void add(int l, int r, i64 v) {
        assert(0 <= l && l <= r && r <= n);
        while (l < r) {
            int b = l / B;
            int e = min(n, (b + 1) * B);
            if (l % B == 0 && e <= r) {
                tag[b] += v;
                l = e;
            } else {
                a[l++] += v;
                sum[b] += v;
            }
        }
    }
    // 作用：查询区间和；输入：半开区间 [l,r)；输出：计入标记后的元素和，空区间为 0。
    i64 qry(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        i64 res = 0;
        while (l < r) {
            int b = l / B;
            int e = min(n, (b + 1) * B);
            if (l % B == 0 && e <= r) {
                res += sum[b] + tag[b] * (e - l);
                l = e;
            } else {
                res += a[l++] + tag[b];
            }
        }
        return res;
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    Block s({1, 2, 3, 4, 5});
    s.add(1, 4, 2);
    cout << s.qry(0, 5) << '\n'; // 输出：21
}
