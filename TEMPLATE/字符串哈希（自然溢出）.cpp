/*
算法：字符串哈希（自然溢出）
简介：预处理多项式前缀哈希，常数时间取得子串哈希。
复杂度：预处理时间/空间 O(n)，查询时间 O(1)。
约定：下标从 0 开始，get(l,r) 查询 [l,r)；uint64_t 按模 2^64 自然溢出，存在碰撞。
*/
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
struct Hash {
    static constexpr uint64_t kBase = 131;
    vector<uint64_t> h, pw;
    // 作用：预处理字符串哈希；输入：字符串 s；输出：初始化前缀哈希 h 和幂 pw，无返回值。
    explicit Hash(const string& s) : h(s.size() + 1), pw(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = h[i] * kBase + static_cast<unsigned char>(s[i]) + 1;
            pw[i + 1] = pw[i] * kBase;
        }
    }
    // 作用：查询子串哈希；输入：0<=l<=r<=|s|；输出：s[l,r) 的模 2^64 哈希，空串为 0。
    uint64_t get(int l, int r) const { return h[r] - h[l] * pw[r - l]; }
};

// ==================== 使用示例 ====================
// 作用：演示自然溢出哈希；输入：abcabc 的 [0,3) 与 [3,6)；输出：哈希相等为 1。
int main() {
    Hash h("abcabc");
    cout << (h.get(0, 3) == h.get(3, 6)) << '\n'; // 1
}
