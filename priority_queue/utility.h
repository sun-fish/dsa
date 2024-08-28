#ifndef PRIORITY_QUEUE_UTILITY
#define PRIORITY_QUEUE_UTILITY

#include <assert.h>

#include <iostream>

template <typename T>
class PriorityQueueArrayUtility {
   public:
    // floor(i - 1) / 2
    static size_t parent(size_t node_index) {
        if (node_index == 0) return 0;
        return (node_index - 1) / 2;
    }
    static size_t leftChild(size_t node_index) { return 2 * node_index + 1; }
    static size_t rightChild(size_t node_index) { return 2 * node_index + 2; }
    static bool inHeap(size_t heap_size, size_t node_index) { return node_index < heap_size; }
    static bool leftChildValid(size_t heap_size, size_t node_index) {
        size_t left_child = leftChild(node_index);
        return inHeap(heap_size, left_child);
    }
    static bool rightChildValid(size_t heap_size, size_t node_index) {
        size_t right_child = rightChild(node_index);
        return inHeap(heap_size, right_child);
    }

    static void heapify(T *vector, size_t size) {  // floyd head algorithm
        if (size < 2) return;
        size_t index = size / 2 - 1;
        while (index != -1) {
            heapNodeDown(vector, size, index);
            --index;
        }
        return;
    }

    static size_t heapNodeDown(T *vector, size_t size, size_t parent_index) {
        assert(size > 0 && parent_index < size);
        while (true) {
            size_t left_child = leftChild(parent_index);
            size_t right_child = rightChild(parent_index);
            T left_child_value = vector[parent_index];
            T right_child_value = vector[parent_index];
            if (leftChildValid(size, parent_index)) {
                left_child_value = vector[left_child];
            }
            if (rightChildValid(size, parent_index)) {
                right_child_value = vector[right_child];
            }

            if (left_child_value > vector[parent_index]) {
                if (right_child_value > left_child_value) {
                    std::swap(vector[right_child], vector[parent_index]);
                    parent_index = right_child;
                } else {
                    std::swap(vector[left_child], vector[parent_index]);
                    parent_index = left_child;
                }
            } else {
                if (right_child_value > vector[parent_index]) {
                    std::swap(vector[right_child], vector[parent_index]);
                    parent_index = right_child;
                } else {
                    return parent_index;
                }
            }
        }
        return parent_index;
    }

    static size_t heapNodeUp(T *vector, size_t node_index) {
        while (node_index > 0) {
            size_t parent_index = parent(node_index);
            if (vector[parent_index] < vector[node_index]) {
                std::swap(vector[parent_index], vector[node_index]);
                node_index = parent_index;
            } else {
                return node_index;
            }
        }
        return node_index;
    }
};

#endif  // !PRIORITY_QUEUE_UTILITY