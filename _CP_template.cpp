#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#else
#include <bits/stdc++.h>
#endif
#define int long long
// struct CMP {bool operator()(const auto & x, const auto &y) const{ return x<y; }};
constexpr int N = (int)2E6 + 10, INF = (int)2E18 + 10;using namespace std;using ll = long long;using ull = unsigned long long; using i128 = __int128_t; using u128 = __uint128_t; using P2 = pair<int, int>; struct P3 {int first, second, third; auto operator<=>(const P3&) const = default;}; // C++20

void SINGLE_TEST() 
{
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    // INIT();
    int SAMPLES = 1;
    cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }
}
