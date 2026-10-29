/*
算法：Dijkstra 最短路（朴素）
简介：每次确定当前距离最小的顶点，适合用邻接矩阵表示的稠密图。
复杂度：时间 O(n²)，额外空间 O(n)。
约定：顶点从 0 开始；边权非负；无边及不可达距离为 kInf，有限距离须小于 kInf。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
constexpr i64 kInf = numeric_limits<i64>::max() / 4;

vector<i64> dijkstra_dense(const vector<vector<i64>>& graph, int source) {
    int n = static_cast<int>(graph.size());
    assert(0 <= source && source < n);
    vector<i64> dist(n, kInf);
    vector<bool> visited(n, false);
    dist[source] = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) u = v;
        }
        if (u == -1 || dist[u] == kInf) break;
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < kInf && dist[u] <= kInf - graph[u][v]) {
                dist[v] = min(dist[v], dist[u] + graph[u][v]);
            }
        }
    }
    return dist;
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<i64>> graph(4, vector<i64>(4, kInf));
    graph[0][1] = 5;
    graph[0][2] = 1;
    graph[2][1] = 2;
    auto dist = dijkstra_dense(graph, 0);
    cout << dist[1] << ' ' << (dist[3] == kInf) << '\n'; // 3 1
}
