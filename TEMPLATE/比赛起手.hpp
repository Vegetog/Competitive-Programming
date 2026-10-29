/*
算法：比赛起手模板
简介：保留常用类型、快速输入输出设置与单组/多组数据入口。
复杂度：时间与空间取决于 solve 的具体实现；此处求和示例时间 O(n)，额外空间 O(1)。
约定：C++17；本头文件可直接包含，定义 TEMPLATE_EXAMPLE 后可单独编译运行底部示例。
*/
#pragma once
#include <iostream>
#include <sstream>

using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
inline void solve(istream& input, ostream& output) {
    int n;
    if (!(input >> n)) return;
    i64 sum = 0, value;
    while (n-- > 0) {
        input >> value;
        sum += value;
    }
    output << sum << '\n';
}

// ==================== 使用示例 ====================
#ifdef TEMPLATE_EXAMPLE
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    istringstream input("3 1 2 3");
    solve(input, cout); // 6；提交时改为 solve(cin, cout)，并替换 solve 中的算法。
    // 多组数据：int tests; cin >> tests; while (tests--) solve(cin, cout);
}
#endif
