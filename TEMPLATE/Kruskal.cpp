/*
算法：Kruskal 最小生成树
简介：按边权从小到大扫描，用并查集判断是否能连接两个不同连通块。
复杂度：时间 O(n+m log m)，额外空间 O(n+m)，包含边集副本。
约定：无向图顶点从 0 开始；允许负权和重边；权值总和须在 i64 范围内。
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct Edge {
    int a, b;
    i64 w;
};

// 作用：求最小生成树；输入：顶点数 n、无向边集 e；输出：最小总边权，无法连通时为 nullopt。
optional<i64> kruskal(int n, vector<Edge> e) {
    vector<int> fa(n), sz(n, 1);
    iota(fa.begin(), fa.end(), 0);
    // 作用：查找并压缩路径；输入：顶点 u；输出：所在集合的根，同时更新 fa。
    auto find = [&](int u) {
        while (u != fa[u]) u = fa[u] = fa[fa[u]];
        return u;
    };
    // 作用：按边权比较；输入：边 a、b；输出：a.w < b.w，用于升序排序。
    sort(e.begin(), e.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    i64 ans = 0;
    int cnt = 0;
    for (auto [a, b, w] : e) {
        int u = find(a), v = find(b);
        if (u == v) continue;
        if (sz[u] < sz[v]) swap(u, v);
        fa[v] = u;
        sz[u] += sz[v];
        ans += w;
        ++cnt;
    }
    if (cnt != max(0, n - 1)) return nullopt;
    return ans;
}

// ==================== 使用示例 ====================
// 作用：演示最小生成树；输入：内置三点图；输出：3。
int main() {
    vector<Edge> e = {{0, 1, 5}, {0, 2, 1}, {1, 2, 2}};
    auto w = kruskal(3, e);
    if (w) cout << *w << '\n'; // 3；nullopt 表示图不连通
}
