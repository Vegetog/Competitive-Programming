/*
算法：扩展欧几里得与二元一次不定方程
简介：求 ax + by = gcd(a,b) 的系数，并统计 ax + by = c 的正整数解。
复杂度：时间 O(log min(a,b))，递归栈空间 O(log min(a,b))。
约定：a,b > 0，c 为 long long；解及解数使用 __int128；一般整数解为 x+k·b/g、y-k·a/g。
*/
#include <cassert>
#include <iostream>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;
using i128 = __int128;

i64 extended_gcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 gcd = extended_gcd(b, a % b, y, x);
    y -= a / b * x;
    return gcd;
}

bool solve_diophantine(i64 a, i64 b, i64 c, i128& x, i128& y) {
    assert(a > 0 && b > 0);
    i64 coefficient_x, coefficient_y;
    i64 gcd = extended_gcd(a, b, coefficient_x, coefficient_y);
    if (c % gcd != 0) return false;
    x = i128(coefficient_x) * (c / gcd);
    y = i128(coefficient_y) * (c / gcd);
    return true;
}

struct PositiveSolutions {
    bool has_integer_solution = false;
    i128 count = 0, min_x = 0, min_y = 0, max_x = 0, max_y = 0;
};

PositiveSolutions positive_solutions(i64 a, i64 b, i64 c) {
    i128 x, y;
    if (!solve_diophantine(a, b, c, x, y)) return {};
    i64 coefficient_x, coefficient_y;
    i64 gcd = extended_gcd(a, b, coefficient_x, coefficient_y);
    i64 step_x = b / gcd, step_y = a / gcd;
    x = (x % step_x + step_x) % step_x;
    if (x == 0) x = step_x;
    y = (i128(c) - i128(a) * x) / b;
    PositiveSolutions result;
    result.has_integer_solution = true;
    result.min_x = x;
    result.min_y = (y % step_y + step_y) % step_y;
    if (result.min_y == 0) result.min_y = step_y;
    // count == 0 时 min_x/min_y 是分别可取得的最小正值，不能同时取到。
    if (y > 0) {
        result.count = (y - 1) / step_y + 1;
        result.max_x = x + (result.count - 1) * step_x;
        result.max_y = y;
    }
    return result;
}

// ==================== 使用示例 ====================
int main() {
    auto result = positive_solutions(2, 3, 13);
    cout << i64(result.count) << ' ' << i64(result.min_x) << ' ' << i64(result.min_y) << ' '
         << i64(result.max_x) << ' ' << i64(result.max_y) << '\n'; // 2 2 1 5 3
}
