#pragma once

#include <iostream>
#include "array_bundle.h"

namespace bmstu {
    template<typename Type>
    class dummy_vector {
    public:
        struct iterator {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Type;
            using pointer = Type *;
            using reference = Type &;

            iterator(pointer ptr) : m_ptr(ptr) {

            }

            reference operator*() const {
                return *m_ptr;
            }

            pointer operator->() {
                return m_ptr;
            }

            iterator &operator++() {
                ++m_ptr;
                return *this;
            }

            iterator &operator--() {
                --m_ptr;
                return *this;
            }

            iterator &operator=(const iterator &other) {
                this->m_ptr = other.m_ptr;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator operator--(int) {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const iterator &a, const iterator &b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const iterator &a, const iterator &b) {
                return !(a == b);
            }

            friend difference_type operator-(const iterator &a, const iterator &b) {
                return a.m_ptr - b.m_ptr;
            }

            iterator &operator+(size_t n) noexcept {
                m_ptr = m_ptr + n;
                return *this;
            }

            iterator &operator-(size_t n) noexcept {
                m_ptr = m_ptr - n;
                return *this;
            }

        private:
            pointer m_ptr;
        };

        using const_iterator = const iterator;

        /// Конструктор по умолчанию
        dummy_vector() noexcept = default;

        /// Конструктор с параметром
        dummy_vector(size_t size, const Type &value = Type{}) :
                size_(size), capacity_(size), data_(size) {
            auto first = begin();
            auto last = end();
            for (; first != last; ++first) {
                *first = value;
            }
        }

        /// Конструктор копироания
        dummy_vector(const dummy_vector<Type> &other) : size_(other.size()), capacity_(other.capacity()), data_(size_){
            std::copy(other.begin(), other.end(), begin());
        }

        /// Конструктор перемещения
        dummy_vector(dummy_vector<Type> &&other) {
            this->swap(other);
        }
        /// Конструктор через инициалайзер лист
        dummy_vector(std::initializer_list<Type> ilist) : size_(ilist.size()), capacity_(ilist.size()), data_(ilist.size()) {
            std::copy(ilist.begin(), ilist.end(), begin());
        }

        /// "Очистка" вектора от элементов
        void clear() noexcept {
            size_ = 0;
        }

        /// Оперотор копирующего присваивания
        dummy_vector &operator=(const dummy_vector<Type> &other) {
            if (this != &other) {
                if (other.empty()) {
                    clear();
                } else {
                    bmstu::dummy_vector<Type> copy(other);
                    this->swap(copy);
                }
            }
            return *this;
        }

        /// Оперотор перемещающего присваивания
        dummy_vector &operator=(const dummy_vector<Type> &&other) {
            if (this != &other) {
                if (other.empty()) {
                    clear();
                } else {
                    bmstu::dummy_vector<Type> copy(std::move(other));
                    this->swap(copy);
                }
            }
            return *this;
        }

        /// Итераторы
        iterator begin() noexcept {
            return data_.Get();
        }

        iterator end() noexcept {
            return data_.Get() + size_;
        }

        const_iterator begin() const noexcept {
            return data_.Get();
        }

        const_iterator end() const noexcept {
            return data_.Get() + size_;
        }

        const_iterator cbegin() const noexcept {
            return data_.Get();
        }

        const_iterator cend() const noexcept {
            return data_.Get() + size_;
        }

        typename iterator::reference operator[](size_t index) noexcept {
            return data_[index];
        }

        typename const_iterator::reference operator[](size_t index) const noexcept {
            return const_cast <typename const_iterator::reference>(data_[index]);
        }

        typename iterator::reference at(size_t index) {
            if (index > size_) {
                throw std::out_of_range("Invalid index");
            } else {
                return data_[index];
            }
        }

        typename const_iterator::reference at(size_t index) const {
            if (index > size_) {
                throw std::out_of_range("Invalid index");
            } else {
                return const_cast <typename const_iterator::reference>(data_[index]);
            }
        }

