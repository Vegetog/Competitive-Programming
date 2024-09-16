#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
// #define int long long

using namespace std;
using ll = long long;
using PI = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

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
    ll mn = INF;
};

Info operator+(Info a, Info b) {
    Info c;
    // c.sum = a.sum + b.sum;
    // c.mx = max(a.mx, b.mx);
    c.mn = min(a.mn, b.mn);
    return c;
}

void SINGLE_TEST() 
{
    int n;cin>>n;
    vector<PI> a(n+1);
    int mxl=-INF;
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
        mxl=max(mxl,a[i].first);
    }

    sort(a.begin()+1,a.end(),[](PI a,PI b){
        if(a.second==b.second) return a.first<b.first;
        return a.second<b.second;
    });

    ll ans=INF;
    vector<ll> dp(n+1,INF);
    dp[0]=0;
    vector<Info> temp(n+1);
    for(int i=1;i<=n;i++){
        temp[0].mn=INF;
    }
    temp[0].mn=0;
    SegmentTree<Info> tr(temp);
    
    a[0].first=a[0].second=-INF;
    vector<int> mx(n+1,-INF);
    for(int i=1;i<=n;i++){
        auto [le,ri]=a[i];
        int t=ri-le;
        mx[i]=max(mx[i-1],le);
        int l=0,r=i-1;
        while(l<r){
            int mid=(l+r+1)/2;
            if(a[mid].second<le) l=mid;
            else r=mid-1;
        }
        int R=l;
        l=0,r=i-1;
        while(l<r){
            int mid=(l+r)/2;
            if(a[mid].second>=mx[R]) r=mid;
            else l=mid+1;
        }
        int L=r;
        dp[i]=min(dp[i],tr.rangeQuery(L,R+1).mn+t);
        tr.modify(i,{dp[i]});
        if(ri>=mxl) ans=min(ans,dp[i]);
    }    
    cout<<ans<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }

    return 0;
}
