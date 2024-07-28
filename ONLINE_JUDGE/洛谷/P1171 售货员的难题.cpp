#include <bits/stdc++.h>
// #define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
#ifdef __clang__
template <typename T>
inline int my_lg(T n) {
    return (n > 0) ? static_cast<int>(log2(n)) : -1;
}
#define __lg my_lg
#define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
#include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E6 + 10;

void SINGLE_TEST() {
    int n;
    cin >> n;
    vector<vector<int>> d(n + 1,vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> d[i][j];
        }
    }
    vector<vector<int>> f(1<<n,vector<int>(n+1,1E9));
    f[1][1]=0;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         // if(i==j) continue;
    //         for(int k=0;k<(1<<n);k++){
    //             if(k&(1<<(j-1)) && !(k&(1<<(i-1)))){
    //                 // if(i==2 && j==3){
    //                 //     cout<<"OK"<<"\n";
    //                 //     cout<<k<<"\n";
    //                 //     cout<<f[k][j]<<" "<<d[j][i]<<"\n";
    //                 //     cout<<f[k|(1<<(i-1))][i]<<"\n";
    //                 // }
    //                 f[k|(1<<(i-1))][i]=min(f[k|(1<<(i-1))][i],f[k][j]+d[j][i]);
    //             }
    //         }
    //     }
    // }
    for(int k=0;k<(1<<n);k++){
        for(int i=1;i<=n;i++){
            if(k&(1<<(i-1))){
                continue;
            }
            for(int j=1;j<=n;j++){
                if(k&(1<<(j-1))){
                    f[k|(1<<(i-1))][i]=min(f[k|(1<<(i-1))][i],f[k][j]+d[j][i]);
                }
            }
        }
    }
    // debug(f);

    int ans=1E9;
    for(int k=2;k<=n;k++){
        ans=min(ans,f[(1<<n)-1][k]+d[k][1]);
    }
    cout<<ans<<"\n";
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    while (SAMPLES--) SINGLE_TEST();
}
