/*
算法：Z 函数
简介：计算每个后缀与整个字符串的最长公共前缀长度。
复杂度：时间 O(n)，空间 O(n)。
约定：下标从 0 开始，z[0] = n；空字符串返回空数组。
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
// 作用：求 Z 函数；输入：字符串 s；输出：z[i] 为 s 与后缀 s[i..] 的最长公共前缀长度，z[0]=|s|。
vector<int> get_z(const string& s) {
    int n = s.size();
    vector<int> z(n);
    if (n == 0) return z;
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// ==================== 使用示例 ====================
// 作用：演示 Z 函数；输入：ababa；输出：5 0 3 0 1。
int main() {
    for (int x : get_z("ababa")) cout << x << ' ';
    cout << '\n'; // 5 0 3 0 1
}
