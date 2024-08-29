#ifndef STRING_H
#define STRING_H

#include <malloc.h>
#include <string.h>

#include <iostream>

template <typename T>
class String {
   public:
    String(T ch, size_t number) {
        size_ = number;
        string_ = static_cast<T *>(malloc(size_ * sizeof(T)));
        for (size_t i = 0; i < size_; ++i) {
            string_[i] = ch;
        }
    }

    String(T *string = nullptr, size_t length = 0) {
        if (string != nullptr && length != 0) {
            size_ = length;
            string_ = static_cast<T *>(malloc(size_ * sizeof(T)));
            memcpy(string_, string, size_ * sizeof(T));
        } else {
            size_ = 0;
            string_ = nullptr;
        }
    }

    String(String<T> &string) { 
        size_ = string.size();
        string_ = static_cast<T *>(malloc(size_ * sizeof(T)));
        memcpy(string_, string.string_, size_ * sizeof(T));
    }

    ~String() {
        size_ = 0;
        free(string_);
    }

    String<T> &operator=(String<T> &string) {
        if (!empty()) free(string_);
        size_ = string.size();
        string_ = static_cast<T *>(malloc(size_ * sizeof(T)));
        memcpy(string_, string.string_, size_ * sizeof(T));
        return *this;
    }

    //String<T> &operator=(T* string) {
    //    if (!empty()) free(string_);
    //    size_ = sizeof(string) / sizeof(T);
    //    string_ = static_cast<T *>(malloc(size_ * sizeof(T)));
    //    memcpy(string_, string, size_ * sizeof(T));
    //    return *this;
    //}

    String<T> &operator+(String<T> &string) {
        size_t new_size = size_ + string.size_;
        T *new_string = static_cast<T *>(malloc((new_size) * sizeof(T)));
        memcpy(new_string, string_, size_ * sizeof(T));
        memcpy(new_string + size_ , string.string_, string.size_ * sizeof(T));
        free(string_);
        string_ = new_string;
        size_ = new_size;
        return *this;
    }

    T operator[](size_t index) {
        assert(index < size_);
        return string_[index];
    }

    bool operator==(String<T> &string) {
        if (size_ != string.size()) return false;
        bool result = true;
        for (size_t i = 0; i < size_; ++i) {
            if (string_[i] != string[i]) {
                result = false;
                break;
            }
        }
        return result;
    }

    bool operator!=(String<T> &string) { return !(*this == string) }

    bool empty() { return size_ == 0; }
    size_t size() { return size_; }

    bool subString(String<T> &string, size_t start, size_t length) {
        if (start >= size_ && start + length > size_) return false;
        if (string.empty()) {
            free(string.string_);
        }
        string.size_ = length;
        string.string_ = static_cast<T*>(malloc(length * sizeof(T)));
        memcpy(string.string_, string_ + start, length * sizeof(T));
    }
    bool prefix(String<T> &string, size_t length) { return subString(string, 0, length); }
    bool suffix(String<T> &string, size_t length) {
        if (length > size_) return false;
        return subString(string, size_ - length, length);
    }

    // if pattern is the sub-string of current string
    // return the start place of the sub-string
    // else return the size of the current string
    size_t indexOf(String<T> &pattern) {
        return 0;  // will be update later
    }

    void print() {
        if (string_ != nullptr) {
            std::wcout << L"String is:";
            for (size_t i = 0; i < size_; ++i) {
                std::wcout << string_[i];
            }
            std::wcout << std::endl;
        }
    }

   private:
    T *string_;
    size_t size_;
};

#endif