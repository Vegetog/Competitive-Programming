#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif

#define int long long
#define new _MY_NEW_

using namespace std;
using ll = long long;
using PII = array<int, 2>;

constexpr long long INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

class GaussianElimination {
public:
    int n; // 方程组的个数（即变量的个数）
    vector<vector<double>> A; // 系数矩阵（包含常数项）
    vector<double> ans; // 解向量
    const double eps = 1e-9; // 用于比较浮点数的精度

    GaussianElimination(int size) : n(size), A(size, vector<double>(size + 1, 0)), ans(size, 0) {}

    // 读取方程组
    void readEquations() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= n; ++j) {
                cin >> A[i][j];
            }
        }
    }

    // 返回绝对值
    double Abs(double x) {
        return x < 0 ? -x : x;
    }

    // 判断两个浮点数是否相等
    bool eq(double x, double y) {
        return Abs(x - y) < eps;
    }

    // 高斯消元求解
    int solve() {
        int nwline = 0; // 当前处理的行
        for (int k = 0; k < n; ++k) {
            // 找到当前列中绝对值最大的元素
            int maxi = nwline;
            for (int i = nwline + 1; i < n; ++i) {
                if (Abs(A[i][k]) > Abs(A[maxi][k])) {
                    maxi = i;
                }
            }
            // 如果找到的主元接近0，说明此列无法消元
            if (eq(A[maxi][k], 0)) continue;
            // 交换当前行和主元行
            for (int j = 0; j < n + 1; ++j) {
                swap(A[nwline][j], A[maxi][j]);
            }
            // 对所有行进行消元操作
            for (int i = 0; i < n; ++i) {
                if (i == nwline) continue;
                double mul = A[i][k] / A[nwline][k];
                for (int j = k; j < n + 1; ++j) {
                    A[i][j] -= A[nwline][j] * mul;
                }
            }
            ++nwline;
        }
        // 如果不能找到足够的主元，说明可能无解或有无穷多解
        if (nwline < n) {
            while (nwline < n) {
                // 如果常数项不为0，说明无解
                if (!eq(A[nwline++][n], 0)) {
                    return -1; // 无解
                }
            }
            return 0; // 有无穷多解
        } else {
            // 唯一解
            for (int i = 0; i < n; ++i) {
                ans[i] = A[i][n] / A[i][i];
            }
            return 1; // 唯一解
        }
    }

    // 输出解
    void printSolution() const {
        for (int i = 0; i < n; ++i) {
            cout << fixed << setprecision(2);
            cout << "x" << i + 1 << "=" << ans[i] << "\n";
        }
    }
};

void SINGLE_TEST() {
    int n;
    cin >> n;
    GaussianElimination ge(n);
    ge.readEquations();
    int result = ge.solve();
    if (result == 1) {
        ge.printSolution(); // 输出唯一解
    } else {
        cout << result << "\n"; // -1表示无解，0表示有无穷多解
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}