/*
算法：二维前缀和
简介：预处理静态矩阵的二维前缀和，常数时间查询任意子矩形的元素和。
复杂度：预处理时间 O(nm)，每次查询 O(1)；空间 O(nm)。
约定：0 下标；矩形为 [x1,x2) × [y1,y2)，x 为行、y 为列；输入须为矩形矩阵，允许空矩阵和空查询。
      元素、前缀和及运算中间结果须在 i64 范围内；原矩阵改变后须重新构造。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct PrefixSum2D {
    int rows, columns;
    vector<vector<i64>> prefix;

    explicit PrefixSum2D(const vector<vector<i64>>& values)
        : rows(static_cast<int>(values.size())),
          columns(rows == 0 ? 0 : static_cast<int>(values[0].size())),
          prefix(rows + 1, vector<i64>(columns + 1)) {
        for (int i = 0; i < rows; ++i) {
            assert(static_cast<int>(values[i].size()) == columns);
            for (int j = 0; j < columns; ++j) {
                prefix[i + 1][j + 1] =
                    values[i][j] + prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j];
            }
        }
    }

    i64 range_sum(int x1, int y1, int x2, int y2) const {
        assert(0 <= x1 && x1 <= x2 && x2 <= rows);
        assert(0 <= y1 && y1 <= y2 && y2 <= columns);
        if (x1 == x2 || y1 == y2) return 0;
        return prefix[x2][y2] - prefix[x1][y2] - prefix[x2][y1] + prefix[x1][y1];
    }
};

// ==================== 使用示例 ====================
int main() {
    vector<vector<i64>> values{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    PrefixSum2D prefix(values);
    cout << prefix.range_sum(0, 0, 3, 3) << '\n'; // 输出：45，整个矩阵
    cout << prefix.range_sum(1, 1, 3, 3) << '\n'; // 输出：28，右下角 2×2 子矩形
    cout << prefix.range_sum(1, 0, 1, 3) << '\n'; // 输出：0，空矩形
}
