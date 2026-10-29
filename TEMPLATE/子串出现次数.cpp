/*
算法：子串出现次数（标准库查找）
简介：重复调用 string::find，统计允许重叠的子串出现次数。
复杂度：最坏时间 O(nm)，额外空间 O(1)。
约定：n 为文本长度，m 为模式长度；空模式串出现 n + 1 次；大串匹配可改用 KMP。
*/
#include <iostream>
#include <string>

using namespace std;

// ==================== 算法模板 ====================
size_t count_occurrences(const string& text, const string& pattern) {
    if (pattern.empty()) return text.size() + 1;
    size_t count = 0;
    for (size_t pos = text.find(pattern); pos != string::npos; pos = text.find(pattern, pos + 1)) {
        count++;
    }
    return count;
}

// ==================== 使用示例 ====================
int main() {
    cout << count_occurrences("aaaa", "aa") << '\n'; // 3
}
