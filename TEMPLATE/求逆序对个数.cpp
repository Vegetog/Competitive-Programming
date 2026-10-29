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
template <class T> i64 count_inversions(vector<T>& values) {
    int n = values.size();
    vector<T> buffer(n);
    function<i64(int, int)> sort_range = [&](int left, int right) -> i64 {
        if (right - left <= 1) return 0;
        int middle = left + (right - left) / 2;
        i64 count = sort_range(left, middle) + sort_range(middle, right);
        int i = left, j = middle, k = left;
        while (i < middle && j < right) {
            if (values[i] <= values[j])
                buffer[k++] = values[i++];
            else {
                buffer[k++] = values[j++];
                count += middle - i;
            }
        }
        while (i < middle) buffer[k++] = values[i++];
        while (j < right) buffer[k++] = values[j++];
        copy(buffer.begin() + left, buffer.begin() + right, values.begin() + left);
        return count;
    };
    return sort_range(0, n);
}

// ==================== 使用示例 ====================
int main() {
    vector<int> values{3, 2, 1};
    cout << count_inversions(values) << '\n'; // 3
}
