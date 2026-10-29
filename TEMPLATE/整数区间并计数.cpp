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
i64 count_covered_points(vector<pair<i64, i64>> intervals) {
    if (intervals.empty()) return 0;
    for (auto& [left, right] : intervals)
        if (left > right) swap(left, right);
    sort(intervals.begin(), intervals.end());
    auto [left, right] = intervals[0];
    i64 count = 0;
    for (auto [next_left, next_right] : intervals) {
        if (next_left > right) {
            count += right - left + 1;
            left = next_left;
        }
        right = max(right, next_right);
    }
    return count + (right - left + 1);
}

// ==================== 使用示例 ====================
int main() {
    cout << count_covered_points({{1, 3}, {2, 5}, {8, 8}}) << '\n'; // 6
    cout << 11 - count_covered_points({{1, 3}, {2, 5}}) << '\n';    // [0,10] 剩 6 棵
}
