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
struct DisjointSet {
    vector<int> parent, size;

    explicit DisjointSet(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }

    int find(int u) {
        while (u != parent[u]) u = parent[u] = parent[parent[u]];
        return u;
    }

    bool same(int u, int v) { return find(u) == find(v); }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        return true;
    }

    int component_size(int u) { return size[find(u)]; }
};

// ==================== 使用示例 ====================
int main() {
    DisjointSet dsu(4);
    dsu.merge(0, 1);
    dsu.merge(1, 2);
    cout << dsu.same(0, 2) << ' ' << dsu.component_size(1) << '\n'; // 1 3
}
