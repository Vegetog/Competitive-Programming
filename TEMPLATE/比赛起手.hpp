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
// 作用：处理一组求和数据；输入：流 in 中的非负数量 n 及随后 n 个整数；输出：无返回值，向 out 写入总和及换行，未读到 n 时不输出。
inline void solve(istream& in, ostream& out) {
    int n;
    if (!(in >> n)) return;
    i64 sum = 0, x;
    while (n-- > 0) {
        in >> x;
        sum += x;
    }
    out << sum << '\n';
}

// ==================== 使用示例 ====================
#ifdef TEMPLATE_EXAMPLE
// 作用：演示比赛入口；输入：无，使用内存流 "3 1 2 3"；输出：6。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    istringstream in("3 1 2 3");
    solve(in, cout); // 6；提交时改为 solve(cin, cout)，并替换 solve 中的算法。
    // 多组数据：int tests; cin >> tests; while (tests--) solve(cin, cout);
}
#endif
