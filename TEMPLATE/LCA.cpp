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
struct LCA {
    vector<int> fa, dep, son, top;

    // 作用：预处理重链信息；输入：非空无向树 g、根 rt；输出：初始化 fa、dep、son、top，无返回值。
    explicit LCA(const vector<vector<int>>& g, int rt = 0) {
        int n = static_cast<int>(g.size());
        assert(0 <= rt && rt < n);
        fa.assign(n, -1);
        dep.assign(n, 0);
        son.assign(n, -1);
        top.resize(n);
        vector<int> ord = {rt}, sz(n, 1);
        fa[rt] = rt;
        for (int i = 0; i < n; ++i) {
            int u = ord[i];
            for (int v : g[u]) {
                if (v == fa[u]) continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                ord.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; --i) {
            int u = ord[i], p = fa[u];
            sz[p] += sz[u];
            if (son[p] == -1 || sz[u] > sz[son[p]]) son[p] = u;
        }
        for (int u : ord) {
            top[u] = u != rt && son[fa[u]] == u ? top[fa[u]] : u;
        }
    }

    // 作用：查询最近公共祖先；输入：顶点 u、v；输出：以构造时 rt 为根的最近公共祖先编号。
    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // 作用：查询树上距离；输入：顶点 u、v；输出：两点唯一路径的边数。
    int dist(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
};

// ==================== 使用示例 ====================
// 作用：演示 LCA 与距离；输入：内置五点树；输出：1 3。
int main() {
    vector<vector<int>> g = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
    LCA t(g);
    cout << t.lca(3, 4) << ' ' << t.dist(2, 4) << '\n'; // 1 3
}
