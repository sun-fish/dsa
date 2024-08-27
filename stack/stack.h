#ifndef STACK_H
#define STACK_H

#include <iostream>

#include "list/list.h"
template <typename T>
class Stack {
   public:
    void push(T const& e) { list_.insertAsLast(e); }

    void pop() {
        if (!list_.empty()) {
            list_.remove(list_.back());
        }
    }

    T& top() {
        if (!list_.empty()) {
            return list_.back()->data_;
        } else {
            assert(true);
            std::cout << "stack is empty, error use!" << std::endl;
            T res;
            return res;
        }
    }

    bool empty() { return list_.empty(); }

   private:
    List<T> list_;
};

#endif