#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=3e2+10;
const int mod=1e9;
typedef pair<int,int> PII;

ll n;
ll m[N];
ll f[N][N];
ll sum[N];
ll dp[N][N];
void solve()
{
    memset(f,2e9,sizeof f);
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>m[i];
		sum[i]=sum[i-1]+m[i];
	}
    for(ll j=2;j<=n;j++){
		for(ll i=j-1;i>=1;i--){
			ll mn=INF;
			for(ll k=i;k+1<=j;k++){
				mn=min(mn,f[i][k]+f[k+1][j]+sum[j]-sum[i-1]);
			}
			f[i][j]=mn;
		}
	}
    for(ll j=2;j<=n;j++){
		for(ll i=j-1;i>=1;i--){
			ll mn=-1;
			for(ll k=i;k+1<=j;k++){
				mn=max(mn,dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
			}
			dp[i][j]=mn;
		}
	}
	// for(ll i=1;i<=n-1;i++){
	// 	for(ll j=i+1;j<=n;j++){
	// 		ll mn=INF;
	// 		for(ll k=i;k+1<=j;k++){
	// 			mn=min(mn,f[i][k]+f[k+1][j]+sum[j]-sum[i-1]);
	// 		}
	// 		f[i][j]=mn;
	// 	}
	// }
	cout<<f[1][n]<<'\n'<<dp[1][n];
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