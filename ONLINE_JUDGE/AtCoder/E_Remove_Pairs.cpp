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
    int n;cin>>n;
    vector<int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    vector<int> dp(1<<n,-1);
    dp[0]=0;
    for(int stu=1;stu<(1<<n);stu++){
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if((stu>>(i-1)&1) && (stu>>(j-1)&1) && (a[i]==a[j] || b[i]==b[j])){
                    int new_stu=stu^(1<<(i-1))^(1<<(j-1));
                    if(dp[new_stu]==0){
                        dp[stu]=1;
                    }
                }
            }
        }
        if(dp[stu]==-1){
            dp[stu]=0;
        }
    }
    cout<<(dp[(1<<n)-1]?"Takahashi":"Aoki")<<"\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
