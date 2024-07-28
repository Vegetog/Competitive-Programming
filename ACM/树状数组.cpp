#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using ll = long long;
#define INF 2000000000000000000
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define y1 Y1
#define y2 Y2
#define debug(a) cout<<#a<<"="<<a<<'\n';
#define PI acos(-1)/*3.141592653589*/
using namespace std;
/*----------------------------------------------*/
#define int long long
template<class T>
map<T,int> sortMap(const map<T,int> mp){vector<pair<T,int>> v(mp.begin(),mp.end());sort(v.begin(),v.end(),[&](auto x,auto y){
        return x.second<y.second;
});map<T,int> ans;for(auto [lo,v]:v){ans[lo]=v;}return ans;
}

const double eps = 1e-10;
typedef array<int,2> PII;
//const int mod=1e9;

const int N = 1e6 + 10;
/*----------------------------------------------*/
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};
void solve()
{
    int n;cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    auto b=a;
    sort(b.begin()+1,b.end());
    Fenwick<int> fc(n+1),fs(n+1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        int p=lower_bound(b.begin()+1,b.end(),a[i])-b.begin();
        ans+=fc.sum(p)*b[p]-fs.sum(p);
        fc.add(p,1);
        fs.add(p,a[i]);
    }
    cout<<ans;
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

	// cout<<fixed<<setprecision(10);
    int testcase=1;
	// cin>>testcase;
    while(testcase--){
    	solve();
	}
}