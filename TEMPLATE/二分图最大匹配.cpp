/*
算法：二分图最大匹配（增广路）
简介：依次从左部未匹配顶点寻找增广路，翻转路径上的匹配关系。
复杂度：时间 O(n_left * m + n_left + n_right)，空间 O(n_left+n_right+m)。
约定：左右部各自从 0 编号；匹配对象为 -1 表示未匹配；递归深度最多 n_left。
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// ==================== 算法模板 ====================
struct BipartiteMatching {
    vector<vector<int>> graph;
    vector<int> match_left, match_right, visited;
    int timestamp = 0;

    BipartiteMatching(int n_left, int n_right)
        : graph(n_left), match_left(n_left, -1), match_right(n_right, -1), visited(n_right, 0) {}

    void add_edge(int left, int right) {
        assert(0 <= left && left < static_cast<int>(graph.size()));
        assert(0 <= right && right < static_cast<int>(match_right.size()));
        graph[left].push_back(right);
    }

    bool augment(int left) {
        for (int right : graph[left]) {
            if (visited[right] == timestamp) continue;
            visited[right] = timestamp;
            if (match_right[right] == -1 || augment(match_right[right])) {
                match_left[left] = right;
                match_right[right] = left;
                return true;
            }
        }
        return false;
    }

    int solve() {
        fill(match_left.begin(), match_left.end(), -1);
        fill(match_right.begin(), match_right.end(), -1);
        fill(visited.begin(), visited.end(), 0);
        timestamp = 0;
        int result = 0;
        for (int left = 0; left < static_cast<int>(graph.size()); ++left) {
            ++timestamp;
            result += augment(left);
        }
        return result;
    }
};

// ==================== 使用示例 ====================
int main() {
    BipartiteMatching matching(3, 2);
    matching.add_edge(0, 0);
    matching.add_edge(0, 1);
    matching.add_edge(1, 0);
    cout << matching.solve() << '\n'; // 2；match_left / match_right 保存具体方案
}
