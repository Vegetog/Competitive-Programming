/*
算法：树的带权重心
简介：汇总子树点权，寻找删除后各连通块点权均不超过总点权一半的顶点。
复杂度：时间 O(n)，额外空间 O(n)。
约定：输入为非空无向树，顶点从 0 开始；点权非负，总点权及加权距离和须在 i64 范围内。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
int weighted_centroid(const vector<vector<int>>& graph, const vector<i64>& weight) {
    int n = static_cast<int>(graph.size());
    assert(n > 0 && static_cast<int>(weight.size()) == n);
    vector<int> parent(n, -1), order = {0};
    vector<i64> subtree = weight;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : graph[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            order.push_back(v);
        }
    }
    for (int i = n - 1; i > 0; --i) {
        int u = order[i];
        subtree[parent[u]] += subtree[u];
    }
    i64 total = subtree[0];
    for (int u : order) {
        i64 largest = total - subtree[u];
        for (int v : graph[u]) {
            if (parent[v] == u) largest = max(largest, subtree[v]);
        }
        if (largest <= total / 2) return u;
    }
    return -1;
}

// 各边长度视为 1；重心使到所有顶点的加权距离和最小。
i64 weighted_distance_sum(const vector<vector<int>>& graph, const vector<i64>& weight, int root) {
    vector<int> dist(graph.size(), -1);
    queue<int> pending;
    dist[root] = 0;
    pending.push(root);
    i64 result = 0;
    while (!pending.empty()) {
        int u = pending.front();
        pending.pop();
        result += weight[u] * dist[u];
        for (int v : graph[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            pending.push(v);
        }
    }
    return result;
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<int>> graph = {{1}, {0, 2}, {1}};
    vector<i64> weight = {1, 3, 1}; // 普通重心令所有点权为 1
    int center = weighted_centroid(graph, weight);
    cout << center << ' ' << weighted_distance_sum(graph, weight, center) << '\n'; // 1 2
}
