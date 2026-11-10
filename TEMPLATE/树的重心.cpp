/*
算法：树的带权重心
简介：汇总子树点权，寻找删除后各连通块点权均不超过总点权一半的顶点。
复杂度：时间 O(n)，额外空间 O(n)。
约定：输入为非空无向树，顶点从 0 开始；点权非负，总点权及加权距离和须在 i64 范围内。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
// 作用：求带权重心；输入：非空无向树 g、各点非负权 w；输出：一个重心编号，删除后各块点权不超过总权一半。
int centroid(const vector<vector<int>>& g, const vector<i64>& w) {
    int n = static_cast<int>(g.size());
    assert(n > 0 && static_cast<int>(w.size()) == n);
    vector<int> fa(n, -1), ord = {0};
    vector<i64> sum = w;
    for (int i = 0; i < n; ++i) {
        int u = ord[i];
        for (int v : g[u]) {
            if (v == fa[u]) continue;
            fa[v] = u;
            ord.push_back(v);
        }
    }
    for (int i = n - 1; i > 0; --i) {
        int u = ord[i];
        sum[fa[u]] += sum[u];
    }
    i64 tot = sum[0];
    for (int u : ord) {
        i64 mx = tot - sum[u];
        for (int v : g[u]) {
            if (fa[v] == u) mx = max(mx, sum[v]);
        }
        if (mx <= tot / 2) return u;
    }
    return -1;
}

// 各边长度视为 1；重心使到所有顶点的加权距离和最小。
// 作用：求加权距离和；输入：无向树 g、点权 w、起点 rt，各边长度为 1；输出：所有 w[u]*dist(rt,u) 之和。
i64 dist_sum(const vector<vector<int>>& g, const vector<i64>& w, int rt) {
    vector<int> dist(g.size(), -1);
    queue<int> q;
    dist[rt] = 0;
    q.push(rt);
    i64 ans = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans += w[u] * dist[u];
        for (int v : g[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return ans;
}

// ==================== 使用示例 ====================
// 作用：演示带权重心；输入：三点链，点权 1、3、1；输出：重心 1、加权距离和 2。
int main() {
    vector<vector<int>> g = {{1}, {0, 2}, {1}};
    vector<i64> w = {1, 3, 1}; // 普通重心令所有点权为 1
    int c = centroid(g, w);
    cout << c << ' ' << dist_sum(g, w, c) << '\n'; // 1 2
}
