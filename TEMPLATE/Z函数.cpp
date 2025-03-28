// #pragma GCC optimize("O3")
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
/*----------------------------------------------*/
template<class T>
map<T,int> sortMap(const map<T,int> mp); 

template<class T>
void debug_vector(const vector<T>& v); 

template<>
void debug_vector(const vector<array<int,2>>& v); 

struct cmp{
	bool operator()(const int & x, const int &y) const{
		return x<y;
	}
};

/*----------------------------------------------*/
const double eps = 1e-10;
typedef array<int,2> PII;

const int N = 2e6 + 10;
/*----------------------------------------------*/
vector<int> Z(string s) {
    int n = s.size();
    vector<int> z(n + 1);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = max(0LL, min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}
void solve()
{
	int n,k;
    cin>>n>>k>>k;
    string s;cin>>s;
    auto z=Z(s);
    // debug_vector(z);
    auto check=[&](int x)->bool{
        int p=0;
        int cnt=0;
        while(p<n){
            if(z[p]>=x){
                cnt++;
                p+=x;
            }else{
                p++;
            }
        }
        return cnt>=k;     
    };
    int l=0,r=n;
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    cout<<l<<'\n';
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

	// cout<<fixed<<setprecision(10);
    int testcase=1;
	cin>>testcase;
    while(testcase--){
    	solve();
	}
}

/*----------------------------------------------*/	

template<class T>
map<T,int> sortMap(const map<T,int> mp){
	vector<pair<T,int>> v(mp.begin(),mp.end());
	sort(v.begin(),v.end(),[&](auto x,auto y){
        return x.second<y.second;
	});
	map<T,int> ans;
	for(auto [lo,v]:v) ans[lo]=v;
	return ans;
}
template<class T>
void debug_vector(const vector<T>& v) {
    for (const auto& x : v) cout << x << " ";
    cout << "\n";
}
template<>
void debug_vector(const vector<array<int,2>>& v) {
    for (const auto& [x1, x2] : v) cout << x1 << " " << x2 << "\n";
}