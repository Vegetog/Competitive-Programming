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
// 作用：统计子串出现次数；输入：文本 s、模式 p；输出：允许重叠的出现次数，空模式计 |s|+1 次。
size_t count_sub(const string& s, const string& p) {
    if (p.empty()) return s.size() + 1;
    size_t cnt = 0;
    for (size_t pos = s.find(p); pos != string::npos; pos = s.find(p, pos + 1)) {
        cnt++;
    }
    return cnt;
}

// ==================== 使用示例 ====================
// 作用：演示子串计数；输入：文本 aaaa、模式 aa；输出：3。
int main() {
    cout << count_sub("aaaa", "aa") << '\n'; // 3
}
