/*
算法：中国剩余定理（CRT）
简介：合并两两互质模数下的同余式，求最小非负解和总模数。
复杂度：n 个同余式时间 O(n log M)，递归栈空间 O(log M)。
约定：r[i] 对应 m[i]；模数为正且两两互质，其乘积不超过 long long 上限；使用 __int128 中间运算。
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
using i128 = __int128;

// 作用：求扩展欧几里得系数；输入：非负 a、b 及引用 x、y；输出：gcd(a,b)，并写入满足 ax+by=gcd 的 x、y。
i128 exgcd(i128 a, i128 b, i128& x, i128& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 gcd = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return gcd;
}

// 作用：合并同余式；输入：余数 r、对应的两两互质正模数 m；输出：{最小非负解, 模数乘积}，空输入为 {0,1}。
pair<i64, i64> crt(const vector<i64>& r, const vector<i64>& m) {
    assert(r.size() == m.size());
    i128 prod = 1, ans = 0;
    for (i64 mod : m) {
        assert(mod > 0);
        prod *= mod;
        assert(prod <= numeric_limits<i64>::max());
    }
    for (int i = 0; i < int(m.size()); ++i) {
        i128 part = prod / m[i], inv, tmp;
        i128 gcd = exgcd(part, m[i], inv, tmp);
        assert(gcd == 1);
        inv = (inv % m[i] + m[i]) % m[i];
        i128 ri = (i128(r[i]) % m[i] + m[i]) % m[i];
        ans = (ans + ri * part * inv) % prod;
    }
    return {i64(ans), i64(prod)};
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    auto [rem, mod] = crt({2, 3, 2}, {3, 5, 7});
    cout << rem << ' ' << mod << '\n'; // 23 105，即 x = 23 + 105k
}
