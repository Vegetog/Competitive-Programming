/*
算法：二分图最大匹配（增广路）
简介：依次从左部未匹配顶点寻找增广路，翻转路径上的匹配关系。
复杂度：时间 O(LE+L+R)，空间 O(L+R+E)，L/R 为左右部点数，E 为边数。
约定：左右部各自从 0 编号；匹配对象为 -1 表示未匹配；递归深度最多 L。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
struct Matching {
    vector<vector<int>> g;
    vector<int> ml, mr, vis;
    int tim = 0;

    // 作用：初始化空二分图；输入：左部点数 n、右部点数 m；输出：初始化邻接表和未匹配状态，无返回值。
    Matching(int n, int m) : g(n), ml(n, -1), mr(m, -1), vis(m, 0) {}

    // 作用：添加二分图边；输入：左部顶点 u、右部顶点 v；输出：将边加入 g，无返回值。
    void add(int u, int v) {
        assert(0 <= u && u < static_cast<int>(g.size()));
        assert(0 <= v && v < static_cast<int>(mr.size()));
        g[u].push_back(v);
    }

    // 作用：寻找增广路；输入：左部顶点 u，顶层从未匹配点开始并递增 tim，递归沿用 tim；输出：能否增广，成功时更新 ml、mr。
    bool dfs(int u) {
        for (int v : g[u]) {
            if (vis[v] == tim) continue;
            vis[v] = tim;
            if (mr[v] == -1 || dfs(mr[v])) {
                ml[u] = v;
                mr[v] = u;
                return true;
            }
        }
        return false;
    }

    // 作用：重算最大匹配；输入：当前 g，无参数；输出：最大匹配数，并在 ml、mr 保存方案（-1 为未匹配）。
    int solve() {
        fill(ml.begin(), ml.end(), -1);
        fill(mr.begin(), mr.end(), -1);
        fill(vis.begin(), vis.end(), 0);
        tim = 0;
        int ans = 0;
        for (int u = 0; u < static_cast<int>(g.size()); ++u) {
            ++tim;
            ans += dfs(u);
        }
        return ans;
    }
};

// ==================== 使用示例 ====================
// 作用：演示二分图匹配；输入：内置三左两右图；输出：2。
int main() {
    Matching mat(3, 2);
    mat.add(0, 0);
    mat.add(0, 1);
    mat.add(1, 0);
    cout << mat.solve() << '\n'; // 2；ml / mr 保存具体方案
}
