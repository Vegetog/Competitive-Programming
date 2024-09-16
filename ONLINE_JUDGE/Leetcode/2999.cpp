#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    ll numberOfPowerfulInt(ll start, ll finish, int limit, string s) {
        string s1 = to_string(start), s2 = to_string(finish);
        s1 = string(s2.size() - s1.size(), '0') + s1;
        vector<ll> f(s1.size(), -1);
        function<ll(int, int, int)> dfs = [&](int u, bool low, bool high) {
            if (u == s1.size()) return 1LL;
            if (!low && !high && f[u] != -1) return f[u];
            int l = low ? s1[u] - '0' : 0, r = high ? s2[u] - '0' : 9;
            ll ret = 0;
            if (s1.size() - u <= s.size()) {
                int t = s[s.size() - (s1.size() - u)] - '0';
                if (t >= l && t <= r) ret = dfs(u + 1, low && t == l, high && t == r);
            }
            else {
                for (int i = l; i <= r && i <= limit; i++) {
                    ret += dfs(u + 1, low && i == l, high && i == r);
                }
            }
            if (!low && !high) f[u] = ret;
            return ret;
        };
        return dfs(0, 1, 1);
    }
};