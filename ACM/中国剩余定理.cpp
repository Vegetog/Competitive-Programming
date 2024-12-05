#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "_my_utils.h"
#endif
#define int long long

using namespace std;
using ll = long long;
using PII = std::pair<int, int>;

constexpr ll INF = 2E18 + 10;
constexpr int N = 2E6 + 10;
// struct CMP{bool operator()(const int & x, const int &y) const{ return x<y; }};

template <typename T = long long>
bool extgcd(T a, T b, T &x, T &y, T d) {  // ax+by=d
    if (!b && d % a) return false;
    if (!b) {
        x = d / a, y = 0;
        return true;
    }
    if (extgcd(b, a % b, y, x, d)) {
        y -= a / b * x;
        return true;
    }
    return false;
}
template <typename T = long long>
T exgcd(T a, T b, T &x, T &y) {  // ax+by=gcd(a,b)
    T d = a;
    if (!b)
        x = 1, y = 0;
    else {
        d = exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
    return d;
}
// x=a[i]%r[i]
// x=a[j]%r[j]
// r[i]、r[j]两两互质
ll CRT(int n,vector<ll> &a,vector<ll> &r){
    __int128_t ms = 1, ans = 0;
    for (int i = 1; i <= n; i++) ms = ms * r[i];
    for (int i = 1; i <= n; i++) {
        __int128_t m = ms / r[i], b, y;
        exgcd(m, (__int128_t)r[i], b, y);  // b * m mod r[i] = 1
        ans = (ans + a[i] * m * b % ms) % ms;
    }
    return (ans % ms + ms) % ms;
}

void SINGLE_TEST() 
{
    int n;
    cin>>n;
    vector<ll> a(n+1),b(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    cout<<CRT(n,b,a)<<"\n";
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
