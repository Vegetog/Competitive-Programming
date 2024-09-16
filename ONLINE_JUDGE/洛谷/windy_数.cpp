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
    int a,b;
    cin>>a>>b;
    string L=to_string(a-1),R=to_string(b);

    string s=R;
    vector<vector<int>> f(s.size(),vector<int>(10,-1));

    function<int(int,bool,int,int)> dfs=[&](int u,bool high,int lead,int las){
        if(u==s.size()) return !lead ? 1 : 0;
        if(!high&&!lead&&f[u][las]!=-1) return f[u][las];
        int res=0;
        if(lead) res=dfs(u+1,0,1,-1);
        int l=0,r=high ? s[u]-'0' : 9;
        for(int i=max(l,lead);i<=r;i++){
            if(abs(i-las)<2) continue;
            res+=dfs(u+1,high&&i==r,0,i);
        }
        if(!high&&!lead) f[u][las]=res;
        return res;
    };

    int ansr=dfs(0,1,1,-1);
    s=L;
    for(auto &it : f){
        for(auto &i : it) i=-1;
    }
    int ansl=dfs(0,1,1,-1);
    cout<<ansr-ansl<<"\n";
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
