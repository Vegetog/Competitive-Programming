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

struct Mat {
    static constexpr i64 P = 1000000007;
    int n, m;
    vector<vector<i64>> a;

    // 作用：构造零矩阵；输入：非负行数 n、列数 m；输出：n×m 的全零矩阵。
    explicit Mat(int n, int m) : n(n), m(m), a(n, vector<i64>(m)) {}
    // 作用：构造零方阵；输入：阶数 n；输出：n×n 的全零矩阵。
    explicit Mat(int n) : Mat(n, n) {}

    // 作用：矩阵加法；输入：同形矩阵；输出：逐元素模 P 后的运算结果矩阵。
    Mat operator+(const Mat& other) const {
        assert(n == other.n && m == other.m);
        Mat res(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) res.a[i][j] = (a[i][j] + other.a[i][j]) % P;
        }
        return res;
    }
    // 作用：矩阵减法；输入：同形矩阵；输出：逐元素模 P 后的运算结果矩阵。
    Mat operator-(const Mat& other) const {
        assert(n == other.n && m == other.m);
        Mat res(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) res.a[i][j] = (a[i][j] - other.a[i][j] + P) % P;
        }
        return res;
    }
    // 作用：矩阵乘法；输入：列数与右矩阵行数相同的左矩阵和右矩阵；输出：逐元素模 P 后的运算结果矩阵。
    Mat operator*(const Mat& other) const {
        assert(m == other.n);
        Mat res(n, other.m);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < m; ++k) {
                for (int j = 0; j < other.m; ++j) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % P;
                }
            }
        }
        return res;
    }
    // 作用：求方阵幂；输入：当前方阵、非负指数 e；输出：模 P 的矩阵 e 次幂，0 次幂为单位矩阵。
    Mat qpow(i64 e) const {
        assert(n == m && e >= 0);
        Mat res(n), base = *this;
        for (int i = 0; i < n; ++i) res.a[i][i] = 1;
        for (; e; e >>= 1, base = base * base) {
            if (e & 1) res = res * base;
        }
        return res;
    }
    // 作用：输出矩阵；输入：当前矩阵和输出流 out（默认 cout）；输出：无返回值，逐行写出元素，以空格分隔。
    void print(ostream& out = cout) const {
        for (const auto& row : a) {
            for (int j = 0; j < m; ++j) out << row[j] << (j + 1 == m ? '\n' : ' ');
        }
    }
};

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    Mat fib(2);
    fib.a = {{1, 1}, {1, 0}};
    cout << fib.qpow(10).a[0][1] << '\n'; // 55
}
