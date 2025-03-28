#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;
/*
有向图对入度的要求是 0 
无向图对入度的要求是 1 
*/
int n,m;
int deg[N];
void solve()
{
	cin>>n>>m;
    vector<vector<int>> g(n+1);
    while(m--){
        int x,y;cin>>x>>y;
        g[x].push_back(y);
        deg[y]++;
    }
    auto topo=[&]()->void{
        queue<int> q;
        for(int i=1;i<=n;i++){
            if(deg[i]==0) q.push(i);
        }
        vector<int> ans;
        while(!q.empty()){
            int t=q.front();
            q.pop();
            ans.push_back(t);
            for(auto it : g[t]){
                deg[it]--;
                if(deg[it]==0) q.push(it);//有向图对入度的要求是 0 无向图对入度的要求是 1
            }
        }
        if(ans.size()==n){
            for(auto i : ans){
                cout<<i<<' ';
            }
        }else{
            cout<<-1;
        }
    };
    topo();
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
	//cin>>T;
    while(T--){
    	solve();
	}
}