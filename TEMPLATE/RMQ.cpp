#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

template<class T,class Cmp = less<T>>
struct RMQ {
    const Cmp cmp = Cmp();
    static constexpr unsigned B = 64;
    using ull = unsigned long long;
    int n;
    vector<vector<T>> a;
    vector<T> pre, suf, ini;
    vector<ull> stk;
    RMQ() {}
    RMQ(const vector<T> &v) {
        init(v);
    }
    void init(const vector<T> &v) {
        n = v.size();
        pre = suf = ini = v;
        stk.resize(n);
        if (!n) {
            return;
        }
        const int M = (n - 1) / B + 1;
        const int lg = __lg(M);
        a.assign(lg + 1, vector<T>(M));
        for (int i = 0; i < M; i++) {
            a[0][i] = v[i * B];
            for (int j = 1; j < B && i * B + j < n; j++) {
                a[0][i] = min(a[0][i], v[i * B + j], cmp);
            }
        }
        for (int i = 1; i < n; i++) {
            if (i % B) {
                pre[i] = min(pre[i], pre[i - 1], cmp);
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            if (i % B != B - 1) {
                suf[i] = min(suf[i], suf[i + 1], cmp);
            }
        }
        for (int j = 0; j < lg; j++) {
            for (int i = 0; i + (2 << j) <= M; i++) {
                a[j + 1][i] = min(a[j][i], a[j][i + (1 << j)], cmp);
            }
        }
        for (int i = 0; i < M; i++) {
            const int l = i * B;
            const int r = min(1U * n, l + B);
            ull s = 0;
            for (int j = l; j < r; j++) {
                while (s && cmp(v[j], v[__lg(s) + l])) {
                    s ^= 1ULL << __lg(s);
                }
                s |= 1ULL << (j - l);
                stk[j] = s;
            }
        }
    } 
    T operator()(int l, int r) {
        if (l / B != (r - 1) / B) {
            T ans = min(suf[l], pre[r - 1], cmp);
            l = l / B + 1;
            r = r / B;
            if (l < r) {
                int k = __lg(r - l);
                ans = min({ans, a[k][l], a[k][r - (1 << k)]}, cmp);
            }
            return ans;
        } else {
            int x = B * (l / B);
            return ini[__builtin_ctzll(stk[r - 1] >> (l - x)) + l];
        }
    }
};
template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void SINGLE_TEST() 
{
    int n, x;
    cin >> n >> x;
    x--;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }
    
    RMQ<int, greater<int>> maxa {a};
    vector<int> f(n);
    vector<vector<int>> vec(n);
    
    for (int i = 0; i < n; i++) {
        int l = i, r = i + 1;
        while (true) {
            bool change = false;
            int lo = 0, hi = l;
            ll sum = pre[r] - pre[l];
            while (lo < hi) {
                int x = (lo + hi) / 2;
                if (maxa(x, l) <= sum) {
                    hi = x;
                } else {
                    lo = x + 1;
                }
            }
            if (l != lo) {
                change = true;
            }
            l = lo;
            lo = r;
            hi = n;
            sum = pre[r] - pre[l];
            while (lo < hi) {
                int x = (lo + hi + 1) / 2;
                if (maxa(r, x) <= sum) {
                    lo = x;
                } else {
                    hi = x - 1;
                }
            }
            if (r != lo) {
                change = true;
            }
            r = lo;
            if (!change) {
                break;
            }
        }
        if (r < n) {
            vec[r].push_back(i);
        }
    }
    Fenwick<int> fen(n);
    vector<int> right(n);
    for (int r = 0, l = 0; r < n; r++) {
        for (auto i : vec[r]) {
            fen.add(i, 1);
        }
        int lo = r + 1, hi = n;
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (pre[x] - pre[r + 1] < a[r]) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }
        right[r] = lo;
        while (right[l] <= r) {
            l++;
        }
        f[r] = l + 1 - fen.sum(l + 1);
    }
    for (int i = x; i < n; i++) {
        cout << f[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
/*---------------------------------------------------------------------------------
struct CMP{bool operator()(const int & x, const int &y) const{ return x<y; }};

template <class T>
map<T, int> sortMap(const map<T, int> mp) {
    vector<pair<T, int>> v(mp.begin(), mp.end());
    sort(v.begin(), v.end(),
         [&](auto x, auto y) { return x.second < y.second; });
    map<T, int> ans;
    for (auto [lo, v] : v) {
        ans[lo] = v;
    }
    return ans;
}

mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count()
);

template <class T>
void shuffle(typename vector<T>::iterator first, typename vector<T>::iterator last) {
    shuffle(first, last, rng);
}
---------------------------------------------------------------------------------*/
