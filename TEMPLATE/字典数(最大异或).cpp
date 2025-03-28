#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 1E5 + 10;
constexpr int M = N * 31;
constexpr int B = 31;

void SINGLE_TEST() 
{
    int n;cin>>n;
    vector<vector<PII>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    vector<int> a;
    function<void(int,int,int)> dfs=[&](int u,int fa,int w){
        a.push_back(w);
        for(auto [v,ww] : g[u]){
            if(v==fa) continue;
            dfs(v,u,w^ww);
        }
    };
    dfs(1,-1,0);

    int tot=1;
    vector<vector<int>> tr(M+1,vector<int>(2));

    for(auto x : a){
        int p=1;
        for(int i=B-1;i>=0;i--){
            int c=x>>i&1;
            if(tr[p][c]==0){
                tr[p][c]=++tot;
            }
            p=tr[p][c];
        }
    }
    int ans=0;
    for(auto x : a){
        int p=1;
        int res=0;
        for(int i=B-1;i>=0;i--){
            int c=x>>i&1;
            if(tr[p][c^1]){
                p=tr[p][c^1];
                res+=(1<<i);
            }else if(tr[p][c]){
                p=tr[p][c];
            }else{
                assert(1);
            }
        }
        ans=max(ans,res);
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
}
