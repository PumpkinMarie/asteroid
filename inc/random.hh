#ifndef RANDOM_H
#define RANDOM_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>

static std::mt19937 rng(
    std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T getRandom(T min = 0, T max = std::numeric_limits<T>::max()) {
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> distrib(min, max);
        return distrib(rng);
    } else if (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> distrib(min, max);
        return distrib(rng);
    }
    return std::numeric_limits<T>::min();
}

#endif