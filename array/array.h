#ifndef ARRAY_H
#define ARRAY_H

#include <assert.h>
#include <math.h>

template <typename T>
class Array {
   protected:
    size_t size_;
    size_t capacity_;
    T* elements_;

    void copyFrom(T const* A, size_t low, size_t high) {
        elements_ = new T[capacity_ = std::max<size_t>(10, 2 * (high - low))];
        for (size_ = 0; low < high; ++size_, ++low) elements_[size_] = A[low];
    }
    void expand() {
        if (size_ < capacity_) return;
        if (capacity_ < 10) capacity_ = 10;
        T* old_elements = elements_;
        elements_ = new T[capacity_ <<= 1];
        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = old_elements[i];
        }
        delete[] old_elements;
    }

    void shrink() {
        if ((size_ * 4) > capacity_) return;  // 25% is the threshold
        T* old_elements = elements_;
        elements_ = new T[capacity_ / 2 + 1];
        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = old_elements[i];
        }
        delete[] old_elements;
    }

   public:
    Array(size_t capcity = 10, size_t size = 0, T value = 0) {
        if (capacity_ < size) {
            capacity_ = 0;
            size_ = 0;
            return;
        }

        elements_ = new T[capacity_ = capcity];
        assert(capacity_ > size);
        for (size_ = 0; size_ < size;) {
            elements_[size_++] = value;
        }
    }

    Array(T const* array, size_t size) { copyFrom(array, 0, size); }
    Array(T const* array, size_t low, size_t high) { copyFrom(array, low, high); }
    Array(Array<T> const& array) { copyFrom(array.elements_, 0, array.size_); }
    Array(Array<T> const& array, size_t low, size_t high) { copyFrom(array.elements_, low, high); }

    ~Array() { delete[] elements_; }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    size_t find(T const& e) const { return find(e, 0, size_); }
    size_t find(T const& e, size_t low, size_t high) const {
        while (low < high) {
            if (elements_[low] == e) break;
            ++low;
        }
        return low;
    }

    bool search(T const& e, size_t& index) { return (0 >= size_) ? false : search(e, 0, size_, index); }

    // binary search
    bool search(T const& e, size_t low, size_t high, size_t& index) {
        if (low >= size_ || high > size_ || low >= high) return false;

        while (low < high) {
            size_t mid = (high - low) / 2 + low;
            if (elements_[mid] < e) {
                low = mid + 1;
            } else if (elements_[mid] == e) {
                index = mid;
                return true;
            } else {
                high = mid;
            }
        }

        index = size_;
        return false;
    }

    T& operator[](size_t index) {
        assert(index < size_);
        return elements_[index];
    }

    const T& operator[](size_t index) const {
        assert(index < size_);
        return elements_[index];
    }

    Array<T>& operator=(Array<T> const& array) {
        if (elements_) delete[] elements_;
        copyFrom(array.elements_, array.size());
        return *this;
    }

    T remove(size_t index) {
        assert(index < size_);
        T res = elements_[index];
        remove(index, index + 1);
        return res;
    }

    // left close and right open
    size_t remove(size_t low, size_t high) {
        assert(low <= size_);
        assert(high <= size_);
        if (low == high) return 0;

        while (high < size_) {
            elements_[low] = elements_[high];
            ++high;
            ++low;
        }
        size_ = low;
        shrink();
        return high - low;
    }

    size_t insert(size_t index, T const& e) {
        expand();
        for (size_t i = size_; i > index; --i) {
            elements_[i] = elements_[i - 1];
        }
        elements_[index] = e;
        ++size_;
        return index;
    }

    size_t pushBack(T const& e) { return insert(size_, e); }
};

#endif  // ARRAY_H