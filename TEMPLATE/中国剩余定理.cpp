/*
算法：中国剩余定理（CRT）
简介：合并两两互质模数下的同余式，求最小非负解和总模数。
复杂度：n 个同余式时间 O(n log M)，递归栈空间 O(log M)。
约定：residues[i] 对应 moduli[i]；模数为正且两两互质，其乘积不超过 long long 上限；使用 __int128 中间运算。
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

i128 extended_gcd(i128 a, i128 b, i128& x, i128& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 gcd = extended_gcd(b, a % b, y, x);
    y -= a / b * x;
    return gcd;
}

pair<i64, i64> chinese_remainder(const vector<i64>& residues, const vector<i64>& moduli) {
    assert(residues.size() == moduli.size());
    i128 product = 1, answer = 0;
    for (i64 modulus : moduli) {
        assert(modulus > 0);
        product *= modulus;
        assert(product <= numeric_limits<i64>::max());
    }
    for (int i = 0; i < int(moduli.size()); ++i) {
        i128 part = product / moduli[i], inverse, unused;
        i128 gcd = extended_gcd(part, moduli[i], inverse, unused);
        assert(gcd == 1);
        inverse = (inverse % moduli[i] + moduli[i]) % moduli[i];
        i128 residue = (i128(residues[i]) % moduli[i] + moduli[i]) % moduli[i];
        answer = (answer + residue * part * inverse) % product;
    }
    return {i64(answer), i64(product)};
}

// ==================== 使用示例 ====================
int main() {
    auto [remainder, modulus] = chinese_remainder({2, 3, 2}, {3, 5, 7});
    cout << remainder << ' ' << modulus << '\n'; // 23 105，即 x = 23 + 105k
}
