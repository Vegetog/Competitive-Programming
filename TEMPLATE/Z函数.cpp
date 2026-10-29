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
vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n);
    if (n == 0) return z;
    z[0] = n;
    for (int i = 1, left = 0, right = 0; i < n; i++) {
        if (i < right) z[i] = min(right - i, z[i - left]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > right) left = i, right = i + z[i];
    }
    return z;
}

// ==================== 使用示例 ====================
int main() {
    for (int length : z_function("ababa")) cout << length << ' ';
    cout << '\n'; // 5 0 3 0 1
}
