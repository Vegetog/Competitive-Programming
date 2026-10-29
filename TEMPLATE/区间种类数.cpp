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
vector<int> count_distinct(const vector<i64>& a, const vector<pair<int, int>>& queries) {
    int n = a.size(), q = queries.size();
    vector<int> tree(n + 1), order(q), answer(q);
    auto add = [&](int pos, int value) {
        for (int i = pos + 1; i <= n; i += i & -i) tree[i] += value;
    };
    auto prefix_sum = [&](int end) {
        int result = 0;
        for (int i = end; i; i -= i & -i) result += tree[i];
        return result;
    };
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(),
         [&](int x, int y) { return queries[x].second < queries[y].second; });
    unordered_map<i64, int> last;
    int end = 0;
    for (int id : order) {
        auto [l, r] = queries[id];
        assert(0 <= l && l <= r && r <= n);
        while (end < r) {
            if (last.count(a[end])) add(last[a[end]], -1);
            last[a[end]] = end;
            add(end++, 1);
        }
        answer[id] = prefix_sum(r) - prefix_sum(l);
    }
    return answer;
}

// ==================== 使用示例 ====================
int main() {
    auto answer = count_distinct({1, 2, 1, 3, 2}, {{0, 3}, {1, 5}, {2, 2}});
    for (int value : answer) cout << value << ' '; // 输出：2 3 0
    cout << '\n';
}
