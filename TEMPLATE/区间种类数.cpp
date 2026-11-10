/*
算法：离线区间种类数
简介：按右端点处理查询，树状数组仅保留每种值最后出现的位置。
复杂度：时间：期望 O((n+q) log(n+q))；空间：O(n+q)。
约定：数组下标从 0 开始；查询区间为 [l,r)，允许空区间；结果按查询输入顺序返回。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
// 作用：离线统计不同值数；输入：数组 a、查询区间列表 qs（[l,r)）；输出：按原查询顺序排列的种类数。
vector<int> distinct(const vector<i64>& a, const vector<pair<int, int>>& qs) {
    int n = a.size(), q = qs.size();
    vector<int> t(n + 1), ord(q), ans(q);
    // 作用：更新最后出现位置的频次；输入：下标 p、增量 v；输出：修改树状数组 t，无返回值。
    auto add = [&](int p, int v) {
        for (int i = p + 1; i <= n; i += i & -i) t[i] += v;
    };
    // 作用：查询有效位置数；输入：前缀右端点 r0；输出：[0,r0) 的树状数组频次和。
    auto sum = [&](int r0) {
        int res = 0;
        for (int i = r0; i; i -= i & -i) res += t[i];
        return res;
    };
    iota(ord.begin(), ord.end(), 0);
    // 作用：按查询右端点排序；输入：查询编号 x、y；输出：qs[x] 的右端点是否更小。
    sort(ord.begin(), ord.end(), [&](int x, int y) { return qs[x].second < qs[y].second; });
    unordered_map<i64, int> last;
    int r0 = 0;
    for (int id : ord) {
        auto [l, r] = qs[id];
        assert(0 <= l && l <= r && r <= n);
        while (r0 < r) {
            if (last.count(a[r0])) add(last[a[r0]], -1);
            last[a[r0]] = r0;
            add(r0++, 1);
        }
        ans[id] = sum(r) - sum(l);
    }
    return ans;
}

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    auto ans = distinct({1, 2, 1, 3, 2}, {{0, 3}, {1, 5}, {2, 2}});
    for (int v : ans) cout << v << ' '; // 输出：2 3 0
    cout << '\n';
}
