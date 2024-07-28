#pragma GCC optimize(3)  //O2优化开启
#include<bits/stdc++.h>
#define ll long long
#define INF (long long)2e+18
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define db double
#define debug(a) cout<<#a<<"="<<a<<'\n';
#define all(a) a.begin(),a.end()
#define pb push_back
#define PI acos(-1)/*3.141592653589*/
using namespace std;
/*----------------------------------------------*/
#define int long long
const double eps=1e-10;
typedef array<int,2> PII;
//const int mod=1e9;
const int N=2e6+10;

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

void solve()
{
	int n,q;
    cin>>n>>q;
    DSU dsu(n);
    while(q--){
        int op,x,y;
        cin>>op>>x>>y;
        x--;y--;
        if(op==1){
            dsu.merge(x,y);
        }
        else{
            if(dsu.same(x,y)) cout<<"Y"<<"\n";
            else cout<<"N"<<"\n";
        }
    }
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	// init();
	// cout<<fixed<<setprecision(10);
    int T=1;
	// cin>>T;
    while(T--){
    	solve();
	}
}