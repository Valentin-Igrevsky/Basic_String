#pragma once

#include <iostream>

/// Пространство имен "bmstu"
namespace bmstu {
    template<class T>
    class basic_string;

    using string = bmstu::basic_string<char>;
    using wstring = bmstu::basic_string<wchar_t>;

    /// Создание класса "string"
    template<class T>
    class basic_string {
    public:
        /// Конструктор по умолчанию
        basic_string() {
            ptr_ = new T[1];
            *ptr_ = static_cast<T>('\0');
            size_ = 0;
        }

        basic_string(size_t num) {
            ptr_ = new T[num + 1];
            for (size_t i = 0; i < num; i++) {
                ptr_[i] = static_cast<T>(' ');
            }
            ptr_[num] = static_cast<T>('\0');
            size_ = num;
        }

        /// Конструктор с параметрами
        basic_string(const T *c_str) {
            size_ = strlen_(c_str);
            if (size_ == 0) {
                ptr_ = new T[1];
                *ptr_ = static_cast<T>('\0');
                size_ = 0;
            } else {
                ptr_ = new T[size_ + 1];
                ptr_[size_] = static_cast<T>('\0');

                for (size_t c = 0; c < size_; c++) {
                    ptr_[c] = c_str[c];
                }
            }
        }

        /// Оператор копирующего присваивания для строк класса bmstu::string с помощью скобок
        basic_string(const basic_string<T> &other) {
            if (this != &other) {
                clean_();
                size_ = other.size_;
                ptr_ = new T[size_ + 1];
                ptr_[size_] = 0;
                for (size_t i = 0; i < size_; i++) {
                    *(ptr_ + i) = other.c_str()[i];
                }
            }
        }

        /// Конструктор через массив char
        basic_string(std::initializer_list<T> il) : ptr_(new T[il.size() + 1]) {
            ptr_[il.size()] = 0;
            size_ = il.size();
            for (size_t i = 0; i < il.size(); i++) {
                ptr_[i] = *(il.begin() + i);
            }
        }

        /// Оператор копирующего присваивания (=) - Работает со строками класса bmstu::string
        basic_string &operator=(const basic_string<T> &other) {
            if (this != &other) {
                clean_();
                size_ = other.size_;
                ptr_ = new T[size_ + 1];
                ptr_[size_] = 0;
                for (size_t i = 0; i < size_; i++) {
                    *(ptr_ + i) = other.c_str()[i];
                }
            }
            return *this;
        }

        /// Оператор перемещающего присваивания
        basic_string &operator=(basic_string<T> &&other) {
            if (this != &other) {
                clean_();
                ptr_ = other.ptr_;
                size_ = other.size_;
                other.moved_();
            }
            return *this;
        }

        /// Оператор присваивания (=) - Работает со C-строками (char *str)
        basic_string &operator=(const T *c_str) {
            clean_();
            size_ = strlen_(c_str);
            ptr_ = new T[size_ + 1];
            ptr_[size_] = 0;
            for (size_t i = 0; i < size_; i++) {
                ptr_[i] = c_str[i];
            }
            return *this;
        }

        /// Перемещающий конструктор
        basic_string(basic_string<T> &&dying) {
            clean_();
            ptr_ = dying.ptr_;
            size_ = dying.size_;
            dying.moved_();
        }

        /// Деконструктор - медор, удаляющий элемент класса после завершения работы с ним
        ~basic_string() {
            delete[] ptr_;
        }

        /// Метод, возвращающий строку (Геттер на C-строку)
        const T *c_str() const {
            return static_cast<const T *>(ptr_);
        }

        /// Метод, возвращающий размер (Геттер на размер)
        size_t size() const {
            return size_;
        }

        /// Прибавление к строке класса bmstu::string другой строки этого же класса
        basic_string<T> &operator+=(const basic_string<T> &other) {
            size_t new_size = size_ + other.size_;
            auto new_ptr = new T[new_size + 1];
            for (size_t i = 0; i < size_; i++) {
                new_ptr[i] = ptr_[i];
            }

            for (size_t i = 0; i < other.size_; i++) {
                new_ptr[i + size_] = other.ptr_[i];
            }

            new_ptr[new_size] = 0;
            clean_();
            ptr_ = new_ptr;
            size_ = new_size;
            return *this;
        }

        /// Прибавление к строке класса bmstu::string другой C-строки
        basic_string<T> &operator+=(const T *str) {
            size_t strlen = strlen_(str);
            size_t new_size = size_ + strlen;
            auto new_ptr = new T[new_size + 1];
            for (size_t i = 0; i < size_; i++) {
                new_ptr[i] = ptr_[i];
            }

            for (size_t i = 0; i < strlen; i++) {
                new_ptr[i + size_] = str[i];
            }

            new_ptr[new_size] = 0;
            clean_();
            ptr_ = new_ptr;
            size_ = new_size;
            return *this;
        }

        /// Прибавление к строке класса bmstu::string символа char
        basic_string<T> &operator+=(const T symbol) {
            size_t new_size = size_ + 1;
            auto new_ptr = new T[new_size + 1];
            for (size_t i = 0; i < size_; i++) {
                new_ptr[i] = ptr_[i];
            }

            new_ptr[new_size - 1] = symbol;
            new_ptr[new_size] = 0;
            clean_();
            ptr_ = new_ptr;
            size_ = new_size;
            return *this;
        }

        /// Метод получения символа строки по его индексу
        T &operator[](size_t index) {
            if (index < size_) {
                return *(ptr_ + index);
            }
            throw std::runtime_error("Wrong index " + std::to_string(index));
        }

        /// Опетатор конкатенации (сложения) двух строк
        friend bmstu::basic_string<T> operator+(const basic_string<T> &left, const basic_string<T> &right) {
            bmstu::basic_string<T> result(left);
            result += right;
            return result;
        }

        /// Оператор передачи строки в топок
        template <class S>
        friend S &operator<<(S &os, const basic_string<T> &obj) {
            os << obj.c_str();
            return os;
        }

        /// Оператор получения строки из потока
        template <class S>
        friend S &operator>>(S &is, basic_string<T> &obj) {
            bmstu::basic_string<T> result;
            T buf = ' ';
            while (is.good()) {
                buf = is.get();
                if (buf == -1) {
                    break;
                }
                result += buf;
            }
            obj = std::move(result);
            return is;
        }

    private:

        /// Метод вычисления длины C-строки
        static size_t strlen_(const T *str) {
            size_t result = 0;
            while (*str) {
                result++;
                ++str;
            }
            return result;
        }

        /// Метод очистки строки
        void clean_() {
            if (ptr_ != nullptr) {
                delete[] ptr_;
                ptr_ = nullptr;
            }
            size_ = 0;
        }

        T *ptr_ = nullptr;
        size_t size_;

        void moved_() {
            ptr_ = new T[1];
            *ptr_ = static_cast<T>('\0');
            size_ = 0;
        }
    };

}