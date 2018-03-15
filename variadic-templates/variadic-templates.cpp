#include <iostream>
#include <string>

template<typename T>
T adder(T v) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return first + adder(args...);
}

template<typename T>
bool pair_comparer(T a) {
    return false;
}

template<typename T>
bool pair_comparer(T a, T b) {
    // In real-world code, we wouldn't compare floating point values like
    // this. It would make sense to specialize this function for floating
    // point types to use approximate comparison.
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return a == b && pair_comparer(args...);
}

int main() {
    long sum = adder(1, 2, 3, 8, 7);

    std::string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy";
    std::string ssum = adder(s1, s2, s3, s4);

    pair_comparer(1.5, 1.5, 2, 2, 6, 6, 7);
}
