/*
算法：笛卡尔树
简介：用单调栈构造中序顺序与原数组一致、满足小根堆性质的二叉树。
复杂度：时间 O(n)，空间 O(n)。
约定：节点下标从 0 开始，空孩子/空树根为 -1；相同值中下标较小的节点优先为祖先。
*/
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

// ==================== 算法模板 ====================
struct CartesianTree {
    int root = -1;
    vector<int> left, right;
    explicit CartesianTree(const vector<i64>& a) : left(a.size(), -1), right(a.size(), -1) {
        vector<int> stack;
        for (int i = 0; i < static_cast<int>(a.size()); i++) {
            int last = -1;
            while (!stack.empty() && a[stack.back()] > a[i]) {
                last = stack.back();
                stack.pop_back();
            }
            left[i] = last;
            if (!stack.empty()) right[stack.back()] = i;
            stack.push_back(i);
        }
        if (!stack.empty()) root = stack.front();
    }
};

// ==================== 使用示例 ====================
int main() {
    CartesianTree tree({3, 1, 4, 2});
    cout << tree.root << '\n';                            // 输出：1
    cout << tree.left[1] << ' ' << tree.right[1] << '\n'; // 输出：0 3
}
