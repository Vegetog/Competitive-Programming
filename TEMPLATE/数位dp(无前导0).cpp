#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int A,B;
    cin>>A>>B;
    A--;
    string L,R;
    L=to_string(A);
    R=to_string(B);
    // L=string(R.size()-L.size(),'0')+L;

    int st=0;
    string s=R;
    vector<vector<vector<ll>>> f(s.size(),vector<vector<ll>>(170,vector<ll>(170,-1LL)));

    function<ll(int,bool,int,int)> dfs=[&](int u,bool high,int sum,int n)->ll{
        if(sum>st) return 0;
        if(u==s.size()) return (sum==st && n==0); // return 1
        if(!high && f[u][sum][n]!=-1) return f[u][sum][n]; // 需要确定一个对后面来说唯一的状态
        int l=0,r=high ? s[u]-'0' : 9;
        ll res=0;
        for(int i=l;i<=r;i++){
            res+=dfs(u+1,high&&i==r,sum+i,(n*10+i)%st);
        }
        if(!high) f[u][sum][n]=res;
        return res;
    };
    // 10 12 18
    ll ans=0;
    for(int i=1;i<=18*9;i++){
        st=i;
        for(auto &it1:f) 
            for(auto &it2:it1) 
                for(auto &it3:it2) it3=-1;
        ans+=dfs(0,1,0,0);
    }
    s=L;
    for(int i=1;i<=18*9;i++){
        st=i;
        for(auto &it1:f) 
            for(auto &it2:it1) 
                for(auto &it3:it2) it3=-1;
        ans-=dfs(0,1,0,0);
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
