#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#else
#include <bits/stdc++.h>
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 1E7 + 10;

int ls[N], rs[N];
int stk[N];

void SINGLE_TEST() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int top = 1;
    stk[top] = 1;
    
    for (int i = 2; i <= n; i++) {
        while (a[stk[top]] > a[i] && top) top--;
        if (!top)
            ls[i] = stk[top + 1];
        else
            ls[i] = rs[stk[top]], rs[stk[top]] = i;
        stk[++top] = i;
    }
    for(int i=1;i<=n;i++){
        cout<<a[stk[i]]<<" ";
    }
    cout<<"\n";
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        cout << ls[i] << " " << rs[i] << "\n";
        ans1 ^= i * (ls[i] + 1);
        ans2 ^= i * (rs[i] + 1);
    }
    cout << ans1 << " " << ans2 << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
/*---------------------------------------------------------------------------------
struct CMP{bool operator()(const int & x, const int &y) const{ return x<y; }};

template <class T>
map<T, int> sortMap(const map<T, int> mp) {
    vector<pair<T, int>> v(mp.begin(), mp.end());
    sort(v.begin(), v.end(),
         [&](auto x, auto y) { return x.second < y.second; });
    map<T, int> ans;
    for (auto [lo, v] : v) {
        ans[lo] = v;
    }
    return ans;
}

std::mt19937_64 rng(
    std::chrono::steady_clock::now().time_since_epoch().count()
);

template <class T>
void shuffle(typename std::vector<T>::iterator first, typename
std::vector<T>::iterator last) { std::shuffle(first, last, rng);
}
---------------------------------------------------------------------------------*/
