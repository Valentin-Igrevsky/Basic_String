#include <iostream>

template<class Type>
std::string bit_repr(Type && value) {
    constexpr size_t size = sizeof(Type) * 8;
    auto tmp = reinterpret_cast<uintptr_t *>(&value);

    std::string result;
    result.resize(size);

    for (int i = size - 1; i >= 0; --i) {
        result[i] = (*tmp & 1) == 1 ? '1' : '0';
        *tmp >>= 1;
    }
    return result;
}

template<typename Type>
std::string bit_repr(std::initializer_list<Type> &&ilst) {
    constexpr size_t size = sizeof(ilst) * 8;
    uintptr_t  tmp(std::forward<Type>(reinterpret_cast<Type &>(ilst)));

    std::string result;
    result.resize(size);

    for (int i = size - 1; i >= 0; --i) {
        result[i] = (tmp & 1) == 1 ? '1' : '0';
        tmp >>= 1;
    }
    return result;
}