#pragma once

#include <iostream>
#include <sstream>
#include <vector>

namespace bmstu {
    template<typename T>
    class matrix {
    public:
        matrix() : data_(1), rows_(1), columns_(1) {
            representation_ = {{&data_[0]}};
        }

        matrix(size_t rows, size_t columns) : data_(rows * columns), rows_(rows), columns_(columns) {
            for (size_t i = 0; i < rows_; ++i) {
                std::vector<T *> current_row(columns_);
                for (size_t j = 0; j < columns_; ++j) {
                    current_row[j] = &(data_[i * columns_ + j]);
                }
                representation_.push_back(std::move(current_row));
            }
        }

        matrix(std::initializer_list<T> i_list, size_t rows, size_t columns) : rows_(rows), columns_(columns) {
            if (i_list.size() == rows_ * columns_) {
                data_.resize(rows_ * columns_);
                std::move(i_list.begin(), i_list.end(), data_.data());
                for (size_t i = 0; i < rows_; ++i) {
                    std::vector<T *> current_row(columns_);
                    for (size_t j = 0; j < columns_; ++j) {
                        current_row[j] = &(data_[i * columns_ + j]);
                    }
                    representation_.push_back(std::move(current_row));
                }
            } else {
                throw std::out_of_range(
                        "Current matrix pos wrong (" + std::to_string(rows) + ", " + std::to_string(columns) +
                        ") != " + std::to_string(i_list.size()));
            }
        }

        T &operator()(size_t rows, size_t columns) {
            return *representation_[rows][columns];
        }

        T operator()(size_t rows, size_t columns) const {
            T copy = *representation_[rows][columns];
            return copy;
        }

//        matrix &operator=(const matrix<T> &other) {
//            if (this != &other) {
//                rows_ = other.rows_;
//                columns_ = other.columns_;
//                clear_();
//                data_ = other.data_;
//
//                for (size_t i = 0; i < rows_; ++i) {
//                    std::vector<T *> current_row(columns_);
//                    for (size_t j = 0; j < columns_; ++j) {
//                        current_row[j] = &(data_[i * columns_ + j]);
//                    }
//                    representation_.push_back(std::move(current_row));
//                }
//            }
//            return *this;
//        }

        template<class S>
        friend S &operator<<(S &ovs, const bmstu::matrix<T> &obj) {
            for (size_t i = 0; i < obj.rows_; ++i) {
                for (size_t j = 0; j < obj.columns_; ++j) {
                    ovs << obj(i, j) << " ";
                }
                ovs << "\r\n";
            }
            return ovs;
        }

        std::vector<T *> operator[](size_t i) {
            return representation_[i];
        }

        std::vector<T> operator[](size_t i) const {
            std::vector<T> result;
            result.resize(columns_);
            for (size_t j = 0; j < columns_; ++j) {
                result[j] = *representation_[i][j];
            }
            return result;
        }

        T det() {
            if (columns_ != rows_) {
                throw std::logic_error("Matrix have determinant if (rows == colimns)!");
            } else {
                T result = T();
                std::vector<size_t> indexes(columns_);
                int sign = 1;
                for (size_t i = 0; i < columns_; ++i) {
                    indexes[i] = i;
                }
                permute(indexes, indexes.size(), result, sign);
                return result;
            }
        }

        friend matrix<T> operator*(const matrix<T> &l, const matrix<T> &r) {
            if (l.columns_ != r.rows_) {
                throw std::logic_error("The left matrix must have as many columns at the right one has rows!");
            } else {
                matrix<T> result(l.rows_, r.columns_);
                for (size_t i = 0; i < result.rows_; ++i) {
                    for (size_t j = 0; j < result.columns_; ++j) {
                        T new_num = 0;
                        for (size_t count = 0; count < l.columns_; ++count) {
                            new_num += (l(i, count) * r(count, j));
                        }
                        result(i, j) = new_num;
                    }
                }
                return result;
            }
        }

        friend matrix<T> operator+(const matrix<T> &l, const matrix<T> &r) {
            if (l.rows_ != r.rows_ || l.columns_ != r.columns_) {
                throw std::logic_error("Matries must have the same dimension!");
            } else {
                matrix<T> result(l.rows_, l.columns_);
                for (size_t i = 0; i < result.rows_; ++i) {
                    for (size_t j = 0; j < result.columns_; ++j) {
                        result(i, j) = l(i, j) + r(i, j);
                    }
                }
                return result;
            }
        }

