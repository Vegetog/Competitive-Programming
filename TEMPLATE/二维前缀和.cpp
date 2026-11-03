// 二维前缀和：预处理 O(nm)，每次查询 O(1)，空间 O(nm)。
// 输入 n m q、n×m 矩阵，再输入 q 个闭矩形 x1 y1 x2 y2；行列从 1 开始。
// 每次输出矩形元素和；所有数值及中间结果须在 long long 范围内。
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
    vector<vector<long long>> s(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            long long a;
            cin >> a;
            s[i][j] = a + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1] << '\n';
    }
}
