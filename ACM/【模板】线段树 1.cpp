#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e5+10;
const int mod=1e9;
typedef pair<int,int> PII;

ll a[N];
ll tree[4*N];
ll tag[4*N];

ll ls(ll p){return p<<1;}
ll rs(ll p){return p<<1|1;}

void push_up(ll p){
    tree[p]=tree[ls(p)]+tree[rs(p)];//求区间和
    //tree[p]=min(tree[2*p],tree[2*p+1]);//求最小值
}
void build(ll p,ll pl,ll pr){
    tag[p]=0;
    if(pl==pr){tree[p]=a[pl];return ;}
    ll mid=(pl+pr)>>1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    push_up(p);
}
void addtag(ll p,ll pl,ll pr,ll d){
    tag[p]+=d;
    tree[p]+=d*(pr-pl+1);
}
void push_down(ll p,ll pl,ll pr){
    if(tag[p]){
        ll mid=(pl+pr)>>1;
        addtag(ls(p),pl,mid,tag[p]);
        addtag(rs(p),mid+1,pr,tag[p]);
        tag[p]=0;
    }
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
void update(ll L,ll R,ll p,ll pl,ll pr, ll d){
    if(L<=pl && pr<=R){
        addtag(p,pl,pr,d);
        return ;
    }
    push_down(p,pl,pr);
    ll mid=(pl+pr)>>1;
    if(L<=mid) update(L,R,ls(p),pl,mid,d);
    if(R>mid) update(L,R,rs(p),mid+1,pr,d);
    push_up(p);
}
ll query(ll L,ll R,ll p,ll pl,ll pr){
    if(L<=pl && pr<=R) return tree[p];
    push_down(p,pl,pr);
    ll res=0;
    ll mid=(pl+pr)>>1;
    if(L<=mid) res+=query(L,R,ls(p),pl,mid);
    if(R>mid) res+=query(L,R,rs(p),mid+1,pr);
    return res;
}
void solve()
{
	int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    while(m--){
        int op,x,y,k;
        cin>>op>>x>>y;
        if(op==1){
            cin>>k;
            update(x,y,1,1,n,k);
        }else{
            cout<<query(x,y,1,1,n)<<'\n';
        }

    }
}

signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int Geshin=1;
//	cin>>Geshin;
    while(Geshin--){
    	solve();
	}
}