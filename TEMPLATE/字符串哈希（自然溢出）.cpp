/*
算法：字符串哈希（自然溢出）
简介：预处理多项式前缀哈希，常数时间取得子串哈希。
复杂度：预处理时间/空间 O(n)，查询时间 O(1)。
约定：下标从 0 开始，query(l,r) 查询 [l,r)；uint64_t 按模 2^64 自然溢出，存在碰撞。
*/
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
struct StringHash {
    static constexpr uint64_t kBase = 131;
    vector<uint64_t> hash, power;
    explicit StringHash(const string& s) : hash(s.size() + 1), power(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) {
            hash[i + 1] = hash[i] * kBase + static_cast<unsigned char>(s[i]) + 1;
            power[i + 1] = power[i] * kBase;
        }
    }
    uint64_t query(int left, int right) const {
        return hash[right] - hash[left] * power[right - left];
    }
};

// ==================== 使用示例 ====================
int main() {
    StringHash hash("abcabc");
    cout << (hash.query(0, 3) == hash.query(3, 6)) << '\n'; // 1
}
