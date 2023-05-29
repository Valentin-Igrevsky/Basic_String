#include <iostream>
#include <cassert>

namespace bmstu {
    template<typename T>
    class list {
        struct node {
            node() = default;

            node(node *prev, const T &value, node *next) : next_node(next), value_(value), prev_node(prev) {}

            ~node() = default;

            T value_ = {};
            node *next_node = nullptr;
            node *prev_node = nullptr;
        };

    public:
        template<typename value_t>
        struct list_iterator {
            friend class list;

            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = value_t;
            using pointer = value_t *;
            using reference = value_t &;

            list_iterator() = default;

            list_iterator(node *node) : node_(node) {}

            list_iterator(const list_iterator<T> &other) noexcept: node_(other.node_) {}

            reference operator*() const {
                assert(node_ != nullptr);
                return static_cast<T &> (node_->value_);
            }

            pointer operator->() {
                assert(node_ != nullptr);
                return static_cast<T *> (&(node_->value_));
            }

            list_iterator &operator++() {
                assert(node_ != nullptr);
                if (node_->next_node == nullptr) {
                    throw std::logic_error("You can't access the element after tail!");
                }
                node_ = node_->next_node;
                return *this;
            }

            list_iterator &operator--() {
                assert(node_ != nullptr);
                if (node_->prev_node == nullptr) {
                    throw std::logic_error("You can't access the element before head!");
                }
                node_ = node_->prev_node;
                return *this;
            }

            list_iterator &operator=(const list_iterator &other) = default;

            list_iterator operator++(int) {
                list_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            list_iterator operator--(int) {
                list_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const list_iterator &a, const list_iterator &b) {
                return a.node_ == b.node_;
            }

            friend bool operator!=(const list_iterator &a, const list_iterator &b) {
                return !(a == b);
            }

            explicit operator bool() {
                return node_ != nullptr;
            }

            list_iterator operator+(const difference_type value) noexcept {
                list_iterator copy(*this);
                for (auto i = 1; i <= value; ++i) {
                    ++(copy);
                }
                return copy;
            }

            template<typename Integer>
            list_iterator operator+(Integer value) noexcept {
                list_iterator copy(*this);
                for (auto i = 1; i <= value; ++i) {
                    ++(copy);
                }
                return copy;
            }

            list_iterator operator-(const difference_type value) noexcept {
                list_iterator copy(*this);
                for (auto i = 1; i <= value; ++i) {
                    --(copy);
                }
                return copy;
            }

            list_iterator operator+=(const difference_type value) noexcept {
                return ((*this) + value);
            }

            friend difference_type operator-(const list_iterator &end, const list_iterator &begin) {
                difference_type result{};
                list_iterator copy(begin);
                for (result = 0; copy != end; ++copy) {
                    ++result;
                }
                return result;
            }

        private:
            node *node_ = nullptr;
        };

        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = list_iterator<T>;
        using const_iterator = list_iterator<const T>;

        list() : size_(0), tail_(new node()), head_(new node()) {
            head_->next_node = tail_;
            tail_->prev_node = head_;
        }

        template<typename it>
        list(it begin, it end) {
            list<T> tmp;
            it copy(begin);
            while (copy != end) {
                tmp.push_back(*copy);
                ++copy;
            }
            swap(tmp);
        }

        list(std::initializer_list<T> values) {
            list<T> tmp;
            for (const auto &val: values) {
                tmp.push_back(val);
            }
            swap(tmp);
        }

        list(const list &other) {
            if (this != &other) {
                list<T> tmp;
                for (const auto &item: other) {
                    tmp.push_back(item);
                }
                swap(tmp);
            }
        }

        list(list &&other) {
            swap(other);
        }

        template<typename Type>
        void push_back(const Type &value) {
            node *last = tail_->prev_node;
            node *new_last = new node(tail_->prev_node, value, tail_);
            tail_->prev_node = new_last;
            last->next_node = new_last;
            ++size_;
        }