        size_t size() const noexcept {
            return size_;
        }

        size_t capacity() const noexcept {
            return capacity_;
        }

        bool empty() const noexcept {
            return (size_ == 0);
        }

        void swap(dummy_vector &other) noexcept {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            data_.swap(other.data_);
        }

        friend void swap(dummy_vector<Type> &left, dummy_vector<Type> &right) {
            left.swap(right);
        }

        void resize(size_t new_size) {
            if (new_size > capacity_) {
                size_t new_capacity = std::max(new_size, capacity_ * 2);
                reserve(new_capacity);
            } else {
                std::fill(begin()+new_size, begin()+capacity_, Type{});
            }
            size_ = new_size;
        }

        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                array_bundle<Type> tmp(new_capacity);
                auto first = begin();
                auto last = end();
                auto tmp_ptr = tmp.Get();
                for (; first != last; ++first, ++tmp_ptr) {
                    *tmp_ptr = std::move(*first);
                }
                capacity_ = new_capacity;
                data_.swap(tmp);
            }
        }

        iterator insert(const_iterator pos, Type &&value) {
            size_t n = pos - begin();
            if (capacity_ == 0) {
                reserve(1);
            }
            if (size_ == capacity_) {
                capacity_ *= 2;
            }
            array_bundle<Type> tmp(capacity_);
            Type *tmp_ptr = tmp.Get();
            for (auto first = begin(); first != begin() + n; ++first, ++tmp_ptr) {
                *tmp_ptr = std::move(*first);
            }

            tmp.Get()[n] = std::move(value);
            tmp_ptr = tmp.Get() + n + 1;
            for (auto first = begin() + n; first != end(); ++first, ++tmp_ptr) {
                *tmp_ptr = std::move(*first);
            }
            data_.swap(tmp);
            size_++;
            return begin() + n;
        }

        iterator insert(const_iterator pos, const Type &value) {
            Type copy = value;
            return insert(pos, std::move(copy));
        }

        iterator erase(const_iterator pos) {
            size_t n = pos - begin();
            array_bundle<Type> tmp(capacity_);
            Type *tmp_ptr = tmp.Get();
            auto first = begin();
            while(first != end()) {
                if (first!=pos) {
                    *tmp_ptr = std::move(*first);
                    ++tmp_ptr;
                }
                ++first;
            }
            data_.swap(tmp);
            --size_;
            return begin() + n;

        }

        void push_back(const Type &value) {
            Type tmp = value;
            push_back(std::move(tmp));
        }

        void push_back(Type &&value) {
            insert(end(), std::move(value));
        }

        void pop_back() noexcept {
            if (!empty()) {
                --size_;
            }
        }

        friend bool operator==(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            if (left.size_ == right.size_) {
                for (auto fl = left.begin(), fr = right.begin(); fl != left.end(); ++fl, ++fr) {
                    if (*fl != *fr) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        friend bool operator!=(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            return !(left == right);
        }

        friend bool operator<(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            return lexicographical_compare_(left, right);
        }

        friend bool operator>(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            return (right < left);
        }

        friend bool operator<=(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            return !(right < left);
        }

        friend bool operator>=(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            return !(left < right);
        }

        friend std::ostream &operator<<(std::ostream &os, const dummy_vector<Type> &other) {
            os << "[";
            if (other.size_) {
                for (int i = 0; i < other.size_ - 1; ++i) {
                    os << other[i] << ", ";
                }
                os << other[other.size_ - 1];
            }
            os << "]";
            return os;
        }

    private:
        static bool lexicographical_compare_(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
            auto fl = left.begin(), fr = right.begin();
            for (; (fl != left.end()) && (fr != right.end()); ++fl, ++fr) {
                if (*fl < *fr) {
                    return true;
                }
                if (*fr < *fl) {
                    return false;
                }
            }
            return ((fr != right.end()) && (fl == left.end()));
        }

        size_t size_ = 0;
        size_t capacity_ = 0;
        array_bundle<Type> data_;
    };
}