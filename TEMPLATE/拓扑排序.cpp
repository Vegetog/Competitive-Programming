/*
算法：拓扑排序（Kahn）
简介：不断移除入度为 0 的顶点，得到有向无环图的合法顶点顺序。
复杂度：时间 O(n+m)，额外空间 O(n)。
约定：有向图顶点从 0 开始；返回 nullopt 表示存在环，空图返回空序列。
*/
#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
optional<vector<int>> topological_sort(const vector<vector<int>>& graph) {
    int n = static_cast<int>(graph.size());
    vector<int> indegree(n, 0), order;
    for (const auto& edges : graph) {
        for (int v : edges) ++indegree[v];
    }
    queue<int> pending;
    for (int u = 0; u < n; ++u) {
        if (indegree[u] == 0) pending.push(u);
    }
    while (!pending.empty()) {
        int u = pending.front();
        pending.pop();
        order.push_back(u);
        for (int v : graph[u]) {
            if (--indegree[v] == 0) pending.push(v);
        }
    }
    if (static_cast<int>(order.size()) != n) return nullopt;
    return order;
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
    auto order = topological_sort(graph);
    if (order) {
        for (int u : *order) cout << u << ' '; // 0 1 2 3
        cout << '\n';
    }
}
