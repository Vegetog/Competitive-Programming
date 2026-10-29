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

struct GeometricSums {
    i64 limit;
    unordered_set<i64> sums;

    explicit GeometricSums(i64 limit) : limit(limit) {
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
    bool contains(i64 value) const {
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
int main() {
    GeometricSums sums(1000);
    cout << sums.contains(7) << ' ' << sums.contains(15) << ' ' << sums.contains(8)
         << '\n'; // 1 1 0
}
