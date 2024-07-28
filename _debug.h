// debug.h
#ifndef DEBUG_H
#define DEBUG_H

#include <array>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
// #include <multiset>

#define EL std::cout << "\n";
#define COUT(ITEM) std::cout << #ITEM << "=" << ITEM << '\n';
#define CERR(ITEM) std::cerr << #ITEM << "=" << ITEM << '\n';

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
#endif  // DEBUG_H