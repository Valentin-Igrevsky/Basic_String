#pragma once

#include <cstdlib>

template<typename T>
class array_bundle {
public:
    array_bundle() = default;

    explicit array_bundle(size_t size) {
        if (size == 0) {
            raw_ptr_ = nullptr;
        } else {
            raw_ptr_ = new T[size]{};
        }
    }

    explicit array_bundle(T *ptr) {
        raw_ptr_ = ptr;
    }

    array_bundle(const array_bundle &other_bundle) = delete;

    array_bundle &operator=(const array_bundle &other_bundle) = delete;

    T &operator[](size_t index) noexcept {
        return *(raw_ptr_ + index);
    }

    const T &operator[](size_t index) const noexcept {
        return const_cast<const T &>(*(raw_ptr_ + index));
    }

    explicit operator bool() const {
        return (raw_ptr_ != nullptr);
    }

    T *Get() const noexcept {
        return raw_ptr_;
    }

    T *Release() noexcept {
        T *ptr = raw_ptr_;
        raw_ptr_ = nullptr;
        return ptr;
    }

    ~array_bundle() {
        delete[]raw_ptr_;
    }

    void swap(array_bundle &other) noexcept {
        std::swap(raw_ptr_, other.raw_ptr_);
    }

private:
    T *raw_ptr_ = nullptr;
};
