/*
tips：朴素版本，适合稠密图，边权不能为负
题目链接：https://www.acwing.com/problem/content/851/
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF (long long)2e+18
const int N=5e2+10;
const int mod=1e9;

int n,m;
int g[N][N];
int dist[N];
bool vis[N];

int dijkstra()
{
	memset(dist,0X3f,sizeof dist);
	dist[1]=0;
	for(int i=0;i<=n-1;i++){
		int t=-1;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&(t==-1||dist[t]>dist[j])){
				t=j;
			}
		}
		for(int j=1;j<=n;j++){
			dist[j] = min(dist[j], dist[t] + g[t][j]);
		}
		vis[t]=1;
	}
	if(dist[n]==0X3f3f3f3f) return -1;
	return dist[n];
}
void solve()
{
	cin>>n>>m;
	memset(g,0X3f,sizeof g);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		g[a][b]=min(g[a][b],c);
	}
	cout<<dijkstra()<<'\n';
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--){
    	solve();
	}
}