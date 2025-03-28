// #pragma GCC optimize("O3")
#include<bits/stdc++.h>
using ll = long long;
#define INF (long long)2e+18
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define y1 Y1
#define y2 Y2
#define debug(a) cout<<#a<<"="<<a<<'\n';
#define PI acos(-1)/*3.141592653589*/
using namespace std;
/*----------------------------------------------*/
#define int long long
const double eps = 1e-10;
typedef array<int,2> PII;
//const int mod=1e9;

const int N = 2e6 + 10;
/*----------------------------------------------*/

void solve()
{
    int n;cin>>n;
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> c(n+1,0);
    for(int i=1;i<=n;i++) cin>>c[i];
    vector<int> sum(n+1,0);
    //计算子树和
    function<void(int,int)> dfs2=[&](int u,int f)->void{
        sum[u]=c[u];
        for(auto v : g[u]){
            if(v==f) continue;
            dfs2(v,u);
            sum[u]+=sum[v];
        }
    };
    dfs2(1,-1);
    //寻找树的重心
    function<int(int,int)> dfs1=[&](int u,int f)->int{
        for(auto v : g[u]){
            if(v==f || 2*sum[v]<=sum[1]) continue;
            return dfs1(v,u);
        }
        return u;
    };
    
    int cent=dfs1(1,-1);
    dfs2(cent,-1);
    
    ll ans = 0;
    for (int i=1;i<=n;i++) {
        if (i != cent) {
            ans += sum[i];
        }
    }
    cout << ans << "\n";
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

	// cout<<fixed<<setprecision(10);
    int testcase=1;
	// cin>>testcase;
    while(testcase--){
    	solve();
	}
}