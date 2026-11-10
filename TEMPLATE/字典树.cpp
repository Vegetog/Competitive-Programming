/*
算法：字典树（Trie）
简介：维护字符串集合，支持插入、完整字符串计数及前缀计数。
复杂度：每次操作时间 O(|s|)，空间 O(62S)，S 为插入字符串总长度。
约定：字符集为 a-z、A-Z、0-9，区分大小写；重复字符串重复计数；空前缀匹配所有字符串。
*/
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==================== 算法模板 ====================
struct Trie {
    struct Node {
        array<int, 62> ch{};
        int cnt = 0, end = 0;
    };
    vector<Node> tr{1};
    // 作用：映射字符编号；输入：a-z、A-Z 或 0-9 中的字符 c；输出：0..61 中对应编号。
    static int idx(char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        if ('A' <= c && c <= 'Z') return c - 'A' + 26;
        assert('0' <= c && c <= '9');
        return c - '0' + 52;
    }
    // 作用：插入一个字符串；输入：字符串 s；输出：更新 tr 的路径计数和终点计数，无返回值。
    void add(const string& s) {
        int u = 0;
        tr[u].cnt++;
        for (char c : s) {
            int id = idx(c);
            if (tr[u].ch[id] == 0) {
                tr[u].ch[id] = tr.size();
                tr.emplace_back();
            }
            u = tr[u].ch[id];
            tr[u].cnt++;
        }
        tr[u].end++;
    }
    // 作用：查找字符串路径；输入：字符串 s；输出：路径终点编号，不存在为 -1，空串返回根 0。
    int find(const string& s) const {
        int u = 0;
        for (char c : s) {
            u = tr[u].ch[idx(c)];
            if (u == 0) return -1;
        }
        return u;
    }
    // 作用：统计前缀匹配；输入：前缀 s；输出：以 s 开头的已插入字符串数，重复项重复计数。
    int prefix(const string& s) const {
        int u = find(s);
        return u == -1 ? 0 : tr[u].cnt;
    }
    // 作用：统计完整字符串；输入：字符串 s；输出：s 被插入的次数。
    int count(const string& s) const {
        int u = find(s);
        return u == -1 ? 0 : tr[u].end;
    }
};

// ==================== 使用示例 ====================
// 作用：演示字典树；输入：插入 abc、abA；输出：前缀 ab 的数量 2、完整串 abc 的数量 1。
int main() {
    Trie t;
    t.add("abc");
    t.add("abA");
    cout << t.prefix("ab") << ' ' << t.count("abc") << '\n'; // 2 1
}
