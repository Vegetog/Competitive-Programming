#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Helper function to build prefix function for KMP
static vector<int> border(const string& pattern) {
    int m = pattern.size();
    vector<int> pi(m);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

// Returns starting indices of occurrences of pattern in text
static vector<int> kmp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> pi = border(pattern);
    vector<int> positions;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j]) {
            if (j == m - 1) {
                positions.push_back(i - m + 1);
                j = pi[j];
            } else {
                ++j;
            }
        }
    }
    return positions;
}

int main() {
    string text = "abcabcabc";
    string pattern = "abc";
    vector<int> expected{0, 3, 6};
    vector<int> result = kmp(text, pattern);
    assert(result == expected);
    cout << "KMP test passed\n";
    return 0;
}

/*
Compile with:
clang++ -std=c++23 -g tests/test_kmp.cpp -o tests/test_kmp
*/
