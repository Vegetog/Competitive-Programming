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

uint32_t maximum_xor_path(const vector<vector<pair<int, uint32_t>>>& graph) {
    if (graph.empty()) return 0;
    vector<uint32_t> distance(graph.size());
    vector<int> parent(graph.size(), -1), order{0};
    parent[0] = 0;
    for (size_t i = 0; i < order.size(); i++) {
        int u = order[i];
        for (auto [v, weight] : graph[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            distance[v] = distance[u] ^ weight;
            order.push_back(v);
        }
    }
    return maximum_xor_pair(distance);
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<pair<int, uint32_t>>> graph(3);
    graph[0].push_back({1, 3});
    graph[1].push_back({0, 3});
    graph[1].push_back({2, 5});
    graph[2].push_back({1, 5});
    cout << maximum_xor_path(graph) << '\n'; // 6
}
