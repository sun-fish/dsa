#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>

#include "list/list.h"
template <typename T>
class Queue {
   public:
    void enqueue(T const& e) { list_.insertAsLast(e); }

    T dequeue() {
        if (!list_.empty()) return list_.remove(list_.front());
    }

    T& front() {
        if (!list_.empty())
            return list_.front()->data_;
        else {
            assert(true);
            T res;
            return res;
        }
    }

    bool empty() { return list_.empty(); }

   private:
    List<T> list_;
};

#endif