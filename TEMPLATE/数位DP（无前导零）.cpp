/*
算法：数位 DP（无需前导零状态）
简介：枚举数位和，统计能被自身数位和整除的正整数；前导零不改变数位和与余数。
复杂度：时间 O(D × (9D)³ × 10)，空间 O(D × (9D)²)。
约定：count_harshad(n) 统计 [1,n]，n <= 0 时返回 0；不计整数 0。
*/
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
i64 count_harshad(i64 upper) {
    if (upper <= 0) return 0;
    string digits = to_string(upper);
    int n = digits.size();
    i64 result = 0;
    for (int target = 1; target <= 9 * n; target++) {
        vector memo(n, vector(target + 1, vector<i64>(target, -1)));
        function<i64(int, int, int, bool)> dfs = [&](int pos, int sum, int remainder,
                                                     bool tight) -> i64 {
            if (sum > target || sum + 9 * (n - pos) < target) return 0;
            if (pos == n) return sum == target && remainder == 0;
            if (!tight && memo[pos][sum][remainder] != -1) return memo[pos][sum][remainder];
            int limit = tight ? digits[pos] - '0' : 9;
            i64 count = 0;
            for (int digit = 0; digit <= limit; digit++) {
                count += dfs(pos + 1, sum + digit, (remainder * 10 + digit) % target,
                             tight && digit == limit);
            }
            if (!tight) memo[pos][sum][remainder] = count;
            return count;
        };
        result += dfs(0, 0, 0, true);
    }
    return result;
}

// ==================== 使用示例 ====================
int main() {
    cout << count_harshad(20) << '\n';                    // 13
    cout << count_harshad(20) - count_harshad(9) << '\n'; // 查询 [10,20]，结果 4
}
