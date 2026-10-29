/*
算法：深度优先搜索（DFS）与子树叶子计数
简介：用显式栈遍历图；对树按遍历的逆序汇总每个子树中的叶子数量。
复杂度：时间 O(n+m)，额外空间 O(n)。
约定：顶点从 0 开始；DFS 仅访问起点可达部分；叶子计数要求输入为非空无向树。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
vector<int> dfs_order(const vector<vector<int>>& graph, int source) {
    assert(0 <= source && source < static_cast<int>(graph.size()));
    vector<int> order, stack = {source};
    vector<bool> visited(graph.size(), false);
    visited[source] = true;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        order.push_back(u);
        for (int v : graph[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            stack.push_back(v);
        }
    }
    return order;
}

vector<int> subtree_leaf_counts(const vector<vector<int>>& graph, int root = 0) {
    auto order = dfs_order(graph, root);
    vector<int> parent(graph.size(), -1), leaves(graph.size(), 0);
    parent[root] = root;
    for (int u : order) {
        for (int v : graph[u]) {
            if (v != parent[u]) parent[v] = u;
        }
    }
    reverse(order.begin(), order.end());
    for (int u : order) {
        if (leaves[u] == 0) leaves[u] = 1;
        if (u != root) leaves[parent[u]] += leaves[u];
    }
    return leaves;
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
    auto leaves = subtree_leaf_counts(graph);
    cout << leaves[0] << ' ' << leaves[1] << '\n'; // 3 2
}
