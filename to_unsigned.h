#ifndef TO_UNSIGNED_H
#define TO_UNSIGNED_H

/* Header file containing the function toUZ which converts signed integral types to std::size_t */

#include <type_traits>      // for std::is_integral and std::is_enum

// Helper function to convert 'value' into an object of type std::size_t
// UZ is the suffix for literals of type std::size_t
template <typename T>
constexpr std::size_t toUZ(T value)
{
    // Make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());

    return static_cast<std::size_t>(value);
}

#endif