/*
算法：可持久化线段树（主席树）
简介：每次插入复制一条值域路径，用两个前缀版本之差查询区间第 k 小。
复杂度：时间：每次插入/查询 O(log V)；空间：n 次插入 O(n log V)，V 为值域大小。
约定：原数组下标从 0 开始，查询区间 [l,r)，k 从 1 开始；值域 [lo,hi)，宽度 <= 2^31-1。
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct PST {
    struct Node {
        int ls = 0, rs = 0, cnt = 0;
    };
    int lo, hi;
    vector<Node> t{{}};
    vector<int> rt{0};
    // 作用：初始化前缀版本；输入：值域 [l0,r0)，宽度不超过 INT_MAX；输出：仅含空版本的 PST。
    PST(int l0, int r0) : lo(l0), hi(r0) {
        assert(l0 < r0 && static_cast<i64>(r0) - l0 <= numeric_limits<int>::max());
    }
    // 作用：复制路径并插入；输入：旧根 old、值域 [l,r)、值 x；输出：新根编号，同时向 t 追加节点。
    int ins(int old, int l, int r, int x) {
        int p = t.size();
        t.push_back(t[old]);
        t[p].cnt++;
        if (r - l == 1) return p;
        int mid = l + (r - l) / 2;
        if (x < mid) {
            int c = ins(t[old].ls, l, mid, x);
            t[p].ls = c;
        } else {
            int c = ins(t[old].rs, mid, r, x);
            t[p].rs = c;
        }
        return p;
    }
    // 作用：追加数组元素；输入：值域内的 x；输出：追加包含 x 的新前缀根到 rt，无返回值。
    void add(int x) {
        assert(lo <= x && x < hi);
        rt.push_back(ins(rt.back(), lo, hi, x));
    }
    // 作用：查询区间第 k 小；输入：原数组区间 [l,r)、1 <= k <= r-l；输出：第 k 小的值。
    int kth(int l, int r, int k) const {
        assert(0 <= l && l < r && r < static_cast<int>(rt.size()) && 1 <= k && k <= r - l);
        int u = rt[l], v = rt[r], l0 = lo, r0 = hi;
        while (r0 - l0 > 1) {
            int cnt = t[t[v].ls].cnt - t[t[u].ls].cnt;
            int mid = l0 + (r0 - l0) / 2;
            if (k <= cnt) {
                u = t[u].ls;
                v = t[v].ls;
                r0 = mid;
            } else {
                k -= cnt;
                u = t[u].rs;
                v = t[v].rs;
                l0 = mid;
            }
        }
        return l0;
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    PST s(-10, 11);
    for (int x : {5, -2, 3, 5}) s.add(x);
    cout << s.kth(1, 4, 2) << '\n'; // 输出：3（[-2,3,5] 的第 2 小）
}
