#include <iostream>

template<size_t n>
struct Factorial {
    static const size_t result = n * Factorial<n - 1>::result;
};

template<>
struct Factorial<0> {
    static const size_t result = 1;
};

template<>
struct Factorial<1> {
    static const size_t result = 1;
};

template<size_t T>
struct _factorial_is_;

int mainFunc5() {
    _factorial_is_<Factorial<10>::result>__;
    return 0;
}