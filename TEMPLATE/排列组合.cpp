/*
算法：排列数与组合数
简介：预处理阶乘和逆阶乘，常数时间查询模素数意义下的排列数、组合数。
复杂度：预处理 O(n + log p)，查询 O(1)，空间 O(n)。
约定：固定素数 p = 1000000007，预处理 0 <= n < p；合法查询须 n 不超过预处理上界。
*/
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

struct Comb {
    static constexpr i64 P = 1000000007;
    vector<i64> fac, ifac;

    // 作用：求模幂；输入：底数 0<=base<P、非负指数 e；输出：base^e mod P。
    static i64 qpow(i64 base, i64 e) {
        i64 res = 1;
        for (; e; e >>= 1, base = base * base % P) {
            if (e & 1) res = res * base % P;
        }
        return res;
    }
    // 作用：预处理组合数表；输入：上界 n>=0 且 n<模数；输出：填好 0..n 阶乘 fac、逆阶乘 ifac 的对象。
    explicit Comb(int n) {
        assert(n >= 0 && n < P);
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % P;
        ifac[n] = qpow(fac[n], P - 2);
        for (int i = n; i > 0; --i) ifac[i - 1] = ifac[i] * i % P;
    }
    // 作用：查询组合数 C(n,k)=n!/[k!(n-k)!]；输入：n、k，合法 n 已预处理；输出：模意义下的结果，n<0、k<0 或 k>n 时为 0。
    i64 C(int n, int k) const {
        if (n < 0 || k < 0 || k > n) return 0;
        assert(n < int(fac.size()));
        return fac[n] * ifac[k] % P * ifac[n - k] % P;
    }
    // 作用：查询排列数 A(n,k)=n!/(n-k)!；输入：n、k，合法 n 已预处理；输出：模意义下的结果，n<0、k<0 或 k>n 时为 0。
    i64 A(int n, int k) const {
        if (n < 0 || k < 0 || k > n) return 0;
        assert(n < int(fac.size()));
        return fac[n] * ifac[n - k] % P;
    }
};

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    Comb comb(10);
    cout << comb.C(5, 2) << ' ' << comb.A(5, 2) << '\n'; // 10 20
}
