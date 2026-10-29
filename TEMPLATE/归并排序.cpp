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
template <class T> i64 merge_sort(vector<T>& values) {
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
    vector<int> values{3, 1, 2};
    cout << merge_sort(values) << '\n'; // 2
    for (int value : values) cout << value << ' ';
    cout << '\n'; // 1 2 3
}
