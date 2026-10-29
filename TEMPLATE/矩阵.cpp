/*
算法：矩阵运算与快速幂
简介：支持模意义下的矩阵加减乘和方阵快速幂。
复杂度：n×m 加减 O(nm)，n×k 乘 k×m 为 O(nkm)，n 阶幂 O(n³ log e)；空间与所存矩阵规模成正比，方阵幂 O(n²)。
约定：0 下标；元素须在 [0,1000000007)；乘法维数匹配，幂指数非负。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

struct Matrix {
    static constexpr i64 kModulus = 1000000007;
    int rows, columns;
    vector<vector<i64>> values;

    explicit Matrix(int rows, int columns)
        : rows(rows), columns(columns), values(rows, vector<i64>(columns)) {}
    explicit Matrix(int n) : Matrix(n, n) {}

    Matrix operator+(const Matrix& other) const {
        assert(rows == other.rows && columns == other.columns);
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j)
                result.values[i][j] = (values[i][j] + other.values[i][j]) % kModulus;
        }
        return result;
    }
    Matrix operator-(const Matrix& other) const {
        assert(rows == other.rows && columns == other.columns);
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j)
                result.values[i][j] = (values[i][j] - other.values[i][j] + kModulus) % kModulus;
        }
        return result;
    }
    Matrix operator*(const Matrix& other) const {
        assert(columns == other.rows);
        Matrix result(rows, other.columns);
        for (int i = 0; i < rows; ++i) {
            for (int k = 0; k < columns; ++k) {
                for (int j = 0; j < other.columns; ++j) {
                    result.values[i][j] =
                        (result.values[i][j] + values[i][k] * other.values[k][j]) % kModulus;
                }
            }
        }
        return result;
    }
    Matrix power(i64 exponent) const {
        assert(rows == columns && exponent >= 0);
        Matrix result(rows), base = *this;
        for (int i = 0; i < rows; ++i) result.values[i][i] = 1;
        for (; exponent; exponent >>= 1, base = base * base) {
            if (exponent & 1) result = result * base;
        }
        return result;
    }
    void print(ostream& output = cout) const {
        for (const auto& row : values) {
            for (int j = 0; j < columns; ++j) output << row[j] << (j + 1 == columns ? '\n' : ' ');
        }
    }
};

// ==================== 使用示例 ====================
int main() {
    Matrix fibonacci(2);
    fibonacci.values = {{1, 1}, {1, 0}};
    cout << fibonacci.power(10).values[0][1] << '\n'; // 55
}
