/*
算法：整数区间并计数
简介：合并闭区间，统计被覆盖的整数点数。
复杂度：时间 O(n log n)，额外空间 O(n)，包含输入副本。
约定：区间为闭区间 [l,r]；坐标及总点数须能用 i64 表示；允许空输入和反向端点。
*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
// 作用：统计闭区间并集中的整数点；输入：区间数组 a，端点可逆序；输出：覆盖点数，空数组返回 0，不修改调用方数组。
i64 covered(vector<pair<i64, i64>> a) {
    if (a.empty()) return 0;
    for (auto& [l, r] : a)
        if (l > r) swap(l, r);
    sort(a.begin(), a.end());
    auto [l, r] = a[0];
    i64 cnt = 0;
    for (auto [nl, nr] : a) {
        if (nl > r) {
            cnt += r - l + 1;
            l = nl;
        }
        r = max(r, nr);
    }
    return cnt + (r - l + 1);
}

// ==================== 使用示例 ====================
// 作用：演示区间覆盖计数；输入：无，使用固定区间；输出：覆盖点数 6 和 [0,10] 中未覆盖点数 6。
int main() {
    cout << covered({{1, 3}, {2, 5}, {8, 8}}) << '\n'; // 6
    cout << 11 - covered({{1, 3}, {2, 5}}) << '\n';    // [0,10] 剩 6 棵
}
