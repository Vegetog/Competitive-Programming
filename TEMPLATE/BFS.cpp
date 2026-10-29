/*
算法：广度优先搜索（BFS）
简介：逐层遍历无权图，求起点到各顶点的最少边数。
复杂度：时间 O(n+m)，额外空间 O(n)。
约定：顶点从 0 开始；支持有向或无向图；不可达距离为 -1。
*/
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
vector<int> bfs(const vector<vector<int>>& graph, int source) {
    assert(0 <= source && source < static_cast<int>(graph.size()));
    vector<int> dist(graph.size(), -1);
    queue<int> pending;
    dist[source] = 0;
    pending.push(source);
    while (!pending.empty()) {
        int u = pending.front();
        pending.pop();
        for (int v : graph[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            pending.push(v);
        }
    }
    return dist;
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<int>> graph = {{1}, {0, 2}, {1}, {}};
    auto dist = bfs(graph, 0);
    cout << dist[2] << ' ' << dist[3] << '\n'; // 2 -1
}
