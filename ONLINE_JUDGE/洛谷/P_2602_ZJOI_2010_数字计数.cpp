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
    ll l,r;
    cin>>l>>r;

    vector<int> dp(15);
    for(int i=1;i<=14;i++){
        dp[i]=dp[i-1]*10+(int)pow(10,i-1);
    }

    auto solve=[&](ll x)->vector<int>{
        vector<int> ans(10);
        vector<int> d;
        while(x>0){
            d.emplace_back(x%10);
            x/=10;
        }
        int n=d.size();
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<=9;j++){
                ans[j]+=dp[i]*d[i];
            }
            for(int j=0;j<d[i];j++){
                ans[j]+=(int)pow(10,i);
            }
            ll t=0;
            for(int j=i-1;j>=0;j--){
                t=t*10+d[j];
            }
            ans[d[i]]+=t+1;
            ans[0]-=(int)pow(10,i);
        }
        return ans;
    };

    auto al=solve(l-1),ar=solve(r);
    for(int i=0;i<=9;i++){
        cout<<ar[i]-al[i]<<" \n"[i==9];
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

    return 0;
}
