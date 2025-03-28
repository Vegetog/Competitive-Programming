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
    int n,m;
    cin>>n>>m;

    const int T = sqrt(n);

    vector<int> st(T+1), ed(T+1);
    for(int i=1; i<=T; i++){
        st[i] = n / T * (i - 1) + 1; // st[i]表示i号块的第一个元素的下标
        ed[i] = n / T * i; // ed[i]表示i号块的最后一个元素的下标
    }
    ed[T] = n;
    vector<int> bel(n+1),siz(T+1);
    for(int i=1; i<=T; i++){
        siz[i] = ed[i] - st[i] + 1;
        for(int j=st[i]; j<=ed[i]; j++){
            bel[j] = i; // 表示j号元素归属于i块
        }
    }


    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    vector<int> sum(T+1),tag(T+1);
    for(int i=1;i<=T;i++){
        for(int j=st[i];j<=ed[i];j++){
            sum[i]+=a[j];
        }
    }

    auto rangeApply=[&](int l,int r,int k)->void{
        if(bel[l]==bel[r]){
            for(int i=l;i<=r;i++){
                a[i]+=k;
                sum[bel[i]]+=k;
            }
            return ;
        }
        for(int i=l;i<=ed[bel[l]];i++){
            a[i]+=k;
            sum[bel[i]]+=k;
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            tag[i]+=k;
        }
        for(int i=st[bel[r]];i<=r;i++){
            a[i]+=k;
            sum[bel[i]]+=k;
        }
    };

    auto rangeQuery=[&](int l,int r)->ll{
        ll res=0;
        if(bel[l]==bel[r]){
            for(int i=l;i<=r;i++){
                res+=a[i]+tag[bel[i]];
            }
            return res;
        }
        for(int i=l;i<=ed[bel[l]];i++){
            res+=a[i]+tag[bel[i]];
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            res+=sum[i]+tag[i]*siz[i];
        }
        for(int i=st[bel[r]];i<=r;i++){
            res+=a[i]+tag[bel[i]];
        }
        return res;
    };

    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            int k;cin>>k;
            rangeApply(x,y,k);
        }else{
            cout<<rangeQuery(x,y)<<"\n";
        }
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
}
