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
    int n;cin>>n;
    vector<PII> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
    }

    sort(a.begin()+1,a.end());

    ll ans=INF;
    vector<int> dp(n+1,INF);
    dp[0]=0;
    a[0].second=-INF;
    for(int i=1;i<=n;i++){
        auto [le,ri]=a[i];
        int t=ri-le;
        int mx=-INF;
        for(int j=i-1;j>=0;j--){
            auto [l,r]=a[j];
            if(r<le && r>=mx) {
                dp[i]=min(dp[i],dp[j]+t);
                mx=max(mx,l);
            }
        }
        if(ri>=a[n].first) ans=min(ans,dp[i]);
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
