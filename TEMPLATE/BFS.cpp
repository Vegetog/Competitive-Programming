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
// 作用：求无权最短路；输入：邻接表 g、起点 s；输出：各点到 s 的最少边数，不可达为 -1。
vector<int> bfs(const vector<vector<int>>& g, int s) {
    assert(0 <= s && s < static_cast<int>(g.size()));
    vector<int> d(g.size(), -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (d[v] != -1) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return d;
}

// ==================== 使用示例 ====================
// 作用：演示 BFS；输入：内置四点图；输出：2 -1。
int main() {
    vector<vector<int>> g = {{1}, {0, 2}, {1}, {}};
    auto d = bfs(g, 0);
    cout << d[2] << ' ' << d[3] << '\n'; // 2 -1
}
