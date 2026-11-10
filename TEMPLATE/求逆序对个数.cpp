/*
算法：逆序对计数
简介：在归并过程中统计右半部分元素越过的左半部分元素数量。
复杂度：时间 O(n log n)，空间 O(n)。
约定：统计 i < j 且 a[i] > a[j] 的数对；会将数组排成升序；返回 i64。
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
// 作用：统计严格逆序对；输入：可修改数组 a；输出：满足 i < j 且 a[i] > a[j] 的数对数，同时将 a 排为升序。
template <class T> i64 inv_count(vector<T>& a) {
    int n = a.size();
    vector<T> tmp(n);
    // 作用：归并并统计一段的逆序对；输入：半开区间 [l,r)；输出：该段逆序对数，同时将 a[l,r) 排序并使用 tmp 缓冲。
    function<i64(int, int)> dfs = [&](int l, int r) -> i64 {
        if (r - l <= 1) return 0;
        int mid = l + (r - l) / 2;
        i64 cnt = dfs(l, mid) + dfs(mid, r);
        int i = l, j = mid, k = l;
        while (i < mid && j < r) {
            if (a[i] <= a[j])
                tmp[k++] = a[i++];
            else {
                tmp[k++] = a[j++];
                cnt += mid - i;
            }
        }
        while (i < mid) tmp[k++] = a[i++];
        while (j < r) tmp[k++] = a[j++];
        copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
        return cnt;
    };
    return dfs(0, n);
}

// ==================== 使用示例 ====================
// 作用：演示逆序对计数；输入：无，使用数组 {3,2,1}；输出：3。
int main() {
    vector<int> a{3, 2, 1};
    cout << inv_count(a) << '\n'; // 3
}
