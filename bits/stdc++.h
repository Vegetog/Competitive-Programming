#ifndef STDCXX_H
#define STDCXX_H

//------------------header files------------------//
// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
/* https://stackoverflow.com/a/25892335/15125422 */
#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#include <cstdalign>
#include <cuchar>
#endif
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <any>
#include <charconv>
// #include <execution>
#include <filesystem>
#include <memory_resource>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if __cplusplus > 201703L
#include <bit>
#include <compare>
#include <concepts>
#include <numbers>
#include <ranges>
#include <span>
#include <stop_token>
// #include <syncstream>
#include <version>
#endif

//------------------debugging simplified------------------//
using ll = long long;

#define SP std::cout << " ";
#define EL std::cout << "\n";
#define SE std::cout << "--------------------------------\n";
#define COUT(ITEM) std::cout << #ITEM << "=" << ITEM << '\n';
#define COUTS(ITEM) std::cout << #ITEM << "=" << ITEM << ' ';
#define COUTE(ITEM) std::cout << #ITEM << "=" << ITEM << '\n';
#define CERR(ITEM) std::cerr << #ITEM << "=" << ITEM << '\n';
#define CERRS(ITEM) std::cerr << #ITEM << "=" << ITEM << ' ';
#define CERRE(ITEM) std::cerr << #ITEM << "=" << ITEM << '\n';

//------------------fake g++ for clang------------------//
#ifdef __clang__
template <typename T>
inline int my_lg(T n) {assert(n > 0); return (ll)log2(n);}
#define __lg my_lg
#define __gcd std::gcd
#endif  

//------------------integer simplification------------------//
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

// std::ostream& operator<<(std::ostream& os, const i128& value) { 
//     if (value == 0) return os << '0';
//     i128 temp = value;
//     if (temp < 0) {
//         os << '-';
//         temp = -temp;
//     }
//     char buffer[40];
//     int pos = 0;
//     while (temp > 0) {
//         buffer[pos++] = '0' + (temp % 10);
//         temp /= 10;
//     }
//     for (int i = pos - 1; i >= 0; --i) {
//         os << buffer[i];
//     }
//     return os;
// }

// std::istream& operator>>(std::istream& is, i128& value) {
//     std::string str;
//     is >> str;
//     value = 0;
//     bool negative = false;
//     size_t start = 0;
//     if (str[0] == '-') {
//         negative = true;
//         start = 1;
//     }
//     for (size_t i = start; i < str.size(); ++i) {
//         value = value * 10 + (str[i] - '0');
//     }
//     if (negative) {
//         value = -value;
//     }
//     return is;
// }

//------------------random------------------//
// std::mt19937_64 rng(
//     std::chrono::steady_clock::now().time_since_epoch().count()
// );

// template <class T>
// void shuffle(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
//     std::shuffle(first, last, rng);
// }

//------------------debug for STL------------------//
template <class K, class V>
void debug(const std::pair<K, V>& p) {
    std::cout << p.first << " " << p.second << "\n";
}

template <class T>
void debug(const std::vector<T>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <class T>
void debug(const std::vector<std::array<T, 2>>& v) {
    for (const auto& [x1, x2] : v) std::cout << x1 << " " << x2 << "\n";
}

template <class T>
void debug(const std::vector<std::array<T, 3>>& v) {
    for (const auto& [x1, x2] : v) std::cout << x1 << " " << x2 << "\n";
}

template <class T>
void debug(const std::vector<std::array<T, 4>>& v) {
    for (const auto& [x1, x2] : v) std::cout << x1 << " " << x2 << "\n";
}

template <class T>
void debug(const std::vector<std::array<T, 5>>& v) {
    for (const auto& [x1, x2] : v) std::cout << x1 << " " << x2 << "\n";
}

template <class K, class V>
void debug(const std::vector<std::pair<K, V>>& v) {
    for (const auto& [x1, x2] : v) std::cout << x1 << " " << x2 << "\n";
}

template <class T>
void debug(const std::vector<std::vector<T>>& v) {
    for (const auto& x : v) debug(x);
}

template <class K, class V>
void debug(const std::map<K, V>& m) {
    for (const auto& [x1, x2] : m) std::cout << x1 << " " << x2 << "\n";
}

template <class K, class V>
void debug(const std::unordered_map<K, V>& m) {
    for (const auto& [x1, x2] : m) std::cout << x1 << " " << x2 << "\n";
}

template <class T>
void debug(const std::set<T>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <class T>
void debug(const std::set<T, std::greater<T>>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <class T>
void debug(const std::set<T, std::greater<>>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <class T>
void debug(const std::multiset<T>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <class T>
void debug(const std::multiset<T, std::greater<T>>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <class T>
void debug(const std::multiset<T, std::greater<>>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

#endif  // STDCXX_H