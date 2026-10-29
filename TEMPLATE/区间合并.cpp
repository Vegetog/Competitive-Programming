/*
算法：区间合并
简介：按左端点排序，合并相交的闭区间。
复杂度：时间 O(n log n)，额外空间 O(n)。
约定：区间为闭区间 [l,r]，要求 l <= r；共享端点时合并，空输入返回空数组。
*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
vector<pair<i64, i64>> merge_intervals(vector<pair<i64, i64>> intervals) {
    sort(intervals.begin(), intervals.end());
    vector<pair<i64, i64>> merged;
    for (auto [left, right] : intervals) {
        if (!merged.empty() && left <= merged.back().second) {
            merged.back().second = max(merged.back().second, right);
        } else {
            merged.push_back({left, right});
        }
    }
    return merged;
}

// ==================== 使用示例 ====================
int main() {
    for (auto [left, right] : merge_intervals({{1, 3}, {2, 5}, {7, 8}})) {
        cout << left << ' ' << right << '\n'; // 1 5 / 7 8
    }
}
