#pragma GCC optimize(3)
#include<bits/stdc++.h>
using ll = long long;
#define INF (long long)2e+18
#define dbINF DBL_MAX/*DBL_MAX,DBL_MIN,INT_MAX,INT_MIN*/
#define y1 Y1
#define y2 Y2
#define debug(a) if(debugging) cout<<#a<<"="<<a<<'\n';
#define PI acos(-1)/*3.141592653589*/
using namespace std;
/*----------------------------------------------*/
#define int long long
const double eps = 1e-10;
typedef array<int,2> PII;
//const int mod=1e9;
const bool debugging = 1;

const int N = 2e6 + 10;
/*----------------------------------------------*/
vector<int> border(const string& b) {
    int m = b.size();
    vector<int> pi(m);
    pi[0] = 0;
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && b[i] != b[j])
            j = pi[j - 1];
        if (b[i] == b[j])
            j++;
        pi[i] = j;
    }
    // for(auto x:pi) cout<<x<<" ";cout<<'\n';
    return pi;
}

vector<int> kmp(const string& a, const string& b) {//在a中找b
    int n = a.size(), m = b.size();
    vector<int> pi = border(b);
    vector<int> positions;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && a[i] != b[j])
            j = pi[j - 1];
        if (a[i] == b[j]) {
            if (j == m - 1) {
                positions.push_back(i - m + 1); // 存储子串开始的位置
                j = pi[j];
            } else {
                j++;
            }
        }
    }
    return positions;
}

void solve()
{
	int n, m;
    string a, b;
    cin >> n >> a;
    cin >> m >> b;
    vector<int> positions = kmp(b, a);
    for (int pos : positions)
        cout << pos << ' ';   
}

/*----------------------------------------------*/	
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

	// cout<<fixed<<setprecision(10);
    int testcase=1;
	// cin>>testcase;
    while(testcase--){
    	solve();
	}
}