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
//-------------------------------------//
template <>
int MInt<0>::Mod = 1E9+7;
// int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1E9+7;
// constexpr int P = 998244353;
using Z = MInt<P>;
//-------------------------------------//
std::string& operator--(std::string& num) {
    int n = num.size();
    for (int i = n - 1; i >= 0; --i) {
        if (num[i] > '0') {
            num[i]--;
            break;
        } else {
            num[i] = '9';
        }
    }
    if (num[0] == '0' && num.size() > 1) {
        num.erase(num.begin());
    }    
    return num;
}

void SINGLE_TEST() 
{
    string L,R;
    cin>>L>>R;
    --L;

    string s=R;
    //212 11
    vector<vector<vector<vector<Z>>>> f(s.size(),vector<vector<vector<Z>>>(10,vector<vector<Z>>(10,vector<Z>(2,-1))));
    bool isL=0;
    function<Z(int,bool,int,PII,bool)> dfs=[&](int u,bool high,int lead,PII las,bool ok)->Z{
        if(u==s.size()) return (!lead && ok) ? 1 : 0;
        if(!high&&!lead&& las.first>=0&&las.second>=0&&f[u][las.first][las.second][ok]!=-1) 
            return f[u][las.first][las.second][ok];
        Z res=0;
        if(lead) res=dfs(u+1,0,1,{-1,-1},ok);
        int l=0,r=high ? s[u]-'0' : 9;
        for(int i=max(l,lead);i<=r;i++){
            res+=dfs(u+1,high&&i==r,0,{las.second,i},ok||(i==las.second)||(i==las.first));
        }
        if(!high&&!lead && las.first>=0&&las.second>=0) f[u][las.first][las.second][ok]=res;
        return res;
    };

    Z ansr=dfs(0,1,1,{-1,-1},0);
    s=L;
    isL=1;
    f.assign(s.size(), vector<vector<vector<Z>>>(10, vector<vector<Z>>(10, vector<Z>(2, -1))));
    Z ansl=dfs(0,1,1,{-1,-1},0);
    cout<<ansr-ansl<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int SAMPLES = 1;
    // cin >> SAMPLES;
    for (int CUR = 1; CUR <= SAMPLES; CUR++) {
        SINGLE_TEST();
    }

    return 0;
}