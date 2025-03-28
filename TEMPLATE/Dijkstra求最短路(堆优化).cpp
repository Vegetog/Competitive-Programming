#pragma GCC optimize(3)
#include<bits/stdc++.h>
using ll = long long;
#define INF (long long)2e+18
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define y1 Y1
#define y2 Y2
#define debug(a) cout<<#a<<"="<<a<<'\n';
#define all(a) a.begin(),a.end()
#define PI acos(-1)/*3.141592653589*/
using namespace std;
/*----------------------------------------------*/
#define int long long
const double eps=1e-10;
typedef array<int,2> PII;
//const int mod=1e9;
bool multi_test=0;
const int N=2e6+10;
/*----------------------------------------------*/

int dijkstra_heap(int n,int sta,vector<vector<PII>> &g)//O((n+m) log n),适用稀疏图
{
    vector<ll> dis(n+1,INF);
    vector<bool> vis(n+1,0);
    dis[1]=0;
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.push({0,1});
    while(!q.empty()){
        auto [d,u]=q.top();
        q.pop();
        // if(vis[u]) continue;
        // vis[u]=1;
        if(d!=dis[u]) continue;
        for(auto [v,w]:g[u]){
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push({dis[v],v});
            }
        }
    }
    if(dis[n]==INF){
        return -1;
    } 
    else{
        return dis[n];
    } 
}

void solve()
{
	int n,m;
    cin>>n>>m;
    vector<vector<PII>> g(n+1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }
    cout<<dijkstra_heap(n,1,g)<<'\n';
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);


	// cout<<fixed<<setprecision(10);
    int Testcase=1;
	if(multi_test) cin>>Testcase;
    while(Testcase--){
    	solve();
	}
}