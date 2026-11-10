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

// 作用：求非负权最短路；输入：邻接表 g（终点、边权）、起点 s；输出：各点最短距离，不可达为 kInf。
vector<i64> dijkstra(const vector<vector<pair<int, i64>>>& g, int s) {
    int n = static_cast<int>(g.size());
    assert(0 <= s && s < n);
    vector<i64> dis(n, kInf);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> q;
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d != dis[u]) continue;
        for (auto [v, w] : g[u]) {
            if (w < kInf && d <= kInf - w && dis[v] > d + w) {
                dis[v] = d + w;
                q.push({dis[v], v});
            }
        }
    }
    return dis;
}

// ==================== 使用示例 ====================
// 作用：演示堆优化最短路；输入：内置四点图、起点 2；输出：3 1，1 表示点 3 不可达。
int main() {
    vector<vector<pair<int, i64>>> g(4);
    g[2] = {{0, 5}, {1, 1}};
    g[1] = {{0, 2}};
    auto dis = dijkstra(g, 2);
    cout << dis[0] << ' ' << (dis[3] == kInf) << '\n'; // 3 1
}
