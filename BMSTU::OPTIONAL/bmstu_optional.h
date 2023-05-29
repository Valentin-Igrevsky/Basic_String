#pragma once

#include <cstdint>
#include <exception>

namespace bmstu {
    class bad_optional_access : public std::exception {
    public:
        virtual const char *what() const noexcept override {
            return "Bad optional access";
        }
    };

    template<typename T>
    class optional {
    public:
        optional() = default;

        optional(const T &value) {
            is_initialized = true;
            T *val = new(&data_[0]) T{value};
            (void) (&val);
        }

        optional(T &&value) {
            is_initialized = true;
            T *val = new(&data_[0]) T(std::move(value));
            (void) (&val);
        }

        optional(const optional &other) {
            if (other.is_initialized) {
                is_initialized = true;
                T *val = new(&data_[0]) T(other.value());
                (void) (&val);
            } else {
                (void) (&data_[0]);
            }
        }

        optional(optional &&other) {
            if (other.is_initialized) {
                is_initialized = true;
                T *val = new(&data_[0]) T(std::move(other.value()));
                (void) (&val);
            } else {
                (void) (&data_[0]);
            }
        }

        ~optional() {
            if (is_initialized) {
                T *ptr = static_cast<T *> ((void *) &data_[0]);
                ptr->~T();
            }
        }

        optional &operator=(const T &value) {
            if (is_initialized) {
                this->value() = value;
            } else {
                is_initialized = true;
                T *val = new(&data_[0])T(value);
                (void) (&val);
            }
            return *this;
        }

        optional &operator=(T &&value) {
            if (is_initialized) {
                this->value() = std::move(value);
            } else {
                is_initialized = true;
                T *val = new(&data_[0])T(std::move(value));
                (void) (&val);
            }
            return *this;
        }

        optional &operator=(const optional &other) {
            if (this != &other) {
                if (is_initialized && other.is_initialized) {
                    this->value() = other.value();
                } else if (!is_initialized && other.is_initialized) {
                    is_initialized = true;
                    T *val = new(&data_[0]) T(other.value());
                    (void) (&val);
                } else if (is_initialized && !other.is_initialized) {
                    this->reset();
                }
            }

            return *this;
        }

        optional &operator=(optional &&other) {
            if (this != &other) {
                if (is_initialized && other.is_initialized) {
                    this->value() = std::move(other.value());
                } else if (!is_initialized && other.is_initialized) {
                    is_initialized = true;
                    T *val = new(&data_[0]) T(std::move(other.value()));
                    (void) (&val);
                } else if (is_initialized && !other.is_initialized) {
                    this->reset();
                }
            }

            return *this;
        }

        template<typename ...Args>
        void emplace(Args &&... args) {
            if (is_initialized) reset();
            is_initialized = true;
            T *val = new(&data_[0])T(std::forward<Args>(args)...);
            (void) (&val);
        }

        bool has_value() const {
            return is_initialized;
        }

        T &operator*() &{
            return *(static_cast<T *>((void *) &data_[0]));
        }

        const T &operator*() const &{
            return *(static_cast<const T *>((void *) &data_[0]));
        }

        T *operator->() {
            return static_cast<T *>((void *) &data_[0]);
        }

        const T *operator->() const {
            return static_cast<const T *>((void *) &data_[0]);
        }

        T &&operator*() &&{
            return std::move(reinterpret_cast<T &>(*(T *) &data_[0]));
        }

        T &value() &{
            if (!is_initialized) throw bad_optional_access();
            return reinterpret_cast<T &>(*(T *) &data_[0]);
        }

        const T &value() const &{
            if (!is_initialized) throw bad_optional_access();
            return reinterpret_cast<const T &>(*(T *) &data_[0]);
        }

        T &&value() &&{
            if (!is_initialized) throw bad_optional_access();
            return reinterpret_cast<T &&>(*(T *) &data_[0]);
        }

        void reset() {
            if (is_initialized) {
                static_cast<T *>((void *) &data_[0])->~T();
                is_initialized = false;
            }
        }

    private:
        alignas(T) uint8_t data_[sizeof(T)];
        bool is_initialized = false;
    };
}