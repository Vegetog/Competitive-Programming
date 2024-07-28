#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
#ifdef __clang__
    template <typename T>
    inline int my_lg(T n) {
        return (n > 0) ? static_cast<int>(log2(n)) : -1;
    }
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E6 + 10;

void SINGLE_TEST() 
{
    
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int SAMPLES = 1;
    cin >> SAMPLES;
    while (SAMPLES--) SINGLE_TEST();
}
