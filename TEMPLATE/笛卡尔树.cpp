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
struct Cartesian {
    int root = -1;
    vector<int> ls, rs;
    // 作用：建立小根笛卡尔树；输入：数组 a；输出：root 与左右孩子 ls、rs，空节点记 -1。
    explicit Cartesian(const vector<i64>& a) : ls(a.size(), -1), rs(a.size(), -1) {
        vector<int> st;
        for (int i = 0; i < static_cast<int>(a.size()); i++) {
            int p = -1;
            while (!st.empty() && a[st.back()] > a[i]) {
                p = st.back();
                st.pop_back();
            }
            ls[i] = p;
            if (!st.empty()) rs[st.back()] = i;
            st.push_back(i);
        }
        if (!st.empty()) root = st.front();
    }
};

// ==================== 使用示例 ====================
// 作用：演示本模板调用；输入：代码内固定数据；输出：下方标注的结果到标准输出。
int main() {
    Cartesian s({3, 1, 4, 2});
    cout << s.root << '\n';                    // 输出：1
    cout << s.ls[1] << ' ' << s.rs[1] << '\n'; // 输出：0 3
}
