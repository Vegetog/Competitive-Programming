#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr long long INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    template <class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
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
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) +
               rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Tag {
    int add = 0;
    void apply(Tag t) {  // 两个懒标记结合
        add += t.add;
    }
};

struct Info {
    int sum = 0;
    int len = 1;
    int mx = -INF;
    int mn = INF;
    void apply(Tag t) {  // 懒标记作用到信息上
        sum += t.add * len;
        mx += t.add;
        mn += t.add;
    }
};
Info operator+(Info a, Info b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.len = a.len + b.len;
    c.mx = max(a.mx, b.mx);
    c.mn = min(a.mn, b.mn);
    return c;
}

void SINGLE_TEST() 
{
    int n,k,q;
    cin>>n>>k>>q;
    vector<int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i]-i;
    }

    multiset<int,greater<>> cnt;
    map<int,int> mp;
    vector<int> ans(n+10);
    for(int i=1,j=1;i<=n;i++){
        if(i>k){
            auto it=cnt.find(mp[b[i-k]]);
            cnt.erase(it);
            cnt.insert(mp[b[i-k]]-1);
            mp[b[i-k]]--;
        }
        mp[b[i]]++;
        if(mp[b[i]]==1){
            cnt.insert(1);
        }else{
            auto it=cnt.find(mp[b[i]]-1);
            cnt.erase(it);
            cnt.insert(mp[b[i]]);
        }
        if(i>=k){
            ans[i]=k-*cnt.begin();
        }
    } 

    vector<vector<PII>> g(n+10);
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        g[l].push_back({r,i});
    }
    LazySegmentTree<Info,Tag> tr(n+10);
    vector<int> stk={n+1};
    vector<int> query(q+1);
    for(int i=n;i>=k;i--){
        while(stk.size()>1 && ans[i]<ans[stk.back()]){
            int t=stk.back();
            stk.pop_back();
            tr.rangeApply(t,stk.back()-1 +1,{-ans[t]});
        }
        tr.rangeApply(i,stk.back()-1 +1,{ans[i]});
        stk.push_back(i);
        for(auto [r,id] : g[i-k+1]){
            query[id]=tr.rangeQuery(i,r +1).sum;
        }
    }

    for(int i=1;i<=q;i++){
        cout<<query[i]<<"\n";
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
