#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
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
    int n;cin>>n;
    vector<int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i]^b[i-1];
    };
    ll ans=0;
    for(int i=0;i<=30;i++){
        vector<int> cnt(2);
        for(int j=0;j<=n;j++){
            int t=b[j]>>i&1;
            ans+=(1LL<<i)*cnt[t^1];
            cnt[t]++;
        }
    }
    for(int i=1;i<=n;i++) ans-=a[i];
    cout<<ans<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