        template<typename Type>
        void push_front(const Type &value) {
            node *first = head_->next_node;
            node *new_first = new node(head_, value, first);
            head_->next_node = new_first;
            first->prev_node = new_first;
            ++size_;
        }

        bool empty() const noexcept {
            return (size_ == 0u);
        }

        ~list() {
            clear();
            delete tail_;
            delete head_;
        }

        void clear() {
            if (empty()) {
                return;
            } else {
                while (head_->next_node != tail_) {
                    node *next = head_->next_node;
                    head_->next_node = next->next_node;
                    delete next;
                }
                tail_->prev_node = head_;
                size_ = 0;
            }
        }

        void swap(list &other) noexcept {
            std::swap(head_, other.head_);
            std::swap(tail_, other.tail_);
            std::swap(size_, other.size_);
        }

        friend void swap(list &l, list &r) {
            l.swap(r);
        }

        iterator begin() noexcept {
            return iterator{head_->next_node};
        }

        iterator end() noexcept {
            return iterator{tail_};
        }

        const_iterator begin() const noexcept {
            return const_iterator{head_->next_node};
        }

        const_iterator end() const noexcept {
            return const_iterator{tail_};
        }

        const_iterator cbegin() const noexcept {
            return const_iterator{head_->next_node};
        }

        const_iterator cend() const noexcept {
            return const_iterator{tail_};
        }

        T operator[](size_t pos) const {
            return *(begin() + pos);
        }

        T &operator[](size_t pos) {
            return *(begin() + pos);
        }

        size_t size() const {
            return size_;
        }

        friend bool operator==(const list &l, const list &r) {
            if (l.size_ != r.size_) {
                return false;
            } else {
                auto l_b = l.begin();
                auto r_b = r.begin();
                while (l_b != l.end() && r_b != r.end()) {
                    if (*l_b != *r_b) {
                        return false;
                    }
                    ++l_b;
                    ++r_b;
                }
            }
            return true;
        }

        friend bool operator!=(const list<T> &left, const list<T> &right) {
            return !(left == right);
        }

        friend bool operator<(const list<T> &left, const list<T> &right) {
            return lexicographical_compare_(left, right);
        }

        friend bool operator>(const list<T> &left, const list<T> &right) {
            return (right < left);
        }

        friend bool operator<=(const list<T> &left, const list<T> &right) {
            return !(right < left);
        }

        friend bool operator>=(const list<T> &left, const list<T> &right) {
            return !(left < right);
        }

        friend std::ostream &operator<<(std::ostream &os, const list<T> &other) {
            os << "{";
            if (other.size_) {
                for (int i = 0; i < other.size_ - 1; ++i) {
                    os << other[i] << ", ";
                }
                os << other[other.size_ - 1];
            }
            os << "}";
            return os;
        }

        iterator insert(const_iterator pos, const T &value) {
            if (pos.node_->next_node == nullptr) {
                throw std::logic_error("You can't insert an element after end");
            }
            node *new_node = new node(pos.node_, value, pos.node_->next_node);
            pos.node_->next_node->prev_node = new_node;
            /// Или лучше так (?)
///            node *next_node = pos.node_->next_node;
///            next_node->prev_node = new_node;
            pos.node_->next_node = new_node;
            ++size_;
            return iterator{new_node};
        }

    private:
        static bool lexicographical_compare_(const list<T> &left, const list<T> &right) {
            auto fl = left.begin(), fr = right.begin();
            for (; (fl != left.end()) && (fr != right.end()); ++fl, ++fr) {
                if (*fl < *fr) {
                    return true;
                }
                if (*fr < *fl) {
                    return false;
                }
            }
            return (fr == right.end()) && (fl == left.end());
        }

        size_t size_ = 0;
        node *tail_ = nullptr;
        node *head_ = nullptr;
    };
}