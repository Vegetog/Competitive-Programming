#include "bits/stdc++.h"

using namespace std;

template <typename T>
class ST {
   public:
    vector<vector<T> > st;
    int sz;
    function<T(T, T)> op;  // op can be max,min,gcd,lcm,&,|,etc.
    ST(vector<T>& x, function<T(T, T)> f) : op(std::move(f)) {
        sz = x.size();
        int K = log2(sz);
        st.resize(sz, vector<T>(K + 1));
        for (int i = 0; i < sz; i++) st[i][0] = x[i];
        for (int j = 1; j <= K; j++) {
            for (int i = 0; i + (1 << j) - 1 < sz; i++) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T get(int l, int r) {
        int K = log2(r - l + 1);
        return op(st[l][K], st[r - (1 << K) + 1][K]);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    ST<int> stmax(a, [](int x, int y) { return max(x, y); });
    ST<int> stmin(a, [](int x, int y) { return min(x, y); });

    while (q--) {
        int op;
        cin >> op;
        int l, r;
        cin >> l >> r;
        cout << (op == 1 ? stmin.get(l, r) : stmax.get(l, r)) << "\n";
    }
}