        friend matrix<T> operator-(const matrix<T> &l, const matrix<T> &r) {
            return l + r * (-1);
        }

        friend matrix<T> operator*(const matrix<T> &l, const T value) {
            matrix<T> result(l.rows_, l.columns_);
            for (size_t i = 0; i < result.rows_; ++i) {
                for (size_t j = 0; j < result.columns_; ++j) {
                    result(i, j) = l(i, j) * value;
                }
            }
            return result;
        }

        matrix<T> get_minor_matrix(size_t row, size_t column) {
            if (row < rows_ && column < columns_) {
                matrix<T> result(rows_ - 1, columns_ - 1);
                size_t row_pos = 0;
                for (size_t i = 0; i < rows_; ++i) {
                    if (i == row) continue;
                    size_t column_pos = 0;
                    for (size_t j = 0; j < columns_; ++j) {
                        if (j == column) continue;
                        result(row_pos, column_pos) = *representation_[i][j];
                        column_pos += 1;
                    }
                    row_pos += 1;
                }
                return result;
            } else {
                throw std::out_of_range("Wrong number of rows or columns!");
            }
        }

        void transpose() {
            std::vector<T> new_data;
            for (size_t j = 0; j < columns_; ++j) {
                for (size_t i = 0; i < rows_; ++i) {
                    new_data.push_back(data_[i * columns_ + j]);
                }
            }

            std::swap(columns_, rows_);
            data_ = std::move(new_data);
            representation_.clear();

            for (size_t i = 0; i < rows_; ++i) {
                std::vector<T *> current_row(columns_);
                for (size_t j = 0; j < columns_; ++j) {
                    current_row[j] = &(data_[i * columns_ + j]);
                }
                representation_.push_back(std::move(current_row));
            }
        }

        matrix<T> adj() {
            if (rows_ != columns_) {
                throw std::logic_error("Matrix have adjugate matrix if (rows == columns)");
            } else {
                matrix<T> result(rows_, columns_);
                for (size_t i = 0; i < rows_; ++i) {
                    for (size_t j = 0; j < columns_; ++j) {
                        result(i, j) = this->get_minor_matrix(i, j).det();
                        if ((i + j) % 2) {
                            result(i, j) = -result(i, j);
                        }
                    }
                }
                result.transpose();
                return result;
            }
        }

        matrix<double> reverse() {
            if (rows_ != columns_) {
                throw std::logic_error("The matrix must be square!");
            } else if (this->det() == 0) {
                throw std::logic_error("The determinant of the matrix is 0. The reversed matrix does not exist!");
            } else {
                matrix<double> result(rows_, columns_);
                matrix<double> adj = this->adj();
                double det = 1/(this->det());

                for (size_t i = 0; i < rows_; ++i) {
                    for (size_t j = 0; j < columns_; ++j) {
                        result(i,j) = adj(i,j)*det;
                    }
                }
                return result;
            }
        }

//        size_t r_count() {
//            return rows_;
//        }
//
//        size_t c_count() {
//            return columns_;
//        }
//
//        size_t size() {
//            return rows_*columns_;
//        }

    private:
        void permute(std::vector<size_t> &a, size_t pos, T &value, int &sign) {
            if (pos == 1) {
                T mrow = T(1);
                for (size_t i = 0; i < columns_; ++i) {
                    mrow *= *this->representation_[i][a[i]];
                }
                value += (mrow * sign);
            } else {
                for (size_t i = 0; i < pos; ++i) {
                    permute(a, pos - 1, value, sign);
                    if (pos % 2) {
                        std::swap(a[0], a[pos - 1]);
                    } else {
                        std::swap(a[i], a[pos - 1]);
                        sign *= (-1);
                    }
                }
            }
        }

//        void clear_() {
//            data_.clear();
//            representation_.clear();
//        }

        std::vector<T> data_;
        std::vector<std::vector<T *>> representation_;

        size_t rows_;
        size_t columns_;
    };
}