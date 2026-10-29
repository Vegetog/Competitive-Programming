/*
算法：分块（区间加、区间和）
简介：每块维护不含懒标记的元素和，整块修改累计加法标记。
复杂度：时间：建表 O(n)，每次修改/查询 O(√n)；空间：O(n)。
约定：下标从 0 开始；区间为 [l,r)，允许空区间；所有元素和及修改中间值须在 i64 范围内。
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct SqrtDecomposition {
    int n, block_size;
    vector<i64> values, sum, lazy;
    explicit SqrtDecomposition(const vector<i64>& a)
        : n(a.size()), block_size(max(1, static_cast<int>(sqrt(n)))), values(a),
          sum((n + block_size - 1) / block_size), lazy(sum.size()) {
        for (int i = 0; i < n; i++) sum[i / block_size] += values[i];
    }
    void range_add(int l, int r, i64 value) {
        assert(0 <= l && l <= r && r <= n);
        while (l < r) {
            int block = l / block_size;
            int end = min(n, (block + 1) * block_size);
            if (l % block_size == 0 && end <= r) {
                lazy[block] += value;
                l = end;
            } else {
                values[l++] += value;
                sum[block] += value;
            }
        }
    }
    i64 range_sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        i64 result = 0;
        while (l < r) {
            int block = l / block_size;
            int end = min(n, (block + 1) * block_size);
            if (l % block_size == 0 && end <= r) {
                result += sum[block] + lazy[block] * (end - l);
                l = end;
            } else {
                result += values[l++] + lazy[block];
            }
        }
        return result;
    }
};

// ==================== 使用示例 ====================
int main() {
    SqrtDecomposition blocks({1, 2, 3, 4, 5});
    blocks.range_add(1, 4, 2);
    cout << blocks.range_sum(0, 5) << '\n'; // 输出：21
}
