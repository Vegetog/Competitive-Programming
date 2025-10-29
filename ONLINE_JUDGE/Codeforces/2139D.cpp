#include "bits/stdc++.h"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::getline;
using std::ios;

using std::array;
using std::bitset;
using std::deque;
using std::forward_list;
using std::list;
using std::map;
using std::multimap;
using std::multiset;
using std::pair;
using std::priority_queue;
using std::queue;
using std::set;
using std::stack;
using std::tuple;
using std::unordered_map;
using std::unordered_multimap;
using std::unordered_multiset;
using std::unordered_set;
using std::vector;

using std::string;
using std::string_view;
using std::to_string;

using std::accumulate;
using std::binary_search;
using std::count;
using std::find;
using std::lower_bound;
using std::next_permutation;
using std::prev_permutation;
using std::reverse;
using std::rotate;
using std::shuffle;
using std::sort;
using std::stable_sort;
using std::transform;
using std::unique;
using std::upper_bound;

using std::forward;
using std::get;
using std::make_pair;
using std::move;
using std::pair;
using std::swap;

using std::abs;
using std::complex;
using std::cos;
using std::exp;
using std::gcd;
using std::lcm;
using std::log;
using std::log10;
using std::log2;
using std::pow;
using std::sin;
using std::sqrt;
using std::tan;

using std::equal_to;
using std::function;
using std::greater;
using std::hash;
using std::less;

// using std::min;
// using std::max;

template <typename C>
inline int size(const C &x) {
    return static_cast<int>(std::size(x));
}
template <typename T, typename U>
inline auto max(const T &a, const U &b) -> decltype(a > b ? a : b) {
    return a > b ? a : b;
}
template <typename T, typename U>
inline auto min(const T &a, const U &b) -> decltype(a < b ? a : b) {
    return a < b ? a : b;
}
template <typename T, typename U, typename V>
inline auto max(const T &a, const U &b, const V &c) {
    return max(max(a, b), c);
}
template <typename T, typename U, typename V>
inline auto min(const T &a, const U &b, const V &c) {
    return min(min(a, b), c);
}
template <typename T, typename U, typename V, typename W>
inline auto max(const T &a, const U &b, const V &c, const W &d) {
    return max(max(a, b), max(c, d));
}
template <typename T, typename U, typename V, typename W>
inline auto min(const T &a, const U &b, const V &c, const W &d) {
    return min(min(a, b), min(c, d));
}

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

std::ostream &operator<<(std::ostream &os, const i128 &value) {
    if (value == 0) return os << '0';
    i128 temp = value;
    if (temp < 0) {
        os << '-';
        temp = -temp;
    }
    char buffer[40];
    int pos = 0;
    while (temp > 0) {
        buffer[pos++] = '0' + (temp % 10);
        temp /= 10;
    }
    for (int i = pos - 1; i >= 0; --i) {
        os << buffer[i];
    }
    return os;
}

std::istream &operator>>(std::istream &is, i128 &value) {
    std::string str;
    is >> str;
    value = 0;
    bool negative = false;
    size_t start = 0;
    if (str[0] == '-') {
        negative = true;
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) {
        value = value * 10 + (str[i] - '0');
    }
    if (negative) {
        value = -value;
    }
    return is;
}

#undef int
template <class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return u64(a) * b % P;
}

template <u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

