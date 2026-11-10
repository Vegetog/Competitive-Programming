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
struct XorTrie {
    vector<array<int, 2>> ch{{0, 0}};
    // 作用：插入 32 位整数；输入：无符号整数 x；输出：在 ch 中建立二进制路径，无返回值。
    void add(uint32_t x) {
        int u = 0;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (ch[u][b] == 0) {
                ch[u][b] = ch.size();
                ch.push_back({0, 0});
            }
            u = ch[u][b];
        }
    }
    // 作用：查询最大异或值；输入：无符号整数 x；输出：x 与已插入整数的最大异或值，空 Trie 返回 0。
    uint32_t qry(uint32_t x) const {
        if (ch.size() == 1) return 0;
        int u = 0;
        uint32_t ans = 0;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (ch[u][b ^ 1] != 0) {
                ans |= uint32_t{1} << i;
                b ^= 1;
            }
            u = ch[u][b];
        }
        return ans;
    }
};
// 作用：求最大异或对；输入：无符号整数数组 a；输出：不同下标两数的最大异或值，不足两项时为 0。
uint32_t xor_pair(const vector<uint32_t>& a) {
    XorTrie t;
    uint32_t ans = 0;
    for (uint32_t x : a) {
        ans = max(ans, t.qry(x));
        t.add(x);
    }
    return ans;
}

// ==================== 使用示例 ====================
// 作用：演示最大异或对；输入：3、10、5、25、2、8；输出：28。
int main() {
    cout << xor_pair({3, 10, 5, 25, 2, 8}) << '\n'; // 28
}
