#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
#ifdef __clang__
    template <typename T>
    inline int my_lg(T n) {
        return (n > 0) ? static_cast<int>(log2(n)) : -1;
    }
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E5 + 10;

int x[N];
int k;
struct Tree{
    int n;
    vector<vector<int>> g;
    vector<int> fa,dep,sz,son,top,val;
    int pr[N],sf[N];
    Tree(int n_):n(n_),g(n),fa(n),dep(n),sz(n),son(n),top(n),val(n){}

    inline void add_edge(int u,int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs1(int u){
        sz[u] = 1;
        dep[u] = dep[fa[u]] + 1;
        for(auto v:g[u]){
            if(v==fa[u]) continue;
            fa[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if(sz[v]>sz[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u,int h){
        top[u] = h;
        if(son[u]) dfs2(son[u],h);
        for(auto v:g[u]){
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    int LCA(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]]) x = fa[top[x]];
            else y = fa[top[y]];
        }
        return dep[x]<dep[y]?x:y;
    }

    void init(){
        dfs1(1);
        dfs2(1,1);
        pr[1]=x[1];
        sf[k]=x[k];
        for(int i=2;i<=k;i++){
            pr[i]=LCA(pr[i-1],x[i]);
        }
        for(int i=k-1;i>=1;i--){
            sf[i]=LCA(sf[i+1],x[i]);
        }
    }
    int get(int i){
        if(i==1) return sf[2];
        if(i==k) return pr[k-1];
        return LCA(pr[i-1],sf[i+1]);
    }
};
void SINGLE_TEST() 
{
    int n;
    cin>>n>>k;
    Tree a(n+1),b(n+1);
    for(int i=1;i<=k;i++) cin>>x[i];
    for(int i=1;i<=n;i++){
        cin>>a.val[i];
    }
    for(int i=2;i<=n;i++){
        int fa;cin>>fa;
        a.add_edge(fa,i);
    }
    for(int i=1;i<=n;i++){
        cin>>b.val[i];
    }
    for(int i=2;i<=n;i++){
        int fa;cin>>fa;
        b.add_edge(fa,i);
    }

    int ans=0;
    a.init();b.init();
    for(int i=1;i<=k;i++){
        ans+=(a.val[a.get(i)]>b.val[b.get(i)]);
    }
    cout<<ans<<"\n";
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    while (SAMPLES--) SINGLE_TEST();
}
