#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;
struct D{
    int l,r;
}a[N];
bool cmp(D x,D y){
    if(x.l==y.l) return x.r<y.r;
    return x.l<y.l;
}
void solve()
{
	int L,m;cin>>L>>m;
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        if(x>y) swap(x,y);
        a[i].l=x;a[i].r=y;
    }
    sort(a+1,a+m+1,cmp);
    ll ans=0,l=a[1].l,r=a[1].r;
    for(int i=2;i<=m;i++){
        if(a[i].l>r){
            ans+=r-l+1;
            l=a[i].l;r=a[i].r;
        }else{
            r=max(r,a[i].r);
        }
    }
    ans+=r-l+1;
    cout<<L-ans+1<<'\n';
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--){
    	solve();
	}
}