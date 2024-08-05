#include <bits/stdc++.h>
#define int long long
using ll = long long;
using PII = std::array<int, 2>;
using namespace std;
const ll INF = 2E18 + 10;
#ifdef __clang__
    template <typename T>
    inline int my_lg(T n) {return (n > 0) ? static_cast<int>(log2(n)) : -1;}
    #define __lg my_lg
    #define __gcd gcd
#endif
#ifndef ONLINE_JUDGE
    #include "_debug.h"
#endif
// struct cmp{bool operator()(const int & x, const int &y) const{ return x<y;}};
const int N = 2E6 + 10;
template <class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) { Mod = Mod_; }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & { return *this *= rhs.inv(); }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template <>
int MInt<0>::Mod = 1e9+7;
// int MInt<0>::Mod = 998244353;

// template <int V, int P>
// constexpr MInt<P> CInv = MInt<P>(V).inv();

// constexpr int P = 1e9+7;
constexpr int P = 0;
using Z = MInt<P>;
/*
1: red->green->yellow->red
2->0->1->2
2: green->red->yellow->green
0->2->1->0
-------------------------------
green:0,yellow:1,red:2
*/
int ch1[]={1,2,0};
int ch2[]={2,0,1};
// x三进制的第i位
int bt(int x,int i){
    return x/power(3LL,i)%3;
}
void SINGLE_TEST() 
{
    int n,k,M;
    cin>>n>>k>>M;
    Z::setMod(M);
    vector<string> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int MAX=power(3,k);
    vector<Z> dp(MAX);
    vector<bool> vis(MAX);
    dp[0] = 1;
    vis[0]=true;
    for(auto s : a){
        auto dpp=dp;
        auto viss=vis;
        for(int i=0;i<MAX;i++){
            int ch=0;
            for(int j=k-1;j>=0;j--){   
                int t=bt(i,j);
                if(s[k-j-1]=='+'){
                    ch=ch*3+ch1[t];
                }else if(s[k-j-1]=='-'){
                    ch=ch*3+ch2[t];
                }else{
                    ch=ch*3+t;
                }
            }
            // cerr<<i<<" "<<ch<<" "<<dpp[i]<<"\n";
            if(viss[i]){
                vis[ch]=true;
            }
            dp[ch]+=dpp[i];
        }
    }
    for(int i=0;i<MAX;i++){
        if(!vis[i]){
            continue;
        }
        string s;
        int val=i;
        for(int j=0;j<k;j++){
            s=char('A'+val%3)+s;
            val/=3;
        }
        cout<<s<<" "<<dp[i]<<"\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);

    int SAMPLES = 1;
    cin >> SAMPLES;
    for(int CUR=1;CUR<=SAMPLES;CUR++){
        SINGLE_TEST();
    }
}
