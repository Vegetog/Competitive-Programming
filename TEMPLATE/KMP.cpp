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
// 作用：求前缀函数；输入：字符串 p；输出：pi[i] 为 p[0..i] 的最长相等真前后缀长度。
vector<int> get_pi(const string& p) {
    int m = p.size();
    vector<int> pi(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) j++;
        pi[i] = j;
    }
    return pi;
}
// 作用：查找全部匹配；输入：文本 s、模式 p；输出：允许重叠的匹配起点，空模式返回 0..s.size()。
vector<int> kmp(const string& s, const string& p) {
    int n = s.size(), m = p.size();
    if (m == 0) {
        vector<int> pos(n + 1);
        iota(pos.begin(), pos.end(), 0);
        return pos;
    }
    auto pi = get_pi(p);
    vector<int> pos;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) j = pi[j - 1];
        if (s[i] == p[j]) j++;
        if (j == m) {
            pos.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return pos;
}

// ==================== 使用示例 ====================
// 作用：演示 KMP；输入：文本 ababa、模式 aba；输出：0 2。
int main() {
    for (int pos : kmp("ababa", "aba")) cout << pos << ' ';
    cout << '\n'; // 0 2
}
