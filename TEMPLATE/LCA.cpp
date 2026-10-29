/*
算法：最近公共祖先（重链剖分）
简介：预处理父节点、深度和重链链头，查询时让较深链头向上跳跃。
复杂度：预处理时间 O(n)，单次查询 O(log n)，空间 O(n)。
约定：输入为非空无向树，顶点从 0 开始；构造时指定根；迭代遍历避免深链递归。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
struct Lca {
    vector<int> parent, depth, heavy, top;

    explicit Lca(const vector<vector<int>>& graph, int root = 0) {
        int n = static_cast<int>(graph.size());
        assert(0 <= root && root < n);
        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        top.resize(n);
        vector<int> order = {root}, size(n, 1);
        parent[root] = root;
        for (int i = 0; i < n; ++i) {
            int u = order[i];
            for (int v : graph[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; --i) {
            int u = order[i], p = parent[u];
            size[p] += size[u];
            if (heavy[p] == -1 || size[u] > size[heavy[p]]) heavy[p] = u;
        }
        for (int u : order) {
            top[u] = u != root && heavy[parent[u]] == u ? top[parent[u]] : u;
        }
    }

    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            u = parent[top[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    int distance(int u, int v) const { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};

// ==================== 使用示例 ====================
int main() {
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
    Lca tree(graph);
    cout << tree.lca(3, 4) << ' ' << tree.distance(2, 4) << '\n'; // 1 3
}
