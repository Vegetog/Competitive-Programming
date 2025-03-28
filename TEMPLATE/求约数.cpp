#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF (long long)2e+18
const int N=2e6+10;
const int mod=1e9;
typedef pair<int,int> PII;

vector<int> get_divisors(int n){
    vector<int> res;//存约数
    for(int i=1;i<=n/i;i++){
        if(n%i==0){
            res.push_back(i);
            if(i!=n/i) res.push_back(n/i);
        }
    }
    sort(res.begin(),res.end());
    return res;
}
void solve()
{
	int n;cin>>n;
    auto x=get_divisors(n);
    for(auto i: x){
        cout<<i<<' ';
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