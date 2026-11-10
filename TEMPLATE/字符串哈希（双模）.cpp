/*
算法：字符串双哈希
简介：使用两组模数与基数，降低子串哈希碰撞概率。
复杂度：预处理时间/空间 O(n)，查询与比较时间 O(1)。
约定：下标从 0 开始，get(l,r) 查询 [l,r)；相同哈希仍可能碰撞，严格判等需校验原串。
*/
#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
struct Hash2 {
    static constexpr array<i64, 2> kBase = {29, 31};
    static constexpr array<i64, 2> kMod = {1000000009, 998244353};
    array<vector<i64>, 2> h, pw;
    // 作用：预处理双模哈希；输入：字符串 s；输出：初始化两组前缀哈希 h 和幂 pw，无返回值。
    explicit Hash2(const string& s) {
        for (int k = 0; k < 2; k++) {
            h[k].assign(s.size() + 1, 0);
            pw[k].assign(s.size() + 1, 1);
            for (size_t i = 0; i < s.size(); i++) {
                pw[k][i + 1] = pw[k][i] * kBase[k] % kMod[k];
                h[k][i + 1] = (h[k][i] * kBase[k] + static_cast<unsigned char>(s[i]) + 1) % kMod[k];
            }
        }
    }
    // 作用：查询子串双哈希；输入：0<=l<=r<=|s|；输出：s[l,r) 的两组哈希，空串均为 0。
    array<i64, 2> get(int l, int r) const {
        array<i64, 2> res;
        for (int k = 0; k < 2; k++) {
            res[k] = (h[k][r] - h[k][l] * pw[k][r - l]) % kMod[k];
            if (res[k] < 0) res[k] += kMod[k];
        }
        return res;
    }
};
// 作用：比较子串哈希；输入：哈希对象 a、b 及各自区间 [l1,r1)、[l2,r2)；输出：长度与双哈希是否均相等。
bool same(const Hash2& a, int l1, int r1, const Hash2& b, int l2, int r2) {
    return r1 - l1 == r2 - l2 && a.get(l1, r1) == b.get(l2, r2);
}

// ==================== 使用示例 ====================
// 作用：演示双模哈希比较；输入：abcabc 的 [3,6) 与 abc 的 [0,3)；输出：1。
int main() {
    Hash2 a("abcabc"), b("abc");
    cout << same(a, 3, 6, b, 0, 3) << '\n'; // 1
}
