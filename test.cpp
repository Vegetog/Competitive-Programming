#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
using PII = pair<int,int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;

vector<vector<ll>> g(10000);
map<pair<ll, ll>, ll> mp, mp1;
vector<ll> siz(10000);

void bfs(ll st) {
    vector<ll> vis(10000);
    queue<pair<ll, ll>> q; q.push({st, 0});
    while(!q.empty()) {
        ll res = q.front().first, cnt = q.front().second; q.pop();
        vis[res] = 1;
        if(mp1.count({st, res})) {
            mp[{st, res}] = cnt; siz[st] --; siz[res] -- ;
            if(siz[st] == 0) return ;   
        }
        string ss = to_string(res); 
        while(ss.size() < 4) ss = '0' + ss;
        for(ll i = 0; i < 4; i ++ ) {
            for(ll j = i; j < 4; j ++ ) {
                string ss1 = ss, ss2 = ss;
                for(ll k = i; k <= j; k ++ ) {
                    ss1[k] += 1;
                    if(ss1[k] > '9') ss1[k] = '0';
                    ll ress = 0;
                    for(ll kk = 0; kk < 4; kk ++ ) {
                        ress = ress * 10 + ss1[kk] - '0'; 
                    }
                    if(!vis[ress]) {
                        vis[ress] = 1;
                        q.push({ress, cnt + 1});
                        // cout << i << " " << j << " ";
                        // cout << ress << "\n";
                    }
                    ss2[k] -= 1;
                    if(ss2[k] < '0') ss2[k] = '9';
                    ress = 0;
                    for(ll kk = 0; kk < 4; kk ++ ) {
                        ress = ress * 10 + ss2[kk] - '0'; 
                    }
                    if(!vis[ress]) {
                        vis[ress] = 1;
                        q.push({ress, cnt + 1});
                        // cout << i << " " << j << " ";
                        // cout << ress << "\n";
                    }        
                }
            }
        }
    }
}

void solve() {
    ll t; cin >> t;
    vector<ll> a(t + 1), b(t + 1); 
    for(ll i = 1; i <= t; i ++ ) {
        cin >> a[i] >> b[i];
        string sa = to_string(a[i]), sb = to_string(b[i]);
        while(sa.size() < 4) sa = '0' + sa;
        while(sb.size() < 4) sb = '0' + sb;
        for(int i=0;i<4;i++){
            b[i]-=a[i];
            b[i]%=10;
        }
        int en=0;
        for(int i=0;i<4;i++){
            en*=10;
            en+=b[i];
        }
        g[a[i]].push_back(b[i]); g[b[i]].push_back(a[i]);
        mp1[{a[i], b[i]}] = 1; mp[{b[i], a[i]}] = 1;
    }
    vector<ll> p(10000);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](ll x, ll y){
        if(g[x].size() == g[y].size())
            return x < y;
        return g[x].size() > g[y].size();
    });
    for(ll i = 0; i <= 9999; i ++ ) {
        siz[i] = g[i].size();
    }
    // for(ll i = 0; i <= 9999; i ++ ) {
    //     if(siz[p[i]] > 0){
    //         bfs(p[i]);
    //     }  
    // }
    bfs(0);
    for(ll i = 1; i <= t; i ++ ) {
        cout << mp[{a[i], b[i]}] << "\n";
    } 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int T=1;
    // cin>>T;
    while(T--){
        solve();
    }
}