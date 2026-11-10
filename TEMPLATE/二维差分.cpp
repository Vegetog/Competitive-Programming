// 二维差分：初始化/还原 O(nm)，每次修改 O(1)，空间 O(nm)。
// 输入 n m q、n×m 矩阵，再输入 q 次修改 x1 y1 x2 y2 c，给闭矩形内所有元素加 c。
// 行列从 1 开始，最后输出修改后的矩阵；所有数值及中间结果须在 long long 范围内。
#include <iostream>
#include <vector>
using namespace std;

// 作用：用二维差分批量进行矩形加法并还原矩阵。
// 输入：标准输入中的 n m q、n×m 矩阵及 q 组 x1 y1 x2 y2 c（1-based 闭矩形加 c）。
// 输出：标准输出中的最终矩阵，每行 m 个数；正常结束返回 0。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
    vector<vector<long long>> a(n + 1, vector<long long>(m + 1));
    vector<vector<long long>> d(n + 2, vector<long long>(m + 2));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            d[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1];
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        long long c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        d[x1][y1] += c;
        d[x2 + 1][y1] -= c;
        d[x1][y2 + 1] -= c;
        d[x2 + 1][y2 + 1] += c;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
            cout << d[i][j] << (j == m ? '\n' : ' ');
        }
    }
}
