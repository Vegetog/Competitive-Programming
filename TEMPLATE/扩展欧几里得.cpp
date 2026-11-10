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

// 作用：求扩展欧几里得系数；输入：非负 a、b 及引用 x、y；输出：gcd(a,b)，并写入满足 ax+by=gcd 的 x、y。
i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 gcd = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return gcd;
}

// 作用：求二元一次方程的一组整数解；输入：a,b>0、常数 c、引用 x,y；输出：有解返回 true 并写入解，无解返回 false。
bool dio(i64 a, i64 b, i64 c, i128& x, i128& y) {
    assert(a > 0 && b > 0);
    i64 cx, cy;
    i64 gcd = exgcd(a, b, cx, cy);
    if (c % gcd != 0) return false;
    x = i128(cx) * (c / gcd);
    y = i128(cy) * (c / gcd);
    return true;
}

struct DioRes {
    bool ok = false;
    i128 count = 0, min_x = 0, min_y = 0, max_x = 0, max_y = 0;
};

// 作用：统计 ax+by=c 的正整数解；输入：a,b>0 和 c；输出：ok 表示有整数解，count 为正解数；有整数解时 min_x/min_y 为各坐标可达的最小正值，max_x/max_y 仅 count>0 时有效。
DioRes pos_sol(i64 a, i64 b, i64 c) {
    i128 x, y;
    if (!dio(a, b, c, x, y)) return {};
    i64 cx, cy;
    i64 gcd = exgcd(a, b, cx, cy);
    i64 dx = b / gcd, dy = a / gcd;
    x = (x % dx + dx) % dx;
    if (x == 0) x = dx;
    y = (i128(c) - i128(a) * x) / b;
    DioRes res;
    res.ok = true;
    res.min_x = x;
    res.min_y = (y % dy + dy) % dy;
    if (res.min_y == 0) res.min_y = dy;
    // count == 0 时 min_x/min_y 是分别可取得的最小正值，不能同时取到。
    if (y > 0) {
        res.count = (y - 1) / dy + 1;
        res.max_x = x + (res.count - 1) * dx;
        res.max_y = y;
    }
    return res;
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    auto res = pos_sol(2, 3, 13);
    cout << i64(res.count) << ' ' << i64(res.min_x) << ' ' << i64(res.min_y) << ' '
         << i64(res.max_x) << ' ' << i64(res.max_y) << '\n'; // 2 2 1 5 3
}
