#ifndef ONLINE_JUDGE
#include "QwQ" 
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long; 
using ull = unsigned long long;

constexpr ll N = (int)2E6 + 10, INF = (ll)2E18 + 10;

void SINGLE_TEST(int &CUR) 
{
    int n;
    cin>>n;
    vector<int> b(n+1);
    for(int i=1;i<=n-2;i++){
        cin>>b[i];
    }
    for(int i=1;i+2<=n;i++){
        if(b[i]==1&&b[i+1]==0&&b[i+2]==1){
            cout<<"NO\n";
            return ;
        }
    }
    cout<<"YES\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(15);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST(CUR);
    }
}
