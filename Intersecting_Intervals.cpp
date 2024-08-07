#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h" 
#endif

#define int long long
#define new _MY_NEW_

using namespace std;
using ll = long long;
using PII = array<int, 2>;

constexpr long long INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int n,m;
    cin>>n>>m;
    vector<vector<ll>> a(n+5,vector<ll>(m+5));
    vector<ll> L0(m+5),L1(m+5),R0(m+5),R1(m+5),f(m+5);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            L0[j]=max(0LL,L0[j-1])+a[i][j];
            if(j==1)L1[j]=L0[j]+f[j];
            else L1[j]=max(L1[j-1]+a[i][j],L0[j]+f[j]);
        }
        for(int j=m;j>=1;j--){
            R0[j]=max(0LL,R0[j+1])+a[i][j];
            if(j==m)R1[j]=R0[j]+f[j];
            else R1[j]=max(R1[j+1]+a[i][j],R0[j]+f[j]);
        }
        for(int j=1;j<=m;j++){
            f[j]=max(L0[j]+R1[j]-a[i][j],L1[j]+R0[j]-a[i][j]);
//			cerr<<i<<' '<<j<<' '<<f[j]<<endl;
        }
    }
    ll ans=-1e18;
    for(int j=1;j<=m;j++)
        ans=max(ans,f[j]);
    cout<<ans<<"\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
