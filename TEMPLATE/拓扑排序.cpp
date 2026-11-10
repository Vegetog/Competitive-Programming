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
// 作用：求拓扑序；输入：有向图邻接表 g；输出：一个合法顶点顺序，存在环时为 nullopt，空图返回空序列。
optional<vector<int>> topo(const vector<vector<int>>& g) {
    int n = static_cast<int>(g.size());
    vector<int> deg(n, 0), ord;
    for (const auto& e : g) {
        for (int v : e) ++deg[v];
    }
    queue<int> q;
    for (int u = 0; u < n; ++u) {
        if (deg[u] == 0) q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (int v : g[u]) {
            if (--deg[v] == 0) q.push(v);
        }
    }
    if (static_cast<int>(ord.size()) != n) return nullopt;
    return ord;
}

// ==================== 使用示例 ====================
// 作用：演示拓扑排序；输入：内置四点 DAG；输出：0 1 2 3。
int main() {
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    auto ord = topo(g);
    if (ord) {
        for (int u : *ord) cout << u << ' '; // 0 1 2 3
        cout << '\n';
    }
}
