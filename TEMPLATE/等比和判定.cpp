/*
算法：等比和判定与防溢出枚举
简介：预处理较小底数的等比和，并用二分检查大底数的三项和。
复杂度：设 B=⌊∛limit⌋；预处理 O(B log limit)，单次查询 O(log limit)，空间 O(B log limit)。
约定：判断 n = 1+k+…+k^e（k >= 2，e >= 2）；0 <= n <= limit <= long long 上限；乘加前检查界限。
*/
#include <cassert>
#include <iostream>
#include <unordered_set>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

struct GeoSum {
    i64 limit;
    unordered_set<i64> sums;

    // 作用：预处理至少四项的等比和；输入：非负上限 limit；输出：保存可行等比和集合的对象，三项和由 has 查询。
    explicit GeoSum(i64 limit) : limit(limit) {
        assert(limit >= 0);
        // 大于立方根的底数只能形成三项和，留到查询时处理。
        for (i64 base = 2; base <= limit / base / base; ++base) {
            i64 term = base * base;
            i64 sum = 1 + base + term;
            while (term <= (limit - sum) / base) {
                term *= base;
                sum += term;
                sums.insert(sum);
            }
        }
    }
    // 作用：判断等比和表示；输入：0<=value<=limit；输出：可写为 1+k+…+k^e（k>=2,e>=2）时返回 true。
    bool has(i64 value) const {
        assert(value >= 0 && value <= limit);
        if (sums.count(value)) return true;
        i64 left = 2, right = value / 2;
        while (left <= right) {
            i64 base = left + (right - left) / 2;
            // base^2 + base + 1 与 value 比较，先用除法避免溢出。
            if (base > (value - 1) / (base + 1)) {
                right = base - 1;
            } else {
                i64 sum = base * (base + 1) + 1;
                if (sum == value) return true;
                left = base + 1;
            }
        }
        return false;
    }
};

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    GeoSum sums(1000);
    cout << sums.has(7) << ' ' << sums.has(15) << ' ' << sums.has(8) << '\n'; // 1 1 0
}
