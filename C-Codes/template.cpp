#include <iostream>
template<typename T>
T max(T a, T b) {
    static_assert(std::is_arithmetic_v<T>, "T must be numeric!");
    return (a > b) ? a : b;
}
