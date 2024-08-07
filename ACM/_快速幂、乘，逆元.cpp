#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=998244353;
typedef pair<int,int> PII;

long long qpow1(long long a, long long b) {
  long long res = 1;
  while (b > 0) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}
template<class T>
constexpr T power(T a, ll b,ll mod) {
    a %= mod;
    T res = 1;
    for (; b; b /= 2, a *= a, a %= mod) {
        if (b % 2) {
            res *= a;
            res %= mod;
        }
    }
    return res;
}
ll qpow(ll a,ll b,ll m=mod) //快速幂求a^b%m; 
{
    a%=m;
	ll ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%m;
		b>>=1;
		a=a*a%m;
	}
	return ans;
}
ll ksc(ll a, ll b, ll mod=mod) {
    ll ans = 0;
    while(b != 0) {
	if(b & 1 != 0) {
	    ans = (ans + a) % mod;
	}
	a = (a + a) % mod;
	b >>= 1;
    }
    return ans;
}
ll inverse(ll a,ll mod=mod){
    return qpow(a,mod-2,mod);
}
/*
对每一个当前的金额都做一次操作，但是在一定区间内的金额可以输的次数是一样的从n优化成logn
*/
void solve()
{
	ll n,m;
    cin>>n>>m;m+=n;
    ll ans=1;
    ll fz=1,fm=1;
    while(n<m){
        ll d=__lg(n+1);//最多可以输的次数

        int sigx,sigy=qpow(2,d)%mod;sigx=sigy-1;

    //    ll sj=qpow(2,d+1,0)-1; 这样就会有问题？
     //   ll sj=(1<<(d+1))-1;
        ll sj=qpow(2,d+1)-1; 
    //    cout<<sj<<' '<<qpow1(2,d+1)-1<<'\n';
        sj=min(sj,m);
        int len=sj-n;
    //    if()
        //int len=min(m,sigy%mod*2%mod-1)-n;

        fz=ksc(fz,qpow(sigx,len));
        fm=ksc(fm,qpow(sigy,len));
        // fz=(fz*qpow(sigx,len)%mod)%mod;
        // fm=(fm*qpow(sigy,len)%mod)%mod;
        //fz*=qpow(sigx,len,mod)%mod;
        //fm*=qpow(sigy,len,mod)%mod;
        n+=len;
    //    cout<<fz<<' '<<fm<<'\n';
    }
    ans=inverse(fm,mod)*fz%mod;
    cout<<ans<<'\n';
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