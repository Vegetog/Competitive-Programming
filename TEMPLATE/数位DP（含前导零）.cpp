/*
算法：数位 DP（区分前导零）
简介：统计相邻数字之差至少为 2 的正整数，以 started 状态区分前导零。
复杂度：时间 O(D × 10²)，空间 O(D × 10)，D 为十进制位数。
约定：count_windy(n) 统计 [1,n]，n <= 0 时返回 0；前导零不参与相邻数字比较。
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
i64 count_windy(i64 upper) {
    if (upper <= 0) return 0;
    string digits = to_string(upper);
    int n = digits.size();
    vector<vector<i64>> memo(n, vector<i64>(10, -1));
    function<i64(int, int, bool, bool)> dfs = [&](int pos, int last, bool tight,
                                                  bool started) -> i64 {
        if (pos == n) return started;
        if (!tight && started && memo[pos][last] != -1) return memo[pos][last];
        int limit = tight ? digits[pos] - '0' : 9;
        i64 result = 0;
        for (int digit = 0; digit <= limit; digit++) {
            bool next_tight = tight && digit == limit;
            if (!started && digit == 0)
                result += dfs(pos + 1, 0, next_tight, false);
            else if (!started || abs(digit - last) >= 2) {
                result += dfs(pos + 1, digit, next_tight, true);
            }
        }
        if (!tight && started) memo[pos][last] = result;
        return result;
    };
    return dfs(0, 0, true, false);
}

// ==================== 使用示例 ====================
int main() {
    cout << count_windy(20) << '\n';                   // 17
    cout << count_windy(100) - count_windy(9) << '\n'; // 查询 [10,100]，结果 64
}
