/*
算法：试除法求约数
简介：枚举不超过平方根的因数，成对收集并排序。
复杂度：时间 O(√n + d log d)，空间 O(d)，d 为约数个数。
约定：n > 0；使用 i <= n/i 避免平方溢出。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
using i64 = long long;

// 作用：枚举正约数；输入：n>0；输出：n 的所有正约数，按升序排列。
vector<i64> divisors(i64 n) {
    assert(n > 0);
    vector<i64> d;
    for (i64 i = 1; i <= n / i; ++i) {
        if (n % i != 0) continue;
        d.push_back(i);
        if (i != n / i) d.push_back(n / i);
    }
    sort(d.begin(), d.end());
    return d;
}

// ==================== 使用示例 ====================
// 作用：运行固定示例；输入：无外部输入；输出：下方标明的算法调用结果。
int main() {
    for (i64 p : divisors(12)) cout << p << ' '; // 1 2 3 4 6 12
    cout << '\n';
}
