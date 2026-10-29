/*
算法：可持久化线段树（主席树）
简介：每次插入复制一条值域路径，用两个前缀版本之差查询区间第 k 小。
复杂度：时间：每次插入/查询 O(log V)；空间：n 次插入 O(n log V)，V 为值域大小。
约定：原数组下标从 0 开始，查询区间 [l,r)，k 从 1 开始；值域 [lower,upper)，宽度 <= 2^31-1。
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct PersistentSegmentTree {
    struct Node {
        int left = 0, right = 0, count = 0;
    };
    int lower, upper;
    vector<Node> nodes{{}};
    vector<int> roots{0};
    PersistentSegmentTree(int low, int high) : lower(low), upper(high) {
        assert(low < high && static_cast<i64>(high) - low <= numeric_limits<int>::max());
    }
    int insert(int old, int l, int r, int value) {
        int current = nodes.size();
        nodes.push_back(nodes[old]);
        nodes[current].count++;
        if (r - l == 1) return current;
        int mid = l + (r - l) / 2;
        if (value < mid) {
            int child = insert(nodes[old].left, l, mid, value);
            nodes[current].left = child;
        } else {
            int child = insert(nodes[old].right, mid, r, value);
            nodes[current].right = child;
        }
        return current;
    }
    void append(int value) {
        assert(lower <= value && value < upper);
        roots.push_back(insert(roots.back(), lower, upper, value));
    }
    int kth(int l, int r, int k) const {
        assert(0 <= l && l < r && r < static_cast<int>(roots.size()) && 1 <= k && k <= r - l);
        int before = roots[l], after = roots[r], low = lower, high = upper;
        while (high - low > 1) {
            int count = nodes[nodes[after].left].count - nodes[nodes[before].left].count;
            int mid = low + (high - low) / 2;
            if (k <= count) {
                before = nodes[before].left;
                after = nodes[after].left;
                high = mid;
            } else {
                k -= count;
                before = nodes[before].right;
                after = nodes[after].right;
                low = mid;
            }
        }
        return low;
    }
};

// ==================== 使用示例 ====================
int main() {
    PersistentSegmentTree tree(-10, 11);
    for (int value : {5, -2, 3, 5}) tree.append(value);
    cout << tree.kth(1, 4, 2) << '\n'; // 输出：3（[-2,3,5] 的第 2 小）
}
