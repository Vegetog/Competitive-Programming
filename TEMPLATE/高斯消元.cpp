/*
算法：高斯消元
简介：使用列主元消元，判断实数线性方程组无解、多解或唯一解。
复杂度：时间 O(n³)，空间 O(n²)。
约定：输入为 n×(n+1) 增广矩阵；返回 status = -1/0/1（无解/多解/唯一解）；仅唯一解时读取 x。
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
constexpr double eps = 1e-9;

struct GaussRes {
    int status;
    vector<double> x;
};

// 作用：求解实数线性方程组；输入：n×(n+1) 增广矩阵 a 的副本；输出：status=-1/0/1 表示无解/多解/唯一解，仅唯一解时 x 有效。
GaussRes gauss(vector<vector<double>> a) {
    int n = a.size(), row = 0;
    for (const auto& eq : a) assert(int(eq.size()) == n + 1);
    for (int col = 0; col < n && row < n; ++col) {
        int pivot = row;
        for (int i = row + 1; i < n; ++i) {
            if (abs(a[i][col]) > abs(a[pivot][col])) pivot = i;
        }
        if (abs(a[pivot][col]) < eps) continue;
        swap(a[row], a[pivot]);
        for (int i = 0; i < n; ++i) {
            if (i == row) continue;
            double factor = a[i][col] / a[row][col];
            for (int j = col; j <= n; ++j) a[i][j] -= a[row][j] * factor;
        }
        ++row;
    }
    for (int i = row; i < n; ++i) {
        if (abs(a[i][n]) >= eps) return {-1, {}};
    }
    if (row < n) return {0, {}};
    vector<double> x(n);
    for (int i = 0; i < n; ++i) x[i] = a[i][n] / a[i][i];
    return {1, x};
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    auto res = gauss({{1, 1, 3}, {2, -1, 0}});
    if (res.status == 1) cout << res.x[0] << ' ' << res.x[1] << '\n'; // 1 2
}
