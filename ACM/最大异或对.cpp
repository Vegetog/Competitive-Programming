#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;

int a[N];
int son[N*31][2];
int n,idx;

void insert(int x)
{
    int p=0;
    for(int i=31;i>=0;i--){
        int t=x>>i&1;
        if(!son[p][t]){
            son[p][t]=++idx;// 新节点编号为 idx + 1
        }
        p=son[p][t];
    }
}
int query(int x)
{
    int p=0;
    int ret=0;
    for(int i=31;i>=0;i--){
        int t=x>>i&1;
        if(son[p][!t]){
            p=son[p][!t];
            ret=ret*2+!t;
        }else{
            p=son[p][t];
            ret=ret*2+t;
        }
    }
    ret=ret^x;
    return ret;
}
void solve()
{
	int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        insert(a[i]);
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,query(a[i]));
    }
    cout<<ans<<'\n';
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--){
    	solve();
	}
}