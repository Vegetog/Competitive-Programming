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
// 作用：二分查找下界；输入：升序数组 a、目标 x；输出：首个 a[i] >= x 的下标，不存在返回 a.size()。
template <class T> int lb(const vector<T>& a, const T& x) {
    int l = 0, r = a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
// 作用：二分查找前驱；输入：升序数组 a、目标 x；输出：最后一个 a[i] <= x 的下标，不存在返回 -1。
template <class T> int pred(const vector<T>& a, const T& x) {
    int l = 0, r = a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] > x)
            r = mid;
        else
            l = mid + 1;
    }
    return l - 1;
}

// ==================== 使用示例 ====================
// 作用：演示两种二分接口；输入：无，使用固定升序数组；输出：1 2 和标准库下界 1。
int main() {
    vector<int> a{1, 3, 3, 7};
    cout << lb(a, 3) << ' ' << pred(a, 3) << '\n';                  // 1 2
    cout << lower_bound(a.begin(), a.end(), 3) - a.begin() << '\n'; // 1
    // 降序数组改用 lower_bound(begin, end, x, greater<int>())。
}
