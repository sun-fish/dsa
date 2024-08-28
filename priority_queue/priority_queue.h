#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <assert.h>

#include "array/array.h"
#include "utility.h"

template <typename T>
class PriorityQueue {
   public:
    virtual void insert(T) = 0;
    virtual T getMax() = 0;
    virtual void delMax() = 0;
};

// complete binary heap
template <typename T>
class PriorityQueueArray : public PriorityQueue<T>, public Array<T> {
   public:
    PriorityQueueArray(){};
    PriorityQueueArray(T* vector, size_t size) { 
        Array<T>::copyFrom(vector, 0, size); 
        PriorityQueueArrayUtility<T>::heapify(elements_, size_);
    }
    virtual void insert(T val) override {
        pushBack(val);
        PriorityQueueArrayUtility<T>::heapNodeUp(elements_, size() - 1);
    }
    virtual T getMax() override { return elements_[0]; }
    virtual void delMax() override {
        if (empty()) return;
        std::swap(elements_[0], elements_[--size_]);
        if (empty()) return;
        PriorityQueueArrayUtility<T>::heapNodeDown(elements_, size(), 0);
    }
};

#endif