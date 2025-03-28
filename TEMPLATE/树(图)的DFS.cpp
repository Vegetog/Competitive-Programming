/*
tips:利用邻接链表存树(图)
题目链接：https://codeforces.com/contest/1843/problem/D
(本题主要用于：求每个子树的叶子结点个数)
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF (long long)2e+18
#define int long long
const int N=2e5+10;
const int mod=1e9;
typedef pair<int,int> PII;

int n;
int h[N],e[2*N],ne[2*N],idx;
bool vis[N];

int ans[N];

void add(int a,int b){
	e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
int dfs(int x)
{
    
    vis[x]=1;
    for(int i=h[x];i!=-1;i=ne[i]){
        int j=e[i];
        if(j!=x&&vis[j]==0){
            ans[x]+=dfs(j);
        }
    }
    if(ans[x]==0) ans[x]=1;
    return ans[x];
}
void solve()
{
    memset(h,-1,sizeof h);
    memset(vis,0,sizeof vis);
    memset(ans,0,sizeof ans);
	int n;cin>>n;
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);add(v,u);
    }
    dfs(1);
    int q;cin>>q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        cout<<ans[x]*ans[y]<<'\n';
    }

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