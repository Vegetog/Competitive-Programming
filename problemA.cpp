#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long;

int N;
string s;
int p[15];

ll cal(string &t) {
    reverse(t.begin(), t.end());
    ll res = 1;
    for (int l = 0; l < t.size(); l += 3) {
        int r = min((int)t.size() - 1, l + 2);
        int v = 0;
        for (int i = l; i <= r; i++) {
            v = v * 10 + t[i] - '0';
        }
        res *= v;
    }
    return res;
}

signed main() {
    cin >> s;
    N = s.size();
    ll ans = 0;
    for (int i = 0; i < N; i++) p[i] = i;
    do {
        string t;
        for (int i = 0; i < N; i++) {
            t += s[p[i]];
        }
        ans = max(ans, cal(t));
    } while (next_permutation(p, p + N));
    cout << ans << "\n";
}