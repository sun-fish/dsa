#ifndef SORT_H
#define SORT_H

#include <functional>
#include <vector>

#include "priority_queue/utility.h"
#include "public/entry.h"

template <typename Key = size_t, typename Value = size_t>
class Sort {
   public:
    static std::vector<Entry<size_t, Value>> bucketSort(std::vector<Entry<size_t, Value>>& input) {
        if (input.empty()) return std::vector<Entry<size_t, Value>>();
        size_t max_key = input.begin()->key;
        for (auto& entry : input) {
            if (entry.key > max_key) {
                max_key = entry.key;
            }
        }
        max_key += 2;
        auto hash_function = [&max_key](size_t key) -> size_t { return key % max_key; };

        std::vector<size_t> counter(max_key, 0);
        for (auto& entry : input) {
            size_t hash_result = hash_function(entry.key);
            ++counter[hash_result];
        }

        // prefix[i] is the sum of counter[j](j = 0, 1, ..., i) which indicate the last key appear position
        std::vector<size_t> prefix(max_key, 0);
        prefix[0] = counter[0];
        for (size_t i = 1; i < prefix.size(); ++i) {
            prefix[i] = prefix[i - 1] + counter[i];
        }

        std::vector<Entry<size_t, Value>> output(input.size());

        for (auto it = input.rbegin(); it != input.rend(); ++it) {
            size_t hash_result = hash_function(it->key);
            --prefix[hash_result];
            output[prefix[hash_result]] = *it;
        }

        return output;
    }

    static std::vector<Key> heapSort(Key* heap_sort_input, size_t size) {
        if (size >= 2) {
            PriorityQueueArrayUtility<Key>::heapify(heap_sort_input, size);
            for (size_t i = size - 1; i > 0; --i) {
                std::swap(heap_sort_input[0], heap_sort_input[i]);
                PriorityQueueArrayUtility<Key>::heapNodeDown(heap_sort_input, i, 0);
            }
        }
        return std::vector<Key>(heap_sort_input, heap_sort_input + size);
    }

    static std::vector<Key> bubbleSort(std::vector<Key> input) {
        for (int i = input.size(); i != 0; --i) {
            for (int j = 1; j < i; ++j) {
                if (input[j -1] > input[j]) {
                    std::swap(input[j], input[j - 1]);
                }
            }
        }
        return input;
    }

    static std::vector<Key> selectionSort(std::vector<Key> input) {
        std::vector<key> output;
        return output;
    }

    static void vectorMerge(size_t low, size_t mid, size_t high) {
        int res = low;
        int res1 = high;
        return;
    }

    static std::vector<Key> vectorMergeSort(std::vector<Key> input) {
        std::vector<key> output;
        return output;
    }

    // static void listMerge(size_t low, size_t mid, size_t high) {}

    // static std::vector<Key> listMergeSort(std::vector<Key> input) {
    //     std::vector<key> output;
    //     return output;
    // }

    // static std::vector<Key> partition(std::vector<Key> input) {
    //     std::vector<key> output;
    //     return output;
    // }

    static std::vector<Key> quickSort(std::vector<Key> input) {
        std::vector<key> output;
        return output;
    }

    static std::vector<Key> shellSort(std::vector<Key> input) {
        std::vector<key> output;
        return output;
    }
};

#endif