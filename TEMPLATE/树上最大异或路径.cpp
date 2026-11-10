/*
算法：树上最大异或路径
简介：先求各点到根的异或值，再用 01 Trie 求这些值的最大异或对。
复杂度：时间 O(32n)，空间 O(32n)。
约定：输入为连通无向树，顶点从 0 开始，边权为 uint32_t；空树返回 0。
*/
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <utility>
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

// 作用：求树上最大路径异或和；输入：无向树邻接表 g（终点、uint32_t 边权）；输出：任意两点路径的最大异或和，空树为 0。
uint32_t xor_path(const vector<vector<pair<int, uint32_t>>>& g) {
    if (g.empty()) return 0;
    vector<uint32_t> dis(g.size());
    vector<int> fa(g.size(), -1), ord{0};
    fa[0] = 0;
    for (size_t i = 0; i < ord.size(); i++) {
        int u = ord[i];
        for (auto [v, w] : g[u]) {
            if (v == fa[u]) continue;
            fa[v] = u;
            dis[v] = dis[u] ^ w;
            ord.push_back(v);
        }
    }
    return xor_pair(dis);
}

// ==================== 使用示例 ====================
// 作用：演示树上最大异或路径；输入：三点链，两边权为 3、5；输出：6。
int main() {
    vector<vector<pair<int, uint32_t>>> g(3);
    g[0].push_back({1, 3});
    g[1].push_back({0, 3});
    g[1].push_back({2, 5});
    g[2].push_back({1, 5});
    cout << xor_path(g) << '\n'; // 6
}
