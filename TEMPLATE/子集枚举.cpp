/*
算法：子集枚举
简介：用位掩码表示集合，枚举所有子集或某个集合的全部子掩码。
复杂度：时间 O(2^n) / O(2^popcount(mask))，额外空间 O(1)。
约定：0 <= n < 64；f 接收 uint64_t 掩码；包含空集。
*/
#include <cassert>
#include <cstdint>
#include <iostream>

using namespace std;

// ==================== 算法模板 ====================
// 作用：枚举 n 个元素的所有子集；输入：0 <= n < 64、回调 f(mask)；输出：无返回值，按掩码升序调用 f，包含空集。
template <class F> void subsets(int n, F f) {
    assert(0 <= n && n < 64);
    for (uint64_t mask = 0; mask < (uint64_t{1} << n); mask++) f(mask);
}
// 作用：枚举集合的所有子掩码；输入：集合掩码 mask、回调 f(s)；输出：无返回值，按掩码降序调用 f，包含 0。
template <class F> void submasks(uint64_t mask, F f) {
    for (uint64_t s = mask;; s = (s - 1) & mask) {
        f(s);
        if (s == 0) break;
    }
}

// ==================== 使用示例 ====================
// 作用：演示子集与子掩码枚举；输入：无，使用 n=2、mask=5；输出：0 1 2 3 和 5 4 1 0。
int main() {
    // 两个回调均接收一个掩码，向标准输出写出该掩码和空格，无返回值。
    subsets(2, [](uint64_t mask) { cout << mask << ' '; });
    cout << '\n'; // 0 1 2 3
    submasks(0b101, [](uint64_t mask) { cout << mask << ' '; });
    cout << '\n'; // 5 4 1 0
}
