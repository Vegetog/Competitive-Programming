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
// 作用：合并相交闭区间；输入：区间数组 a，各区间满足 l <= r；输出：按左端点排序且互不相交的区间数组。
vector<pair<i64, i64>> merge_seg(vector<pair<i64, i64>> a) {
    sort(a.begin(), a.end());
    vector<pair<i64, i64>> res;
    for (auto [l, r] : a) {
        if (!res.empty() && l <= res.back().second) {
            res.back().second = max(res.back().second, r);
        } else {
            res.push_back({l, r});
        }
    }
    return res;
}

// ==================== 使用示例 ====================
// 作用：演示区间合并；输入：无，使用三段固定区间；输出：两行 1 5、7 8。
int main() {
    for (auto [l, r] : merge_seg({{1, 3}, {2, 5}, {7, 8}})) {
        cout << l << ' ' << r << '\n'; // 1 5 / 7 8
    }
}
