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
        array<int, 62> next{};
        int count = 0, terminal = 0;
    };
    vector<Node> nodes{1};
    static int char_id(char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        if ('A' <= c && c <= 'Z') return c - 'A' + 26;
        assert('0' <= c && c <= '9');
        return c - '0' + 52;
    }
    void insert(const string& s) {
        int node = 0;
        nodes[node].count++;
        for (char c : s) {
            int id = char_id(c);
            if (nodes[node].next[id] == 0) {
                nodes[node].next[id] = nodes.size();
                nodes.emplace_back();
            }
            node = nodes[node].next[id];
            nodes[node].count++;
        }
        nodes[node].terminal++;
    }
    int find_node(const string& s) const {
        int node = 0;
        for (char c : s) {
            node = nodes[node].next[char_id(c)];
            if (node == 0) return -1;
        }
        return node;
    }
    int count_prefix(const string& s) const {
        int node = find_node(s);
        return node == -1 ? 0 : nodes[node].count;
    }
    int count_word(const string& s) const {
        int node = find_node(s);
        return node == -1 ? 0 : nodes[node].terminal;
    }
};

// ==================== 使用示例 ====================
int main() {
    Trie trie;
    trie.insert("abc");
    trie.insert("abA");
    cout << trie.count_prefix("ab") << ' ' << trie.count_word("abc") << '\n'; // 2 1
}
