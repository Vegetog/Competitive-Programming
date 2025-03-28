#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
#define dbINF 1.79769e+308
#define db double
#define debug(a) cout<<#a<<"="<<a<<'\n';
#define all(a) a.begin(),a.end()
#define pb push_back
const double eps=1e-10;
typedef array<int,2> PII;
//const int mod=1e9;
const int N=2e6+10;
int a[N],b[N];
bool cmp(PII x,PII y){
    return x[1]<y[1];
}
void solve()
{
	int n;cin>>n;
    int mx=0,mn=INF;
/////////////////////////////////////////////////    
    vector<PII> q;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        mx=max({mx,a[i],b[i]});
        if(a[i]>=b[i]){
            mn=min(mn,b[i]);
            q.pb({b[i],a[i]});
        }
    }
    sort(all(q));
    vector<PII> s;
    for(auto [l,r] : q){
        if(!s.empty()&&l<=s.back()[1]){
            s.back()[1]=max(s.back()[1],r);
        }else{

            s.push_back({l,r});
        }
    }
/////////////////////////////////////////////////
    sort(all(s),cmp);
    ll ans=0;
    int las=0;
    ll rr=0;
    int le=0;
    int ans1,ans2;
    for(int i=0;i<s.size();i++){
        int l=s[i][0],r=s[i][1];
        if(i==s.size()-1){
            ans1=ans2=ans;
            ans2+=mx-l;
            ans2+=mx-le;
        }
        
        ans+=r-las+r-l;
        las=l;
        rr=max(rr,r);
        le=l;
    }
    //debug(le);
    ans+=mx-le;
    if(mn==INF) mn=-INF;
    int ans3=mx+mx-mn;
    cout<<min({ans,ans2,ans3})<<'\n';
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