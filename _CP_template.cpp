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
constexpr int N = 2E6 + 10;

void SINGLE_TEST() 
{
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
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
void shuffle(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
    std::shuffle(first, last, rng);
}
---------------------------------------------------------------------------------*/
