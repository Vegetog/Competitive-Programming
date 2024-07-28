#include<bits/stdc++.h>
using namespace std;
#define ll long long
//#define int long long
#define i128 __int128
#define INF (long long)2e+18
const int N=2e6+10;
//const int mod=1e9;
typedef pair<int,int> PII;
ll sqrtt(ll X){
    ll ret=sqrt(X);
    while((ret+1)*(ret+1)<=X) ret++;
    while(ret*ret>X) ret--;
    return ret;
}
inline __int128 read(){
    __int128 x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void print(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
void solve()
{
	
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