// https://github.com/Vegetog/Competitive-Programming/blob/main/_my_utils.h
#ifndef _MY_UTILS_H
#define _MY_UTILS_H

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
// #include <multiset>

#define EL std::cout << "\n";
#define SE std::cout << "--------------------------------\n";
#define COUT(ITEM) std::cout << #ITEM << "=" << ITEM << '\n';
#define CERR(ITEM) std::cerr << #ITEM << "=" << ITEM << '\n';

std::mt19937_64 rng(
    std::chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;

template <class T>
void debug(const std::vector<T>& v) {
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "\n";
}

template <>
void debug(const std::vector<std::array<ll, 2>>& v) {
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