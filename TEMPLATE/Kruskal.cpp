/*
算法：Kruskal 最小生成树
简介：按边权从小到大扫描，用并查集判断是否能连接两个不同连通块。
复杂度：时间 O(n+m log m)，额外空间 O(n+m)，包含边集副本。
约定：无向图顶点从 0 开始；允许负权和重边；权值总和须在 i64 范围内。
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct Edge {
    int from, to;
    i64 weight;
};

optional<i64> kruskal(int n, vector<Edge> edges) {
    vector<int> parent(n), size(n, 1);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](int u) {
        while (u != parent[u]) u = parent[u] = parent[parent[u]];
        return u;
    };
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
    i64 total = 0;
    int count = 0;
    for (auto [from, to, weight] : edges) {
        int u = find(from), v = find(to);
        if (u == v) continue;
        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        total += weight;
        ++count;
    }
    if (count != max(0, n - 1)) return nullopt;
    return total;
}

// ==================== 使用示例 ====================
int main() {
    vector<Edge> edges = {{0, 1, 5}, {0, 2, 1}, {1, 2, 2}};
    auto weight = kruskal(3, edges);
    if (weight) cout << *weight << '\n'; // 3；nullopt 表示图不连通
}
