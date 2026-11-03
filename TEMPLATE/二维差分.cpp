/*
算法：二维差分
简介：用矩形的四个角记录增量，批量完成子矩形加法后，通过二维前缀和还原矩阵。
复杂度：初始化/还原时间 O(nm)，每次修改 O(1)；空间 O(nm)。
约定：0 下标；矩形为 [x1,x2) × [y1,y2)，x 为行、y 为列；行列数非负，输入须为矩形矩阵。
      允许空矩阵和空修改；元素、差分值及运算中间结果须在 i64 范围内。
      build() 不改变差分数组，可重复调用，也可在还原后继续修改；不支持在线矩形求和。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct Difference2D {
    int rows, columns;
    vector<vector<i64>> difference;

    Difference2D(int rows, int columns) : rows(rows), columns(columns) {
        assert(rows >= 0 && columns >= 0);
        difference.assign(rows + 1, vector<i64>(columns + 1));
    }

    explicit Difference2D(const vector<vector<i64>>& values)
        : Difference2D(static_cast<int>(values.size()),
                       values.empty() ? 0 : static_cast<int>(values[0].size())) {
        for (int i = 0; i < rows; ++i) {
            assert(static_cast<int>(values[i].size()) == columns);
            for (int j = 0; j < columns; ++j) {
                difference[i][j] = values[i][j];
                if (i > 0) difference[i][j] -= values[i - 1][j];
                if (j > 0) difference[i][j] -= values[i][j - 1];
                if (i > 0 && j > 0) difference[i][j] += values[i - 1][j - 1];
            }
        }
    }

    void range_add(int x1, int y1, int x2, int y2, i64 value) {
        assert(0 <= x1 && x1 <= x2 && x2 <= rows);
        assert(0 <= y1 && y1 <= y2 && y2 <= columns);
        if (x1 == x2 || y1 == y2) return;
        difference[x1][y1] += value;
        difference[x2][y1] -= value;
        difference[x1][y2] -= value;
        difference[x2][y2] += value;
    }

    vector<vector<i64>> build() const {
        vector<vector<i64>> values(rows, vector<i64>(columns));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                values[i][j] = difference[i][j];
                if (i > 0) values[i][j] += values[i - 1][j];
                if (j > 0) values[i][j] += values[i][j - 1];
                if (i > 0 && j > 0) values[i][j] -= values[i - 1][j - 1];
            }
        }
        return values;
    }
};

// ==================== 使用示例 ====================
int main() {
    vector<vector<i64>> values{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Difference2D difference(values); // 若初始矩阵全为 0，可用 Difference2D(rows, columns)
    difference.range_add(0, 0, 2, 2, 10);
    difference.range_add(1, 1, 3, 3, -2);
    for (const auto& row : difference.build()) {
        for (int j = 0; j < difference.columns; ++j) {
            cout << row[j] << (j + 1 == difference.columns ? '\n' : ' ');
        }
    }
    // 输出：
    // 11 12 3
    // 14 13 4
    // 7 6 7
}