constexpr i64 safeMod(i64 x, i64 m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr std::pair<i64, i64> invGcd(i64 a, i64 b) {
    a = safeMod(a, b);
    if (a == 0) {
        return {b, 0};
    }

    i64 s = b, t = a;
    i64 m0 = 0, m1 = 1;

    while (t) {
        i64 u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        std::swap(s, t);
        std::swap(m0, m1);
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return {s, m0};
}

template <std::unsigned_integral U, U P>
struct ModIntBase {
   public:
    constexpr ModIntBase() : x(0) {}
    template <std::unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_ % mod()) {}
    template <std::signed_integral T>
    constexpr ModIntBase(T x_) {
        using S = std::make_signed_t<U>;
        S v = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static U mod() { return P; }

    constexpr U val() const { return x; }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const { return power(*this, mod() - 2); }

    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs,
                                          const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator+(ModIntBase lhs,
                                          const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator-(ModIntBase lhs,
                                          const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator/(ModIntBase lhs,
                                          const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream &operator>>(std::istream &is, ModIntBase &a) {
        i64 i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os,
                                              const ModIntBase &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(const ModIntBase &lhs,
                                     const ModIntBase &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr std::strong_ordering operator<=>(const ModIntBase &lhs,
                                                      const ModIntBase &rhs) {
        return lhs.val() <=> rhs.val();
    }

   private:
    U x;
};

template <u32 P>
using ModInt = ModIntBase<u32, P>;
template <u64 P>
using ModInt64 = ModIntBase<u64, P>;

struct Barrett {
   public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    constexpr u32 mod() const { return m; }

    constexpr u32 mul(u32 a, u32 b) const {
        u64 z = a;
        z *= b;

        u64 x = u64((u128(z) * im) >> 64);

        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

   private:
    u32 m;
    u64 im;
};

template <u32 Id>
struct DynModInt {
   public:
    constexpr DynModInt() : x(0) {}
    template <std::unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_ % mod()) {}
    template <std::signed_integral T>
    constexpr DynModInt(T x_) {
        auto v = x_ % static_cast<decltype(x_)>(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(u32 m) { bt = m; }

    static u32 mod() { return bt.mod(); }

    constexpr u32 val() const { return x; }

    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr DynModInt inv() const {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt &operator*=(const DynModInt &rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    constexpr DynModInt &operator+=(const DynModInt &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr DynModInt &operator-=(const DynModInt &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr DynModInt &operator/=(const DynModInt &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream &operator>>(std::istream &is, DynModInt &a) {
        i64 i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os,
                                              const DynModInt &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(const DynModInt &lhs,
                                     const DynModInt &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr std::strong_ordering operator<=>(const DynModInt &lhs,
                                                      const DynModInt &rhs) {
        return lhs.val() <=> rhs.val();
    }

   private:
    u32 x;
    static Barrett bt;
};

template <u32 Id>
Barrett DynModInt<Id>::bt = 998244353;

template <typename T>
struct Comb {
    std::vector<T> fac, invfac;

    Comb() {}
    Comb(int n) { init(n); }

    void init(int n) {
        fac.assign(n + 1, 0);
        invfac.assign(n + 1, 0);
        fac[0] = invfac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
        invfac[n] = fac[n].inv();
        for (int i = n - 1; i; i--) invfac[i] = invfac[i + 1] * (i + 1);
    }

    // 排列数：A(n,k) = n!/(n-k)!
    inline T A(int a, int b) const {
        if (a < 0 || b < 0 || a < b) return 0;
        return fac[a] * invfac[a - b];
    }

    // 组合数：C(n,k) = n!/[k!(n-k)!]
    inline T C(int a, int b) const {
        if (a < 0 || b < 0 || a < b) return 0;
        return fac[a] * invfac[b] * invfac[a - b];
    }
};

using DM = DynModInt<0>;
using Z9 = ModInt<998244353>;
using Z1 = ModInt<1000000007>;

#define int long long

using pii = std::pair<int, int>;

std::mt19937_64 rng(
    std::chrono::steady_clock::now().time_since_epoch().count());

#define print(x) cout << #x << " = " << (x) << "\n"

constexpr int B32 = 30, B64 = 63, inf32 = 1E9 + 10;
constexpr i64 inf = 1E12 + 10, inf64 = 2E18 + 10;
constexpr int N = 2E6 + 10, M = 5E6 + 10, mod = 998244353;

void Gura(int &_turn) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> L(n + 1, 0);
    stack<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) {
            st.pop();
        }
        if (!st.empty()) {
            L[i] = st.top();
        } else {
            L[i] = 0;
        }
        st.push(i);
    }

    while (!st.empty()) st.pop();

    vector<int> R(n + 1, n + 1);
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && a[st.top()] >= a[i]) {
            st.pop();
        }
        if (!st.empty()) {
            R[i] = st.top();
        } else {
            R[i] = n + 1;
        }
        st.push(i);
    }
    while (!st.empty()) st.pop();

    vector<int> M(n + 1, 0);
    for (int j = 1; j <= n; j++) {
        if (L[j] > 0 && R[j] <= n) {
            if (L[j] > M[R[j]]) {
                M[R[j]] = L[j];
            }
        }
    }

    vector<int> best(n + 1, 0);
    for (int r = 1; r <= n; r++) {
        best[r] = max(best[r - 1], M[r]);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (best[r] >= l) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << std::fixed << std::setprecision(10);

    int Gawr = 1;
    cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura(_i);
    }

    return 0;
}
