#include<bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int,2>;
using namespace std;
const ll INF = 2E18+10;
#ifdef __clang__
    template<typename T>
    inline int my_lg(T n) {
        return (n > 0) ? static_cast<int>(log2(n)) : -1;
    }
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
    #define COUT(ITEM) std::cout<<#ITEM<<"="<<ITEM<<'\n';
    #define CERR(ITEM) std::cerr<<#ITEM<<"="<<ITEM<<'\n';
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y; }};
const int N = 2E6 + 10;
struct Matrix {
    static const int MOD = 1E9 + 7;

    int rows, cols;
    vector<vector<int>> A;

    Matrix(int rows, int cols) { Init(rows, cols); }

    void Init(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        A.assign(rows + 1, vector<int>(cols + 1, 0));  // 下标从1开始
    }

    Matrix operator+(const Matrix &ma) const {
        assert(rows == ma.rows && cols == ma.cols);
        Matrix res(rows, cols);
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                res.A[i][j] = A[i][j] + ma.A[i][j];
                if (res.A[i][j] >= MOD) res.A[i][j] -= MOD;
            }
        }
        return res;
    }

    Matrix operator-(const Matrix &ma) const {
        assert(rows == ma.rows && cols == ma.cols);
        Matrix res(rows, cols);
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                res.A[i][j] = A[i][j] - ma.A[i][j];
                if (res.A[i][j] < 0) res.A[i][j] += MOD;
            }
        }
        return res;
    }

    Matrix operator*(const Matrix &ma) const {
        assert(cols == ma.rows);
        Matrix res(rows, ma.cols);
        for (int i = 1; i <= rows; ++i) {
            for (int t = 1; t <= cols; ++t) {
                for (int j = 1, T = A[i][t]; j <= ma.cols; ++j) {
                    res.A[i][j] += 1LL * T * ma.A[t][j] % MOD;
                    if (res.A[i][j] >= MOD) res.A[i][j] -= MOD;
                }
            }
        }
        return res;
    }

    Matrix pow(ll n) const {
        assert(rows == cols);
        Matrix res(rows, cols), x(rows, cols);
        for (int i = 1; i <= rows; ++i) {
            res.A[i][i] = 1;
            for (int j = 1; j <= cols; ++j) x.A[i][j] = A[i][j];
        }
        while (n) {
            if (n & 1) res = res * x;
            x = x * x;
            n >>= 1;
        }
        return res;
    }

    void Show() const {
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) cout << A[i][j] << " \n"[j == cols];
        }
    }
};
void SINGLE_TEST()
{   
    int n;cin>>n;
    Matrix a(2);
    a.A[1][1] = 1;
    a.A[1][2] = 1;
    a.A[2][1] = 1;
    a.A[2][2] = 0;
    a = a.pow(n);
    cout<<a.A[1][2]<<"\n";
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);

    int SAMPLES = 1;
	// cin>>SAMPLES;
    while(SAMPLES--) SINGLE_TEST();
}
