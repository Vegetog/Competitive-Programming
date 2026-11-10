/*
算法：数位 DP（区分前导零）
简介：统计相邻数字之差至少为 2 的正整数，以 started 状态区分前导零。
复杂度：时间 O(D × 10²)，空间 O(D × 10)，D 为十进制位数。
约定：windy(n) 统计 [1,n]，n <= 0 时返回 0；前导零不参与相邻数字比较。
*/
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
// 作用：统计相邻数位之差至少为 2 的正整数；输入：上界 x；输出：[1,x] 内符合条件的个数，x <= 0 时为 0。
i64 windy(i64 x) {
    if (x <= 0) return 0;
    string s = to_string(x);
    int n = s.size();
    vector<vector<i64>> dp(n, vector<i64>(10, -1));
    // 作用：补全后续数位；输入：位置 pos、上一位 pre、是否贴上界 tight、是否已有非零位 started；输出：合法补全数，缓存非受限且已开始的状态。
    function<i64(int, int, bool, bool)> dfs = [&](int pos, int pre, bool tight,
                                                  bool started) -> i64 {
        if (pos == n) return started;
        if (!tight && started && dp[pos][pre] != -1) return dp[pos][pre];
        int up = tight ? s[pos] - '0' : 9;
        i64 ans = 0;
        for (int d = 0; d <= up; d++) {
            bool nt = tight && d == up;
            if (!started && d == 0)
                ans += dfs(pos + 1, 0, nt, false);
            else if (!started || abs(d - pre) >= 2) {
                ans += dfs(pos + 1, d, nt, true);
            }
        }
        if (!tight && started) dp[pos][pre] = ans;
        return ans;
    };
    return dfs(0, 0, true, false);
}

// ==================== 使用示例 ====================
// 作用：演示前缀及区间计数；输入：无，使用上界 20、100、9；输出：17 和区间 [10,100] 的计数 64。
int main() {
    cout << windy(20) << '\n';             // 17
    cout << windy(100) - windy(9) << '\n'; // 查询 [10,100]，结果 64
}
