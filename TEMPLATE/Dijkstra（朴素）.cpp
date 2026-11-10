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

// 作用：求非负权最短路；输入：邻接矩阵 g、起点 s，无边为 kInf；输出：各点最短距离，不可达为 kInf。
vector<i64> dijkstra(const vector<vector<i64>>& g, int s) {
    int n = static_cast<int>(g.size());
    assert(0 <= s && s < n);
    vector<i64> dis(n, kInf);
    vector<bool> vis(n, false);
    dis[s] = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (!vis[v] && (u == -1 || dis[v] < dis[u])) u = v;
        }
        if (u == -1 || dis[u] == kInf) break;
        vis[u] = true;
        for (int v = 0; v < n; ++v) {
            if (g[u][v] < kInf && dis[u] <= kInf - g[u][v]) {
                dis[v] = min(dis[v], dis[u] + g[u][v]);
            }
        }
    }
    return dis;
}

// ==================== 使用示例 ====================
// 作用：演示朴素最短路；输入：内置四点图、起点 0；输出：3 1，1 表示点 3 不可达。
int main() {
    vector<vector<i64>> g(4, vector<i64>(4, kInf));
    g[0][1] = 5;
    g[0][2] = 1;
    g[2][1] = 2;
    auto dis = dijkstra(g, 0);
    cout << dis[1] << ' ' << (dis[3] == kInf) << '\n'; // 3 1
}
