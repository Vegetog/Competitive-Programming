#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
#ifdef __clang__
    template <typename T>
    inline int my_lg(T n) {return (n > 0) ? static_cast<int>(log2(n)) : -1;}
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int n,k;
    cin>>n>>k;
    vector<int> a(k+1);
    for(int i=1;i<=k;i++){
        cin>>a[i];
    }
    vector<vector<vector<PII>>> g(2,vector<vector<PII>>(n+1));
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[0][u].push_back({v,w});
        g[0][v].push_back({u,w});
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[1][u].push_back({v,w});
        g[1][v].push_back({u,w});
    }
    
    vector<vector<int>> dp(n+1,vector<int>(2));
    function<void(int,int,int)> dfs=[&](int u,int fa,int id){
        dp[u][id]=0;
        for(auto [v,w]:g[id][u]){
            if(v==fa) continue;
            dfs(v,u,id);
            
            dp[u][id]=max(dp[u][id],dp[v][id]+w);
            dp[u][id]=max(dp[u][id],dp[v][id^1]);
            dp[u]
        }
    };  
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
