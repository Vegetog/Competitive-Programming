#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#else
#include <bits/stdc++.h>
#endif
#define int long long
// struct CMP {bool operator()(const auto & x, const auto &y) const{ return x<y; }};
constexpr int N = (int)2E6 + 10, INF = (int)2E18 + 10;using namespace std;using ll = long long;using ull = unsigned long long; using i128 = __int128_t; using u128 = __uint128_t; using P2 = pair<int, int>; struct P3 {int first, second, third; auto operator<=>(const P3&) const = default;}; // C++20

template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    // int sum = 0;
    // int mx = -INF;
    // int mn = INF;
    int g=0;
};

Info operator+(Info a, Info b) {
    Info c;
    // c.sum = a.sum + b.sum;
    // c.mx = max(a.mx, b.mx);
    // c.mn = min(a.mn, b.mn);
    c.g=gcd(a.g,b.g);
    return c;
}

void SINGLE_TEST() 
{
    int n,q;
    cin>>n>>q;
    vector<int> a(n+1);
    SegmentTree<Info> rq(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int x=a[i+1]-a[i];
        rq.modify(i,Info{x});
    }

    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<rq.rangeQuery(l,r).g<<" \n"[q==0];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    // INIT();
    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
