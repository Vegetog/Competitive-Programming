#pragma once

#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace debug {

#ifndef ONLINE_JUDGE
namespace detail {

template <class T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

template <class T>
concept Iterable = requires(const T &value) {
    std::begin(value);
    std::end(value);
} && !StringLike<T>;

template <class T>
void print(const T &value);

template <class T>
void print(const T &value) {
    if constexpr (StringLike<T>) {
        std::cerr << value;
    } else if constexpr (requires { value.first; value.second; }) {
        std::cerr << '(';
        print(value.first);
        std::cerr << ", ";
        print(value.second);
        std::cerr << ')';
    } else if constexpr (Iterable<T>) {
        std::cerr << '[';
        bool first = true;
        for (const auto &item : value) {
            if (!first) {
                std::cerr << ", ";
            }
            first = false;
            print(item);
        }
        std::cerr << ']';
    } else {
        std::cerr << value;
    }
}

inline void log_names(std::string_view names) {
    std::cerr << names << " = ";
}

template <class T, class... Rest>
void log_values(const T &value, const Rest &...rest) {
    print(value);
    if constexpr (sizeof...(rest) > 0) {
        std::cerr << ", ";
        log_values(rest...);
    } else {
        std::cerr << '\n';
    }
}

}

template <class... Args>
void log(std::string_view names, const Args &...args) {
    detail::log_names(names);
    detail::log_values(args...);
}
#endif

}

#ifndef ONLINE_JUDGE
#define dbg(...) ::debug::log(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) do { } while (false)
#endif