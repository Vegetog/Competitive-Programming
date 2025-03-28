#include<bits/stdc++.h>
using namespace std;
#define ll long long
//#define int long long
#define INF (long long)2e+18
const int N=5e5+10;
const int mod=1e9;
typedef pair<int,int> PII;

int a[N];
int tree[4*N];

void push_up(int p){
    tree[p]=tree[2*p]+tree[2*p+1];//区间和
    //tree[p]=min(tree[2*p],tree[2*p+1]);//求最小值
}
void build(int p,int pl,int pr){
    if(pl==pr){tree[p]=a[pl];return ;}
    int mid=(pl+pr)>>1;
    build(2*p,pl,mid);
    build(2*p+1,mid+1,pr);
    push_up(p);
}
void add(int p,int l,int r,int po,int k){//单点修改
    if(l==r){
        tree[p]+=k;
        return ;
    }
    int mid=(l+r)>>1;
    if(po<=mid){
        add(2*p,l,mid,po,k);
    }else{
        add(2*p+1,mid+1,r,po,k);
    }
    push_up(p);
}
int search(int p,int l,int r,int x,int y){
    if(l>=x&&y>=r){
        return tree[p];
    }
    int mid=(l+r)>>1;
    if(y<=mid) return search(2*p,l,mid,x,y);
    if(mid+1<=x) return search(2*p+1,mid+1,r,x,y);
    return search(2*p,l,mid,x,mid)+search(2*p+1,mid+1,r,mid+1,y);
}
void solve()
{
	int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            add(1,1,n,x,y);
        }else{
            cout<<search(1,1,n,x,y)<<'\n';
        }
    }
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