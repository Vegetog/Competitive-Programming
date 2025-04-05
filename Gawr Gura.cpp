#include "bits/stdc++.h"
#define x1 _x1
#define x2 _x2
#define y1 _y1
#define y2 _y2
#define int long long

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
using pii = std::pair<int, int>;

// 基本输入输出
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ios;
using std::setprecision;
using std::fixed;
using std::scientific;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::flush;
using std::ws;
using std::getline;

// 容器
using std::vector;
using std::deque;
using std::list;
using std::set;
using std::map;
using std::multiset;
using std::multimap;
using std::unordered_set;
using std::unordered_map;
using std::unordered_multiset;
using std::unordered_multimap;
using std::array;
using std::bitset;
using std::stack;
using std::queue;
using std::priority_queue;
using std::forward_list;

// 字符串
using std::string;
using std::string_view;
using std::to_string;
using std::stoi;
using std::stol;
using std::stoll;
using std::stof;
using std::stod;
using std::stold;

// 算法
// using std::min;
// using std::max;
using std::sort;
using std::stable_sort;
using std::binary_search;
using std::find;
using std::count;
using std::lower_bound;
using std::upper_bound;
using std::reverse;
using std::rotate;
using std::unique;
using std::next_permutation;
using std::prev_permutation;
using std::shuffle;
using std::accumulate;
using std::transform;

// 实用工具
using std::pair;
using std::tuple;
using std::make_pair;
using std::make_tuple;
using std::tie;
using std::get;
using std::swap;
using std::move;
using std::forward;
using std::ref;
using std::cref;

// 数值计算
using std::complex;
using std::abs;
using std::gcd;
using std::lcm;

// 函数对象
using std::function;
using std::hash;
using std::less;
using std::greater;
using std::equal_to;

// 异常和断言
using std::exception;
using std::runtime_error;

// 文件IO
using std::ifstream;
using std::ofstream;
using std::fstream;

// C++17以上的特性
using std::optional;
using std::variant;
using std::any;
using std::filesystem::path;

template <typename C>
inline int size(const C &x) {
    return static_cast<int>(x.size());
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

constexpr int B = 30, N = 1E6 + 10, mod = 998244353, inf32 = 1E9 + 10;
constexpr i64 inf = 1E12 + 10, inf64 = 2E18 + 10;


void Gura() 
{
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(10);

    int Gawr = 1;
    cin >> Gawr;
    for (int _i = 1; _i <= Gawr; _i++) {
        Gura();
    }

    return 0;
}
