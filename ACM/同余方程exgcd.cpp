#include<bits/stdc++.h>
using ll = long long;
#define INF (long long)2e+18
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define y1 Y1
#define y2 Y2
#define debug(a) if(debugging) cout<<#a<<"="<<a<<'\n';
#define PI acos(-1)/*3.141592653589*/
#define sort(abort) sort(abort.begin(),abort.end())
using namespace std;
/*----------------------------------------------*/
#define int long long
const double eps = 1e-10;
typedef array<int,2> PII;
//const int mod=1e9;
const bool debugging = 1;

const int N = 2e6 + 10;
/*----------------------------------------------*/
template <typename T=long long> 
bool extgcd(T a, T b, T &x, T &y, T d) {//ax+by=d
    if(!b and d % a) return false;
    if(!b) {
        x = d / a, y = 0;
        return true;
    }
    if(extgcd(b, a % b, y, x, d)) {
        y -= a / b * x;
        return true;
    }
    return false;
}
int exgcd(int a,int b,int&x,int&y){//ax+by=gcd(a,b)
	int d=a;
	if(!b)x=1,y=0;
	else{
		d=exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	return d;
}
void solve()
{
    ll a,b;
    cin>>a>>b;
    ll x,y;
    // ll d=exgcd(a,b,x,y);
    // cout<<(x%b+b)%b<<"\n";
    extgcd(a,-b,x,y,1LL);
    cout<<(x%b+b)%b<<"\n";
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

	// cout<<fixed<<setprecision(10);
    int testcase=1;
	// cin>>testcase;
    while(testcase--){
    	solve();
	}
}