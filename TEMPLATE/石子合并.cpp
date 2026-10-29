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
pair<i64, i64> stone_merge(const vector<i64>& weights) {
    int n = weights.size();
    if (n == 0) return {0, 0};
    vector<i64> prefix(n + 1);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + weights[i];
    vector minimum(n, vector<i64>(n)), maximum = minimum;
    for (int length = 2; length <= n; length++) {
        for (int left = 0; left + length <= n; left++) {
            int right = left + length - 1;
            i64 total = prefix[right + 1] - prefix[left];
            minimum[left][right] = numeric_limits<i64>::max();
            for (int middle = left; middle < right; middle++) {
                minimum[left][right] =
                    min(minimum[left][right],
                        minimum[left][middle] + minimum[middle + 1][right] + total);
                maximum[left][right] =
                    max(maximum[left][right],
                        maximum[left][middle] + maximum[middle + 1][right] + total);
            }
        }
    }
    return {minimum[0][n - 1], maximum[0][n - 1]};
}

// ==================== 使用示例 ====================
int main() {
    auto [minimum, maximum] = stone_merge({1, 2, 3});
    cout << minimum << ' ' << maximum << '\n'; // 9 11
}
