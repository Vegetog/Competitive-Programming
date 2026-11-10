/*
算法：并查集（DSU）
简介：用路径压缩和按大小合并维护动态连通块，支持连通性与集合大小查询。
复杂度：初始化 O(n)，单次操作均摊 O(α(n))，空间 O(n)。
约定：元素从 0 开始；merge 返回本次是否合并了两个不同集合。
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
struct DSU {
    vector<int> fa, sz;

    // 作用：初始化独立集合；输入：元素个数 n；输出：含 n 个单元素集合的 DSU。
    explicit DSU(int n) : fa(n), sz(n, 1) { iota(fa.begin(), fa.end(), 0); }

    // 作用：查找并压缩路径；输入：元素 u；输出：u 所属集合的根，同时更新 fa。
    int find(int u) {
        while (u != fa[u]) u = fa[u] = fa[fa[u]];
        return u;
    }

    // 作用：判断连通；输入：元素 u、v；输出：二者是否属于同一集合。
    bool same(int u, int v) { return find(u) == find(v); }

    // 作用：合并集合；输入：元素 u、v；输出：是否发生合并，同时更新 fa、sz。
    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        fa[v] = u;
        sz[u] += sz[v];
        return true;
    }

    // 作用：查询集合大小；输入：元素 u；输出：u 所属集合的元素个数。
    int size(int u) { return sz[find(u)]; }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    DSU dsu(4);
    dsu.merge(0, 1);
    dsu.merge(1, 2);
    cout << dsu.same(0, 2) << ' ' << dsu.size(1) << '\n'; // 1 3
}
