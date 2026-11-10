/*
算法：石子合并（区间 DP）
简介：每次合并相邻两堆，求把一行石子合并为一堆的最小与最大代价。
复杂度：时间 O(n³)，空间 O(n²)。
约定：石子重量非负；合并代价为两堆重量和，所有中间结果须在 i64 范围内；空数组代价为 0。
*/
#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
// 作用：求一行石子相邻合并的最小、最大代价；输入：非负堆重数组 a；输出：{最小代价, 最大代价}，空数组返回 {0,0}。
pair<i64, i64> stones(const vector<i64>& a) {
    int n = a.size();
    if (n == 0) return {0, 0};
    vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
    vector mn(n, vector<i64>(n)), mx = mn;
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            i64 sum = s[r + 1] - s[l];
            mn[l][r] = numeric_limits<i64>::max();
            for (int mid = l; mid < r; mid++) {
                mn[l][r] = min(mn[l][r], mn[l][mid] + mn[mid + 1][r] + sum);
                mx[l][r] = max(mx[l][r], mx[l][mid] + mx[mid + 1][r] + sum);
            }
        }
    }
    return {mn[0][n - 1], mx[0][n - 1]};
}

// ==================== 使用示例 ====================
// 作用：演示石子合并；输入：无，使用堆重 {1,2,3}；输出：9 11。
int main() {
    auto [mn, mx] = stones({1, 2, 3});
    cout << mn << ' ' << mx << '\n'; // 9 11
}
