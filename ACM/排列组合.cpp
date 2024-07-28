#include<bits/stdc++.h>
using ll = long long;
#define INF (long long)2e+18
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define y1 Y1
#define y2 Y2
#define debug(a) if(debugging) cout<<#a<<"="<<a<<'\n';
#define PI acos(-1)/*3.141592653589*/
using namespace std;
/*----------------------------------------------*/
#define int long long
const double eps = 1e-10;
typedef array<int,2> PII;
// const int mod=1e9;
const bool debugging = 1;

const int N = 2e6 + 10;
/*----------------------------------------------*/
ll jc[N],inf[N];
template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr ll mul(ll a, ll b, ll p=mod) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
ll qpow(ll a,ll b,ll m=mod) //快速幂求a^b%m; 
{
    if(m==0) return power(a,b);
	ll ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%m;
		b>>=1;
		a=a*a%m;
	}
	return ans%mod;
}
void PREPARE(){
    inf[0]=1;
    jc[0]=jc[1]=1;
    for(int i=1;i<=N;i++){
        (jc[i]=jc[i-1]%mod*i)%=mod;
        inf[i] = inf[i - 1] * qpow(i, mod - 2) % mod;
    }
}

ll inverse(ll a,ll mod=mod){
    return qpow(a,mod-2,mod)%mod;
}
ll exgcd(ll fm,ll fz,ll mod=mod){
    return inverse(fm,mod)*fz%mod;
}
ll C(int n, int m){
    return jc[n] * inf[m] % mod * inf[n - m] % mod;
}
ll A(int n,int m){
    return jc[n] * inf[m] % mod;
}

void solve()
{
	int n;cin>>n;
    ll ans=0;
    vector<int> num(5);
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        num[x]++;
    }
    int s1=0,s2=0,s3=0;
    for(int i=0;i<=num[2];i++){
        s2+=C(num[2],i)*(i+1);
        s2%=mod;
    }
    for(int i=0;i<=num[3];i++){
        s3+=C(num[3],i)*(i+1);
        s3%=mod;
    }
    cout<<qpow(2,num[1])*s2%mod*s3%mod-1<<"\n";
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    PREPARE();
	// cout<<fixed<<setprecision(10);
    int testcase=1;
	cin>>testcase;
    while(testcase--){
    	solve();
	}
}