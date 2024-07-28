/*
keys：小范围(k<1e6)预处理解决，大范围用根号附近或二分解决
	对于jia的爆longlong问题的处理需要注意

题目链接：https://codeforces.com/contest/1846/problem/E2
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;
map<int,int> mp;
void solve()
{
	ll n;cin>>n;
	if(mp[n]>0){
		cout<<"YES"<<'\n';
		return ;
	}
	ll now=sqrt(n);
	while(now*now+now+1<n) now++;
	while(now*now+now+1>n) now--;
	if(now>1&&now*now+now+1==n){
		cout<<"YES"<<'\n';
		return ;
	}else{
		cout<<"NO"<<'\n';
	}
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
	for(int k=2;k<=1e6;k++){
		ll sum=1+k+k*k,jia=k*k;
		while(sum<=INF){
			mp[sum]++;
            if(INF/k<jia){//防止jia爆longlong，然后变成随机数无法跳出while造成TLE
                break;
            }
			jia*=k;
			sum+=jia;
		}
	}
    
    int T=1;
	cin>>T;
	while(T--) solve();
    
}