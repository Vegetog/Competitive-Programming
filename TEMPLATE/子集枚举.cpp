/*
算法：子集枚举
简介：用位掩码表示集合，枚举所有子集或某个集合的全部子掩码。
复杂度：时间 O(2^n) / O(2^popcount(mask))，额外空间 O(1)。
约定：0 <= n < 64；visit 接收 uint64_t 掩码；包含空集。
*/
#include <cassert>
#include <cstdint>
#include <iostream>

using namespace std;

// ==================== 算法模板 ====================
template <class F> void enumerate_subsets(int n, F visit) {
    assert(0 <= n && n < 64);
    for (uint64_t mask = 0; mask < (uint64_t{1} << n); mask++) visit(mask);
}
template <class F> void enumerate_submasks(uint64_t mask, F visit) {
    for (uint64_t subset = mask;; subset = (subset - 1) & mask) {
        visit(subset);
        if (subset == 0) break;
    }
}

// ==================== 使用示例 ====================
int main() {
    enumerate_subsets(2, [](uint64_t mask) { cout << mask << ' '; });
    cout << '\n'; // 0 1 2 3
    enumerate_submasks(0b101, [](uint64_t mask) { cout << mask << ' '; });
    cout << '\n'; // 5 4 1 0
}
