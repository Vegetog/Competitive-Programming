/*
算法：归并排序
简介：递归排序左右两半并稳定合并，同时返回逆序对个数。
复杂度：时间 O(n log n)，空间 O(n)。
约定：原地修改传入数组；逆序对要求 a[i] > a[j]，计数使用 i64。
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
// 作用：稳定归并排序并计数逆序对；输入：可修改数组 a；输出：逆序对数，同时将 a 排为升序。
template <class T> i64 merge_sort(vector<T>& a) {
    int n = a.size();
    vector<T> tmp(n);
    // 作用：递归处理子区间；输入：半开区间 [l,r)；输出：该段逆序对数，同时将 a[l,r) 排序并使用 tmp 缓冲。
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
// 作用：演示排序与逆序计数；输入：无，使用数组 {3,1,2}；输出：2 和排序后的 1 2 3。
int main() {
    vector<int> a{3, 1, 2};
    cout << merge_sort(a) << '\n'; // 2
    for (int x : a) cout << x << ' ';
    cout << '\n'; // 1 2 3
}
