#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <new>

template <typename T>
class Vector {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    class iterator {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        iterator() : ptr_(0) {}
        explicit iterator(T* p) : ptr_(p) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp(*this); ++ptr_; return tmp; }
        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator tmp(*this); --ptr_; return tmp; }

        iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }
        iterator operator+(difference_type n) const { return iterator(ptr_ + n); }
        iterator operator-(difference_type n) const { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }

        reference operator[](difference_type n) const { return ptr_[n]; }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

    private:
        T* ptr_;
        friend class const_iterator;
    };

    class const_iterator {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        const_iterator() : ptr_(0) {}
        explicit const_iterator(const T* p) : ptr_(p) {}
        const_iterator(const iterator& it) : ptr_(it.ptr_) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        const_iterator& operator++() { ++ptr_; return *this; }
        const_iterator operator++(int) { const_iterator tmp(*this); ++ptr_; return tmp; }
        const_iterator& operator--() { --ptr_; return *this; }
        const_iterator operator--(int) { const_iterator tmp(*this); --ptr_; return tmp; }

        const_iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        const_iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }
        const_iterator operator+(difference_type n) const { return const_iterator(ptr_ + n); }
        const_iterator operator-(difference_type n) const { return const_iterator(ptr_ - n); }
        difference_type operator-(const const_iterator& other) const { return ptr_ - other.ptr_; }

        reference operator[](difference_type n) const { return ptr_[n]; }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const const_iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const const_iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const const_iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const const_iterator& other) const { return ptr_ >= other.ptr_; }

    private:
        const T* ptr_;
    };

    Vector();
    explicit Vector(size_type n, const T& val = T());
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    size_type size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_type new_cap);
    void resize(size_type new_size, const T& val = T());

    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    void push_back(const T& val);
    void pop_back();
    void clear();
    void swap(Vector& other) noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

private:
    T* data_;
    size_type size_;
    size_type capacity_;

    void destroy_range(T* first, T* last);
    void construct_range(size_type n, const T& val);
};

template <typename T>
Vector<T>::Vector() : data_(0), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_type n, const T& val) : data_(0), size_(0), capacity_(0) {
    if (n > 0) {
        reserve(n);
        construct_range(n, val);
        size_ = n;
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other) : data_(0), size_(0), capacity_(0) {
    reserve(other.size_);
    for (size_type i = 0; i < other.size_; ++i)
        new (data_ + i) T(other.data_[i]);
    size_ = other.size_;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : data_(other.data_)
    , size_(other.size_)
    , capacity_(other.capacity_)
{
    other.data_ = 0;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    clear();
    ::operator delete(data_);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        clear();
        ::operator delete(data_);
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = 0;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
void Vector<T>::reserve(size_type new_cap) {
    if (new_cap <= capacity_)
        return;
    T* new_data = static_cast<T*>(::operator new(new_cap * sizeof(T)));
    for (size_type i = 0; i < size_; ++i) {
        new (new_data + i) T(data_[i]);
        data_[i].~T();
    }
    ::operator delete(data_);
    data_ = new_data;
    capacity_ = new_cap;
}

template <typename T>
void Vector<T>::resize(size_type new_size, const T& val) {
    if (new_size < size_) {
        destroy_range(data_ + new_size, data_ + size_);
    }
    else if (new_size > size_) {
        if (new_size > capacity_)
            reserve(new_size);
        for (size_type i = size_; i < new_size; ++i)
            new (data_ + i) T(val);
    }
    size_ = new_size;
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
    return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
    return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if (pos >= size_)
        throw std::out_of_range("Vector::at");
    return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
    if (pos >= size_)
        throw std::out_of_range("Vector::at");
    return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
    return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return data_[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
    return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return data_[size_ - 1];
}

template <typename T>
void Vector<T>::push_back(const T& val) {
    if (size_ == capacity_) {
        size_type new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        reserve(new_cap);
    }
    new (data_ + size_) T(val);
    ++size_;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        data_[size_ - 1].~T();
        --size_;
    }
}

template <typename T>
void Vector<T>::clear() {
    destroy_range(data_, data_ + size_);
    size_ = 0;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return iterator(data_);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return iterator(data_ + size_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
    return const_iterator(data_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
    return const_iterator(data_ + size_);
}

template <typename T>
void Vector<T>::destroy_range(T* first, T* last) {
    for (T* p = first; p != last; ++p)
        p->~T();
}

template <typename T>
void Vector<T>::construct_range(size_type n, const T& val) {
    for (size_type i = 0; i < n; ++i)
        new (data_ + i) T(val);
}

#endif