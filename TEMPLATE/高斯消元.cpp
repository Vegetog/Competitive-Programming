/*
算法：高斯消元
简介：使用列主元消元，判断实数线性方程组无解、多解或唯一解。
复杂度：时间 O(n³)，空间 O(n²)。
约定：输入为 n×(n+1) 增广矩阵；返回 status = -1/0/1（无解/多解/唯一解）；仅唯一解时读取 solution。
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
constexpr double kEpsilon = 1e-9;

struct GaussianResult {
    int status;
    vector<double> solution;
};

GaussianResult gaussian_elimination(vector<vector<double>> matrix) {
    int n = matrix.size(), row = 0;
    for (const auto& values : matrix) assert(int(values.size()) == n + 1);
    for (int column = 0; column < n && row < n; ++column) {
        int pivot = row;
        for (int i = row + 1; i < n; ++i) {
            if (abs(matrix[i][column]) > abs(matrix[pivot][column])) pivot = i;
        }
        if (abs(matrix[pivot][column]) < kEpsilon) continue;
        swap(matrix[row], matrix[pivot]);
        for (int i = 0; i < n; ++i) {
            if (i == row) continue;
            double factor = matrix[i][column] / matrix[row][column];
            for (int j = column; j <= n; ++j) matrix[i][j] -= matrix[row][j] * factor;
        }
        ++row;
    }
    for (int i = row; i < n; ++i) {
        if (abs(matrix[i][n]) >= kEpsilon) return {-1, {}};
    }
    if (row < n) return {0, {}};
    vector<double> solution(n);
    for (int i = 0; i < n; ++i) solution[i] = matrix[i][n] / matrix[i][i];
    return {1, solution};
}

// ==================== 使用示例 ====================
int main() {
    auto result = gaussian_elimination({{1, 1, 3}, {2, -1, 0}});
    if (result.status == 1) cout << result.solution[0] << ' ' << result.solution[1] << '\n'; // 1 2
}
