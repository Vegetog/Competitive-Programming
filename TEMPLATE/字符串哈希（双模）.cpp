/*
算法：字符串双哈希
简介：使用两组模数与基数，降低子串哈希碰撞概率。
复杂度：预处理时间/空间 O(n)，查询与比较时间 O(1)。
约定：下标从 0 开始，query(l,r) 查询 [l,r)；相同哈希仍可能碰撞，严格判等需校验原串。
*/
#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
struct DoubleHash {
    static constexpr array<i64, 2> kBase = {29, 31};
    static constexpr array<i64, 2> kMod = {1000000009, 998244353};
    array<vector<i64>, 2> hash, power;
    explicit DoubleHash(const string& s) {
        for (int k = 0; k < 2; k++) {
            hash[k].assign(s.size() + 1, 0);
            power[k].assign(s.size() + 1, 1);
            for (size_t i = 0; i < s.size(); i++) {
                power[k][i + 1] = power[k][i] * kBase[k] % kMod[k];
                hash[k][i + 1] =
                    (hash[k][i] * kBase[k] + static_cast<unsigned char>(s[i]) + 1) % kMod[k];
            }
        }
    }
    array<i64, 2> query(int left, int right) const {
        array<i64, 2> result;
        for (int k = 0; k < 2; k++) {
            result[k] = (hash[k][right] - hash[k][left] * power[k][right - left]) % kMod[k];
            if (result[k] < 0) result[k] += kMod[k];
        }
        return result;
    }
};
bool same_substring(const DoubleHash& a, int left_a, int right_a, const DoubleHash& b, int left_b,
                    int right_b) {
    return right_a - left_a == right_b - left_b &&
           a.query(left_a, right_a) == b.query(left_b, right_b);
}

// ==================== 使用示例 ====================
int main() {
    DoubleHash a("abcabc"), b("abc");
    cout << same_substring(a, 3, 6, b, 0, 3) << '\n'; // 1
}
