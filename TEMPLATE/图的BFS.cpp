#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N = 2e5 + 10;
const int mod = 1e9;

int n, m;
ll ans;
vector<vector<int>> a(N + 1);
int d[N];


void bfs(int x)
{
    for(int i=0;i<=n+5;i++){
        d[i]=-1;
    }
    queue<int> q;
    q.push(x);
    d[x]=0;
    while(!q.empty()){
        int t=q.front();
        q.pop();
        for(auto it : a[t]){
            if(d[it]==-1){
                d[it]=d[t]+1;
                ans=max(ans,d[it]);
                q.push(it);
            }
        }
    }
    cout<<ans-1<<'\n';
}

void solve()
{
    ans=0;
    cin >> n;
    m = n - 1;
    for(int i=0;i<=n+5;i++){
        a[i].clear();
    }
   // a.clear();
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    bfs(1);
   // cout<<ans<<'\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    	cin>>T;
    while (T--)
    {
        solve();
    }
    
}
