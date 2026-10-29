/*
算法：KMP 字符串匹配
简介：用前缀函数在线性时间内查找模式串的全部出现位置，允许重叠。
复杂度：时间 O(n + m)，空间 O(m + 匹配数)。
约定：字符串下标从 0 开始；空模式串匹配全部 n + 1 个边界。
*/
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
vector<int> prefix_function(const string& pattern) {
    int m = pattern.size();
    vector<int> prefix(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) j = prefix[j - 1];
        if (pattern[i] == pattern[j]) j++;
        prefix[i] = j;
    }
    return prefix;
}
vector<int> kmp_search(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    if (m == 0) {
        vector<int> positions(n + 1);
        iota(positions.begin(), positions.end(), 0);
        return positions;
    }
    auto prefix = prefix_function(pattern);
    vector<int> positions;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) j = prefix[j - 1];
        if (text[i] == pattern[j]) j++;
        if (j == m) {
            positions.push_back(i - m + 1);
            j = prefix[j - 1];
        }
    }
    return positions;
}

// ==================== 使用示例 ====================
int main() {
    for (int pos : kmp_search("ababa", "aba")) cout << pos << ' ';
    cout << '\n'; // 0 2
}
