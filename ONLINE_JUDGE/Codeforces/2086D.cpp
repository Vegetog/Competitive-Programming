#include "bits/stdc++.h"
using namespace std;
#define x1 X1
#define x2 X2
#define y1 Y1
#define y2 Y2
#define int long long
template <typename C>
inline int size(const C &x) {
    return static_cast<int>(x.size());
}

using i64 = long long;
using ll = long long;
using pii = pair<int, int>;

constexpr int B = 30, N = 2E6 + 10, mod = 998244353, inf32 = 1E9 + 10;
constexpr i64 inf = 2E18 + 10;

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
// int MInt<0>::Mod = 1E9+7;
int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

// constexpr int P = 1E9+7;
constexpr int P = 998244353;
using Z = MInt<P>;
//-------------------------------------//

Z fac[N], invfac[N];

void INIT() {
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i;
    invfac[N - 1] = fac[N - 1].inv();
    for (int i = N - 2; i; i--) invfac[i] = invfac[i + 1] * (i + 1);
}
inline Z A(int a, int b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return fac[a] * invfac[a - b];
}
inline Z C(int a, int b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return fac[a] * invfac[b] * invfac[a - b];
}

void Gura() {
    vector<int> cnt(26);
    int sum = 0;
    for (int i = 0; i < 26; i++) {
        cin >> cnt[i];
        sum += cnt[i];
    }

    int odd = (sum + 1) / 2;
    int even = sum / 2;

    vector<int> nz;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) nz.push_back(cnt[i]);
    }

    vector<Z> dp(odd + 1, 0);
    dp[0] = 1;
    for (int v : nz) {
        for (int j = odd; j >= v; j--) {
            dp[j] += dp[j - v];
        }
    }

    Z ans = dp[odd] * fac[odd] * fac[even];
    for (int i = 0; i < 26; i++) {
        ans *= invfac[cnt[i]];
    }

    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(15);
    INIT();
    int Gawr = 1;
    cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura();
    }

    return 0;
}
