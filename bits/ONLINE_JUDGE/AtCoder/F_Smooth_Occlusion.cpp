#ifndef ONLINE_JUDGE
#include "QwQ.h" 
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long; 
using ull = unsigned long long;

constexpr ll N = (int)2E6 + 10, INF = (ll)2E18 + 10;
/*
4 3
3 1 4
4 1 5
5 9 14
2 6 8

3 1 0
4 0 1
4 0 10
2 2 4
*/
// 50 52 3
void SINGLE_TEST(int &CUR) 
{
    int n,x;
    cin>>n>>x;
    vector<int> u(n+1),d(n+1);
    for(int i=1;i<=n;i++){
        cin>>u[i]>>d[i];
    }

    ll ans=0;
    int mn=INF;
    for(int i=2;i<=n;i++){
        if(u[i]>u[i-1]+x){
            ans+=u[i]-u[i-1]-x;
            u[i]=u[i-1]+x;
        }
        mn=min(mn,u[i]+d[i]);
    }
    for(int i=n-1;i>=1;i--){
        if(u[i]>u[i+1]+x){
            ans+=u[i]-u[i+1]-x;
            u[i]=u[i+1]+x;
        }
        mn=min(mn,u[i]+d[i]);
    }
    for(int i=1;i<=n;i++){
        ans+=u[i]+d[i]-mn;
    }
    cout<<ans<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(15);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST(CUR);
    }
}
