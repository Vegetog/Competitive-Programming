/*
算法：二分查找
简介：在升序数组中寻找第一个 >= x 的位置，或最后一个 <= x 的位置。
复杂度：时间 O(log n)，空间 O(1)。
约定：下标从 0 开始；后继不存在返回 n，前驱不存在返回 -1；允许空数组。
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
template <class T> int lower_bound_index(const vector<T>& values, const T& target) {
    int left = 0, right = values.size();
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (values[middle] >= target)
            right = middle;
        else
            left = middle + 1;
    }
    return left;
}
template <class T> int predecessor_index(const vector<T>& values, const T& target) {
    int left = 0, right = values.size();
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (values[middle] > target)
            right = middle;
        else
            left = middle + 1;
    }
    return left - 1;
}

// ==================== 使用示例 ====================
int main() {
    vector<int> values{1, 3, 3, 7};
    cout << lower_bound_index(values, 3) << ' ' << predecessor_index(values, 3) << '\n'; // 1 2
    cout << lower_bound(values.begin(), values.end(), 3) - values.begin() << '\n';       // 1
    // 降序数组改用 lower_bound(begin, end, x, greater<int>())。
}
