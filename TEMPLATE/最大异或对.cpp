/*
算法：最大异或对（01 Trie）
简介：按二进制位建立字典树，每一位优先走与查询数相反的分支。
复杂度：时间 O(32n)，空间 O(32n)。
约定：使用 32 位无符号整数；空数组或只有一个数时返回 0。
*/
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
struct BinaryTrie {
    vector<array<int, 2>> next{{0, 0}};
    void insert(uint32_t value) {
        int node = 0;
        for (int bit = 31; bit >= 0; bit--) {
            int digit = (value >> bit) & 1;
            if (next[node][digit] == 0) {
                next[node][digit] = next.size();
                next.push_back({0, 0});
            }
            node = next[node][digit];
        }
    }
    uint32_t max_xor(uint32_t value) const {
        if (next.size() == 1) return 0;
        int node = 0;
        uint32_t result = 0;
        for (int bit = 31; bit >= 0; bit--) {
            int digit = (value >> bit) & 1;
            if (next[node][digit ^ 1] != 0) {
                result |= uint32_t{1} << bit;
                digit ^= 1;
            }
            node = next[node][digit];
        }
        return result;
    }
};
uint32_t maximum_xor_pair(const vector<uint32_t>& values) {
    BinaryTrie trie;
    uint32_t result = 0;
    for (uint32_t value : values) {
        result = max(result, trie.max_xor(value));
        trie.insert(value);
    }
    return result;
}

// ==================== 使用示例 ====================
int main() {
    cout << maximum_xor_pair({3, 10, 5, 25, 2, 8}) << '\n'; // 28
}
