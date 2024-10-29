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

//string下标从零开始,hash下标从1开始,因为init里面S=‘ ’+S
struct Shash{  
    const ll base[2]={29,31};
    const ll hashmod[2]={(ll)1e9+9,998244353};
    
    array<vector<ll>,2>hsh;
    array<vector<ll>,2>pwMod;
    void init(string S){
        int n=S.size();S=' '+S;
        hsh[0].resize(n+1),hsh[1].resize(n+1);
        pwMod[0].resize(n+1),pwMod[1].resize(n+1);
        for(int i=0;i<2;++i){
            pwMod[i][0]=1;
            for (int j=1;j<=n;++j){
                pwMod[i][j]=pwMod[i][j-1]*base[i]%hashmod[i];
                hsh[i][j]=(hsh[i][j-1]*base[i]+S[j])%hashmod[i];
            }
        }
    }
    pair<ll,ll>get(int l,int r){
        pair<ll,ll> ans;
        ans.first=(hsh[0][r]-hsh[0][l-1]*pwMod[0][r-l+1])%hashmod[0];
        ans.second=(hsh[1][r]-hsh[1][l-1]*pwMod[1][r-l+1])%hashmod[1];
        ans.first=(ans.first+hashmod[0])%hashmod[0];
        ans.second=(ans.second+hashmod[1])%hashmod[1];
        return ans;
    }
};
bool same(Shash &a,int la,int ra,Shash &b,int lb,int rb){
    return a.get(la,ra)==b.get(lb,rb);
}
/*
//初始化：
string s,t;
Shash a,b;
a.init(s),b.init(t);
//比较  下标都是从1开始
same(a,la,ra,b,lb,rb);
same(a,l1,r1,a,l2,r2);
*/
void SINGLE_TEST() 
{
    int n,c;
    cin>>n>>c;
    ll ans=0;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        
    }
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
