#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
// #define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int n,m;
    cin>>n>>m;
    if(!n && !m) exit(0);

    string L=to_string(n-1),R=to_string(m);
    // L=string(R.size()-L.size(),'0')+L;

    string s=R;
    vector<vector<int>> f(s.size(),vector<int>(10,-1));

    function<int(int,bool,int)> dfs=[&](int u,bool high,int las){
        if(u==s.size()) return 1;
        if(!high && f[u][las]!=-1) return f[u][las];
        int l=0,r=high ? s[u]-'0' : 9;
        int res=0;
        for(int i=l;i<=r;i++){
            if(i==4 || las==6&&i==2) continue;
            res+=dfs(u+1,high&&i==r,i);
        }
        if(!high) f[u][las]=res;
        return res;
    };
    ll ansr=dfs(0,1,0);
    s=L;
    for(auto &it : f){
        for(auto &i : it) i=-1;
    }
    ll ansl=dfs(0,1,0);
    // cout<<ansr<<" "<<ansl<<"\n";
    cout<<ansr-ansl<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; ; CUR++) {
        SINGLE_TEST();
    }

    return 0;
}
