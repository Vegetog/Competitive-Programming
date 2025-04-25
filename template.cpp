#include "bits/stdc++.h"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::flush;
using std::getline;
using std::ios;
using std::left;
using std::right;
using std::scientific;
using std::setfill;
using std::setprecision;
using std::setw;
using std::ws;

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

using std::stod;
using std::stof;
using std::stoi;
using std::stol;
using std::stold;
using std::stoll;
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
using std::fill;

using std::cref;
using std::forward;
using std::get;
using std::make_pair;
using std::make_tuple;
using std::move;
using std::pair;
using std::ref;
using std::swap;
using std::tie;
using std::tuple;

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

using std::exception;
using std::runtime_error;

using std::fstream;
using std::ifstream;
using std::ofstream;

#if __cplusplus >= 201703L  // C++17
using std::any;
using std::byte;
using std::optional;
using std::string_view;
using std::variant;
namespace fs = std::filesystem;
using fs::path;
using std::apply;
using std::clamp;
using std::exclusive_scan;
using std::inclusive_scan;
using std::invoke;
using std::reduce;
using std::scoped_lock;
#endif

template <typename C>
inline int size(const C &x) {return static_cast<int>(std::size(x));}
template <typename T, typename U>
inline auto max(const T &a, const U &b) -> decltype(a > b ? a : b) {return a > b ? a : b;}
template <typename T, typename U>
inline auto min(const T &a, const U &b) -> decltype(a < b ? a : b) {return a < b ? a : b;}
template <typename T, typename U, typename V>
inline auto max(const T &a, const U &b, const V &c) {return max(max(a, b), c);}
template <typename T, typename U, typename V>
inline auto min(const T &a, const U &b, const V &c) {return min(min(a, b), c);}
template <typename T, typename U, typename V, typename W>
inline auto max(const T &a, const U &b, const V &c, const W &d) {return max(max(a, b), max(c, d));}
template <typename T, typename U, typename V, typename W>
inline auto min(const T &a, const U &b, const V &c, const W &d) {return min(min(a, b), min(c, d));}
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

#define print(x) cout << #x << " = " << (x) << "\n"
#define printv(x) cout << #x << " = "; for (auto &i : x) cout << i << " "; cout << "\n"

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

#define int long long
using pii = std::pair<int, int>;

constexpr int N = 1E6 + 10, M = 5E6 + 10;
constexpr i64 inf = 2E18 + 10;

void Gura(int &_turn) 
{
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(10);

    int Gawr = 1;
    cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura(_i);
    }

    return 0;
}
