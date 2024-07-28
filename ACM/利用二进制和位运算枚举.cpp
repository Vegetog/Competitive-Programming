/*
keys：用二进制来表示枚举所有取字母的情况(利用位运算)
	字母数较少可以暴力枚举
题目链接：https://codeforces.com/contest/1778/problem/C
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;

ll n,k;
string a,b;
map<char,int> num;
map<char,int> id;

void solve()
{
	cin>>n>>k;cin>>a>>b;
    ll pm=0;
	for(int i=0;i<n;i++){
    //    if(a[i]==b[i]) continue;
		num[a[i]]++;
		if(num[a[i]]==1){
            id[a[i]]=++pm;
		}
	}
	k=min(k,pm);
	ll ans1=0;
	for(int S=0;S<(1<<pm);S++){
		if(__builtin_popcountll(S)!=k) continue;
		ll ans=0;
		ll l=0,r=0;

        while(l<n&&r<n){
            r=l;
            while(r<n&&(a[r]==b[r]||(S>>(id[a[r]]-1)&1))){
			    r++;
	    	}
		    ans+=(r-l)*(r-l+1)/2;
		    l=r;
            l++;
        }
		ans1=max(ans1,ans);

	}
	cout<<ans1<<'\n';
	id.clear();num.clear();
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
	cin>>T;
    while(T--){
    	solve();
	}
}