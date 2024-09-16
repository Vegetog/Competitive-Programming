#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
constexpr int M = 2520;
constexpr int K = 48;

std::string& operator--(std::string& num) {
    int n = num.size();
    for (int i = n - 1; i >= 0; --i) {
        if (num[i] > '0') {
            num[i]--;
            break;
        } else {
            num[i] = '9';
        }
    }
    if (num[0] == '0' && num.size() > 1) {
        num.erase(num.begin());
    }    
    return num;
}

ll LCM[M+1][M+1];
int tot=0;
int mp[M+1];
ll f[20][K+1][M+1];

void SINGLE_TEST() 
{
    string L,R;
    cin>>L>>R;
    --L;
    L=string(R.size()-L.size(),'0')+L;
    string s=R;

    function<ll(int,bool,int,int)> dfs=[&](int u,bool high,int lm,int n)->ll{
        if(u==s.size()) return (lm>0&&n%lm==0);
        if(mp[lm]==-1) mp[lm]=tot++;
        if(!high && f[u][mp[lm]][n]!=-1) return f[u][mp[lm]][n]; // 需要确定一个对后面来说唯一的状态
        int l=0,r=high ? s[u]-'0' : 9;
        ll res=0;
        for(int i=l;i<=r;i++){
            res+=dfs(u+1,high&&i==r,LCM[lm][i],(n*10+i)%M);
        }
        if(!high) f[u][mp[lm]][n]=res;
        return res;
    };

    for(int i=0;i<20;i++)
        for(int j=0;j<=K;j++)
            for(int k=0;k<=M;k++)
                f[i][j][k]=-1;
    ll ans=dfs(0,1,0,0);
    s=L;
    // for(int i=0;i<20;i++)
    //     for(int j=0;j<=K;j++)
    //         for(int k=0;k<=M;k++)
    //             f[i][j][k]=-1;
    ans-=dfs(0,1,0,0);
    cout<<ans<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    for(int i=0;i<=M;i++){
        mp[i]=-1;
    }
    for(int i=0;i<=M;i++){
        for(int j=0;j<=M;j++){
            LCM[i][j]= i*j==0 ? max(i,j) : lcm(i,j);
        }
    }
    // for(int i=0;i<20;i++)
    //     for(int j=0;j<=K;j++)
    //         for(int k=0;k<=M;k++)
    //             f[i][j][k]=-1;
    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }

    return 0;
}
