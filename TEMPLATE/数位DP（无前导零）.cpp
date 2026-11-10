/*
算法：数位 DP（无需前导零状态）
简介：枚举数位和，统计能被自身数位和整除的正整数；前导零不改变数位和与余数。
复杂度：时间 O(D × (9D)³ × 10)，空间 O(D × (9D)²)。
约定：harshad(n) 统计 [1,n]，n <= 0 时返回 0；不计整数 0。
*/
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
// 作用：统计能被自身数位和整除的正整数；输入：上界 x；输出：[1,x] 内符合条件的个数，x <= 0 时为 0。
i64 harshad(i64 x) {
    if (x <= 0) return 0;
    string s = to_string(x);
    int n = s.size();
    i64 ans = 0;
    for (int tar = 1; tar <= 9 * n; tar++) {
        vector dp(n, vector(tar + 1, vector<i64>(tar, -1)));
        // 作用：统计数位和为 tar 的补全方案；输入：位置 pos、当前数位和 sum、前缀模 tar 的余数 rem、上界限制 tight；输出：合法补全数，并缓存非受限状态。
        function<i64(int, int, int, bool)> dfs = [&](int pos, int sum, int rem, bool tight) -> i64 {
            if (sum > tar || sum + 9 * (n - pos) < tar) return 0;
            if (pos == n) return sum == tar && rem == 0;
            if (!tight && dp[pos][sum][rem] != -1) return dp[pos][sum][rem];
            int up = tight ? s[pos] - '0' : 9;
            i64 cnt = 0;
            for (int d = 0; d <= up; d++) {
                cnt += dfs(pos + 1, sum + d, (rem * 10 + d) % tar, tight && d == up);
            }
            if (!tight) dp[pos][sum][rem] = cnt;
            return cnt;
        };
        ans += dfs(0, 0, 0, true);
    }
    return ans;
}

// ==================== 使用示例 ====================
// 作用：演示前缀及区间计数；输入：无，使用上界 20、9；输出：13 和区间 [10,20] 的计数 4。
int main() {
    cout << harshad(20) << '\n';              // 13
    cout << harshad(20) - harshad(9) << '\n'; // 查询 [10,20]，结果 4
}
