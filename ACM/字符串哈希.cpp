#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int long long
#define INF (long long)2e+18
//const int mod=1e9;
const int N=2e6+10,P=131;

ull h[N],p[N];

ull query(int l,int r){
    return h[r]-h[l-1]*p[r-l+1];
}
void solve()
{
	int n,m;
    cin>>n>>m;
    string s;cin>>s;

    h[0]=0;p[0]=1;
    for(int i=0;i<n;i++){
        p[i+1]=p[i]*P;
        h[i+1]=h[i]*P+(int)s[i];
    }
    while(m--){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        if(query(l1,r1) == query(l2,r2)) printf("Yes\n");
        else printf("No\n");
    }
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
	//cin>>T;
    while(T--){
    	solve();
	}
}