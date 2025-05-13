#ifndef ONLINE_JUDGE
#include "QwQ" 
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long; 
using ull = unsigned long long;
using P2 = pair<int,int>;

constexpr ll N = (int)2E6 + 10, INF = (ll)2E18 + 10;

void SINGLE_TEST(int &CUR) 
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }

    vector<int> cnt(n*m+1,0);
    vector<int> st;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cnt[a[i][j]]=max(cnt[a[i][j]],1LL);
            if(i-1>=1&&a[i][j]==a[i-1][j]) cnt[a[i][j]]=max(cnt[a[i][j]],2LL);
            if(j-1>=1&&a[i][j]==a[i][j-1]) cnt[a[i][j]]=max(cnt[a[i][j]],2LL);
            if(i+1<=n&&a[i][j]==a[i+1][j]) cnt[a[i][j]]=max(cnt[a[i][j]],2LL);
            if(j+1<=m&&a[i][j]==a[i][j+1]) cnt[a[i][j]]=max(cnt[a[i][j]],2LL);
        }
    }

    for(int i=1;i<=n*m;i++){
        st.push_back(cnt[i]);
    }

    sort(st.begin(),st.end(),greater<>());

    ll ans=0;
    for(int i=1;i<st.size();i++){
        ans+=st[i];
    }
    cout<<ans<<"\n";
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
