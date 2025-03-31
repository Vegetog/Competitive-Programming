#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e5 + 10, INF = 1e9;
int a[N];
struct PresidentTree{
    struct Node
    {
        int l, r;
        int cnt;
    };
    vector<Node> tr;
    // PresidentTree() : tr(N << 5) {}
    int idx ;
    vector<int> root;
    PresidentTree() : tr(N << 5),idx(0), root(N, 0) {}

    void insert(int &u, int v, int l, int r, int x)
    {
        u = ++ idx;
        tr[u] = tr[v];
        tr[u].cnt ++ ;
        if(l == r) return ;
        int mid = l + r >> 1;
        if(x <= mid) insert(tr[u].l, tr[v].l, l, mid, x);
        else insert(tr[u].r, tr[v].r, mid + 1, r, x);
    }

    int query(int p, int q, int l, int r, int k)
    {
        if(l == r) return l;
        int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
        int mid = l + r >> 1;
        if(k <= cnt) return query(tr[p].l, tr[q].l, l, mid, k);
        if(k > cnt) return query(tr[p].r, tr[q].r, mid + 1, r, k - cnt);
    }
};

/*
5 5
25957 6405 15770 26287 26465
2 2 1
3 4 1
4 5 1
1 2 2
4 4 1
*/
int main()
{
    int n,m;
    cin >> n >> m;
    // vector<int> a(n+1);
    PresidentTree pst;
    for(int i = 1 ; i <= n ; i ++ )
    {
        cin >> a[i];
        pst.insert(pst.root[i], pst.root[i - 1], -INF, INF, a[i]);
    }
    
    for(int i = 1 ; i <= m ; i ++ )
    {
        int l, r, k;
        cin >> l >> r >> k;
        cout << pst.query(pst.root[l - 1], pst.root[r], -INF, INF, k) << endl;
    }

    // 释放空间
    // delete[] pst.tr;
    // delete[] pst.root;
    
    return 0;
}