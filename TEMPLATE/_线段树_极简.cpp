#include <bits/stdc++.h>
using namespace std;
#define int long long

// ===== 按题意修改 Info (+ Tag) =====
struct Tag {
    int add = 0;
    void apply(Tag t) { add += t.add; }
};
struct Info {
    int sum = 0, len = 1;
    void apply(Tag t) { sum += t.add * len; }
};
Info operator+(Info a, Info b) { return {a.sum + b.sum, a.len + b.len}; }

// ===== 单点修改 + 区间查询 [l, r) 0-indexed =====
struct Seg {
    int n; vector<Info> t;
    Seg(int n) : n(n), t(4 * n) {}
    Seg(vector<Info> a) : Seg((int)a.size()) { bld(a, 1, 0, n); }
    void pull(int p) { t[p] = t[2 * p] + t[2 * p + 1]; }
    void bld(vector<Info>& a, int p, int l, int r) {
        if (r - l == 1) { t[p] = a[l]; return; }
        int m = (l + r) / 2;
        bld(a, 2 * p, l, m); bld(a, 2 * p + 1, m, r); pull(p);
    }
    void modify(int p, int l, int r, int x, Info v) {
        if (r - l == 1) { t[p] = v; return; }
        int m = (l + r) / 2;
        x < m ? modify(2 * p, l, m, x, v) : modify(2 * p + 1, m, r, x, v);
        pull(p);
    }
    void modify(int x, Info v) { modify(1, 0, n, x, v); }
    Info qry(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) return {};
        if (l >= x && r <= y) return t[p];
        int m = (l + r) / 2;
        return qry(2 * p, l, m, x, y) + qry(2 * p + 1, m, r, x, y);
    }
    Info qry(int l, int r) { return qry(1, 0, n, l, r); }
};

// ===== 区间修改 + 区间查询 (Lazy) =====
struct LazySeg {
    int n; vector<Info> t; vector<Tag> tag;
    LazySeg(int n) : n(n), t(4 * n), tag(4 * n) {}
    LazySeg(vector<Info> a) : LazySeg((int)a.size()) { bld(a, 1, 0, n); }
    void pull(int p) { t[p] = t[2 * p] + t[2 * p + 1]; }
    void aply(int p, Tag v) { t[p].apply(v); tag[p].apply(v); }
    void push(int p) { aply(2 * p, tag[p]); aply(2 * p + 1, tag[p]); tag[p] = {}; }
    void bld(vector<Info>& a, int p, int l, int r) {
        if (r - l == 1) { t[p] = a[l]; return; }
        int m = (l + r) / 2;
        bld(a, 2 * p, l, m); bld(a, 2 * p + 1, m, r); pull(p);
    }
    void modify(int p, int l, int r, int x, Info v) {
        if (r - l == 1) { t[p] = v; return; }
        int m = (l + r) / 2; push(p);
        x < m ? modify(2 * p, l, m, x, v) : modify(2 * p + 1, m, r, x, v);
        pull(p);
    }
    void modify(int x, Info v) { modify(1, 0, n, x, v); }
    void upd(int p, int l, int r, int x, int y, Tag v) {
        if (l >= y || r <= x) return;
        if (l >= x && r <= y) { aply(p, v); return; }
        int m = (l + r) / 2; push(p);
        upd(2 * p, l, m, x, y, v); upd(2 * p + 1, m, r, x, y, v); pull(p);
    }
    void upd(int l, int r, Tag v) { upd(1, 0, n, l, r, v); }
    Info qry(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) return {};
        if (l >= x && r <= y) return t[p];
        int m = (l + r) / 2; push(p);
        return qry(2 * p, l, m, x, y) + qry(2 * p + 1, m, r, x, y);
    }
    Info qry(int l, int r) { return qry(1, 0, n, l, r); }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<Info> a(n);
    for (auto& x : a) { cin >> x.sum; x.len = 1; }
    LazySeg seg(a);
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, v; cin >> l >> r >> v;
            seg.upd(l - 1, r, {v}); // 1-indexed -> 0-indexed [l-1, r)
        } else {
            int l, r; cin >> l >> r;
            cout << seg.qry(l - 1, r).sum << '\n';
        }
    }
}
