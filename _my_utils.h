// https://github.com/Vegetog/Competitive-Programming/blob/main/_my_utils.h
#ifndef _MY_UTILS_H
#define _MY_UTILS_H

// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

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


#ifdef __clang__
#include <cmath>
#include <numeric>  // For std::gcd

template <typename T>
inline int my_lg(T n) {
    return (n > 0) ? static_cast<int>(std::log2(n)) : -1;
}

#define __lg my_lg
#define __gcd std::gcd

#endif  // __clang__

#include <array>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <random>
// #include <multiset>

#define SP std::cout << " ";
#define EL std::cout << "\n";
#define SE std::cout << "--------------------------------\n";
#define COUT(ITEM) std::cout << #ITEM << "=" << ITEM << '\n';
#define COUTS(ITEM) std::cout << #ITEM << "=" << ITEM << ' ';
#define COUTE(ITEM) std::cout << #ITEM << "=" << ITEM << '\n';
#define CERR(ITEM) std::cerr << #ITEM << "=" << ITEM << '\n';
#define CERRS(ITEM) std::cerr << #ITEM << "=" << ITEM << ' ';
#define CERRE(ITEM) std::cerr << #ITEM << "=" << ITEM << '\n';

std::mt19937_64 rng(
    std::chrono::steady_clock::now().time_since_epoch().count()
);

template <class T>
void shuffle(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
    std::shuffle(first, last, rng);
}

using ll = long long;

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

#endif  // _MY_UTILS_H