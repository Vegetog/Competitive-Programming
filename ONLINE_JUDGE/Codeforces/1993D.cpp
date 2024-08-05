#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 1E7 + 10;
#ifdef __clang__
    template <typename T>
    inline int my_lg(T n) {return (n > 0) ? static_cast<int>(log2(n)) : -1;}
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int n,k;
    cin>>n>>k;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int lea=n%k;
    if(lea==0) lea=k;   
    auto check=[&](int x){
        vector<int> dp(lea+1,-INF);
        dp[0]=0;
        for(int i=1;i<=n;i++){
            int j=(i-1)%k+1;
            if(j<=lea)
                dp[j]=max(dp[j],dp[j-1]+(a[i]>=x ? 1 : -1));
        }
        return dp[lea]>0;
    };
    int l=0,r=1E9;
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid)){
            l=mid;
        }else{
            r=mid-1;
        }
    }
    cout<<l<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
