/*
算法：深度优先搜索（DFS）与子树叶子计数
简介：用显式栈遍历图；对树按遍历的逆序汇总每个子树中的叶子数量。
复杂度：时间 O(n+m)，额外空间 O(n)。
约定：顶点从 0 开始；DFS 仅访问起点可达部分；叶子计数要求输入为非空无向树。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
// 作用：按深度优先顺序遍历；输入：邻接表 g、起点 s；输出：s 可达顶点的访问序列。
vector<int> dfs(const vector<vector<int>>& g, int s) {
    assert(0 <= s && s < static_cast<int>(g.size()));
    vector<int> ord, st = {s};
    vector<bool> vis(g.size(), false);
    vis[s] = true;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        ord.push_back(u);
        for (int v : g[u]) {
            if (vis[v]) continue;
            vis[v] = true;
            st.push_back(v);
        }
    }
    return ord;
}

// 作用：统计各子树叶子数；输入：非空无向树 g、根 rt；输出：以 rt 为根时各子树的叶子数。
vector<int> leaf_cnt(const vector<vector<int>>& g, int rt = 0) {
    auto ord = dfs(g, rt);
    vector<int> fa(g.size(), -1), cnt(g.size(), 0);
    fa[rt] = rt;
    for (int u : ord) {
        for (int v : g[u]) {
            if (v != fa[u]) fa[v] = u;
        }
    }
    reverse(ord.begin(), ord.end());
    for (int u : ord) {
        if (cnt[u] == 0) cnt[u] = 1;
        if (u != rt) cnt[fa[u]] += cnt[u];
    }
    return cnt;
}

// ==================== 使用示例 ====================
// 作用：演示子树叶子计数；输入：内置五点树；输出：3 2。
int main() {
    vector<vector<int>> g = {{1, 2}, {0, 3, 4}, {0}, {1}, {1}};
    auto cnt = leaf_cnt(g);
    cout << cnt[0] << ' ' << cnt[1] << '\n'; // 3 2
}
