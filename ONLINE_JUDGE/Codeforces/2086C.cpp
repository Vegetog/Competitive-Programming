#include "bits/stdc++.h"
using namespace std;
#define x1 X1
#define x2 X2
#define y1 Y1
#define y2 Y2
#define int long long
template <typename C> inline int size(const C& x) {return static_cast<int>(x.size());}

using i64 = long long;
using pii = pair<int, int>;

constexpr int B = 30, N = 2E6 + 10, mod = 998244353, inf32 = 1E9 + 10;
constexpr i64 inf = 2E18 + 10;

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

void Gura() 
{
    int n;
    cin>>n;
    vector<int> p(n+1),d(n+1);
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        cin>>d[i];
    }

    DSU dsu(n+1);
    vector<bool> vis(n+1);
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int x=i;
            while(!vis[x]){
                vis[x]=true;
                dsu.merge(x,p[x]);
                x=p[x];
            }
        }
    }
    vector<int> ans(n+1);
    vector<int> vis1(n+1);
    int sum=0;
    // for(int i=1;i<=n;i++){
    //     cout<<dsu.find(i)<<" ";
    // }
    // cout<<"\n";
    for(int i=1;i<=n;i++){
        if(!vis1[dsu.find(d[i])]){
            vis1[dsu.find(d[i])]=true;
            sum+=dsu.size(d[i]);
        }
        cout<<sum<<" \n"[i==n];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(15);

    int Gawr = 1;
    cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura();
    }

    return 0;
}
