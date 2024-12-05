#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

void SINGLE_TEST() 
{
    int n;
    cin>>n;
    vector<array<int,3>> a(n+1);
    map<PII,int> mp;
    // map<int,int> mpl,mpr;
    for(int i=1;i<=n;i++){
        cin>>a[i][0]>>a[i][1];
        a[i][2]=i;
        mp[{a[i][0],a[i][1]}]++;
        // if(!mpl.count(a[i][0])){
        //     mpl[a[i][0]]=a[i][1];
        // }else{
        //     mpl[a[i][0]]=max(mpl[a[i][0]],a[i][1]);
        // }
        // if(!mpr.count(a[i][1])){
        //     mpr[a[i][1]]=a[i][0];
        // }else{
        //     mpr[a[i][1]]=min(mpr[a[i][1]],a[i][0]);
        // }
    }

    sort(a.begin()+1,a.end(),[&](auto x,auto y){
        if(x[0]==y[0]) return x[1]>y[1];
        return x[0]<y[0];
    });

    vector<int> ans(n+1);   
    multiset<int> sel;
    multiset<int> ser;
    for(int i=1;i<=n;i++){
        auto [l,r,id] = a[i];
        // cout<<l<<" "<<r<<"\n";
        if(i>1 && mp[{l,r}]==1){
            auto imnr=ser.lower_bound(r);
            if(imnr!=ser.end()){
                int mnr=*imnr;
                ans[id]+=mnr-r;
            }
        }
        ser.insert(r);
        // if(mp[{l,r}]>1){
        //     ans[id]=0;
        // }
    }
    // SE;
    // for(int i=1;i<=n;i++){
    //     cout<<ans[i]<<"\n";
    // }
    // SE;
    sort(a.begin()+1,a.end(),[&](auto x,auto y){
        if(x[1]==y[1]) return x[0]<y[0];
        return x[1]>y[1];
    });
    for(int i=1;i<=n;i++){
        auto [l,r,id] = a[i];
        // cout<<l<<" "<<r<<"\n";
        // debug(sel);
        if(i>1 && mp[{l,r}]==1){
            // auto imxl=upper_bound(sel.begin(),sel.end(),l);
            auto imxl=sel.upper_bound(l);
            if(imxl==sel.begin()) {
                sel.insert(l);
                // SE;
                continue;
            }
            imxl--;
            int mxl=*imxl;
            // cout<<mxl<<"\n";
            ans[id]+=l-mxl;
        }
        sel.insert(l);
        // if(mp[{l,r}]>1){
        //     ans[id]=0;
        // }
        // SE;
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<"\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
/*---------------------------------------------------------------------------------
struct CMP{bool operator()(const int & x, const int &y) const{ return x<y; }};

template <class T>
map<T, int> sortMap(const map<T, int> mp) {
    vector<pair<T, int>> v(mp.begin(), mp.end());
    sort(v.begin(), v.end(),
         [&](auto x, auto y) { return x.second < y.second; });
    map<T, int> ans;
    for (auto [lo, v] : v) {
        ans[lo] = v;
    }
    return ans;
}

std::mt19937_64 rng(
    std::chrono::steady_clock::now().time_since_epoch().count()
);

template <class T>
void shuffle(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
    std::shuffle(first, last, rng);
}
---------------------------------------------------------------------------------*/
