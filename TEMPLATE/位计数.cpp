/*
算法：二进制中 1 的个数
简介：每次清除最低位的 1，统计无符号整数的置位数。
复杂度：时间 O(置位数)，空间 O(1)。
约定：使用 64 位无符号整数；0 的结果为 0。
*/
#include <cstdint>
#include <iostream>

using namespace std;

// ==================== 算法模板 ====================
int popcount(uint64_t value) {
    int count = 0;
    for (; value != 0; value &= value - 1) count++;
    return count;
}

// ==================== 使用示例 ====================
int main() {
    cout << popcount(0b101101ULL) << '\n'; // 4
}
