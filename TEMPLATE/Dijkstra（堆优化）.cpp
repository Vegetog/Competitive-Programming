/*
算法：Dijkstra 最短路（堆优化）
简介：用小根堆选择待扩展顶点，适合邻接表表示的稀疏图。
复杂度：时间 O((n+m) log(n+m))，额外空间 O(n+m)。
约定：顶点从 0 开始；邻接项为 {终点, 边权}，边权非负且有限距离小于 kInf。
*/
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
constexpr i64 kInf = numeric_limits<i64>::max() / 4;

vector<i64> dijkstra_heap(const vector<vector<pair<int, i64>>>& graph, int source) {
    int n = static_cast<int>(graph.size());
    assert(0 <= source && source < n);
    vector<i64> dist(n, kInf);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> heap;
    dist[source] = 0;
    heap.push({0, source});
    while (!heap.empty()) {
        auto [distance, u] = heap.top();
        heap.pop();
        if (distance != dist[u]) continue;
        for (auto [v, weight] : graph[u]) {
            if (weight < kInf && distance <= kInf - weight && dist[v] > distance + weight) {
                dist[v] = distance + weight;
                heap.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ==================== 使用示例 ====================
int main() {
    vector<vector<pair<int, i64>>> graph(4);
    graph[2] = {{0, 5}, {1, 1}};
    graph[1] = {{0, 2}};
    auto dist = dijkstra_heap(graph, 2);
    cout << dist[0] << ' ' << (dist[3] == kInf) << '\n'; // 3 1
}
