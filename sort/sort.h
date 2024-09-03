#ifndef SORT_H
#define SORT_H

#include <functional>
#include <vector>

#include "list/list.h"
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
                if (input[j - 1] > input[j]) {
                    std::swap(input[j], input[j - 1]);
                }
            }
        }
        return input;
    }

    static std::vector<Key> selectionSort(std::vector<Key> input) {
        for (size_t i = 0; i < input.size(); ++i) {
            size_t minimun_element_index = i;
            for (size_t j = i + 1; j < input.size(); ++j) {
                if (input[j] < input[minimun_element_index]) {
                    minimun_element_index = j;
                }
            }
            std::swap(input[i], input[minimun_element_index]);
        }
        return input;
    }

    static std::vector<Key> insertionSort(std::vector<Key> input) {
        for (size_t i = 1; i < input.size(); ++i) {
            Key element = input[i];
            for (size_t j = i - 1; j != -1; --j) {
                if (element < input[j]) {
                    input[j + 1] = input[j];
                } else {
                    input[j + 1] = element;
                    break;
                }
            }
            if (element < input[0]) {
                input[0] = element;
            }
        }

        return input;
    }

    static void vectorMerge(std::vector<Key>& input, size_t low, size_t mid, size_t high) {
        std::vector<Key> temp(high - low);
        size_t current_low_index = low;
        size_t current_high_index = mid;

        for (size_t i = 0; i < high - low; ++i) {
            if (current_low_index == mid) {
                temp[i] = input[current_high_index++];
                continue;
            }
            if (current_high_index == high) {
                temp[i] = input[current_low_index++];
                continue;
            }
            if (input[current_low_index] < input[current_high_index]) {
                temp[i] = input[current_low_index++];
            } else {
                temp[i] = input[current_high_index++];
            }
        }

        for (size_t i = 0; i < high - low; ++i) {
            input[low + i] = temp[i];
        }
        return;
    }

    // left close, right open
    static void vectorMergeSort(std::vector<Key>& input, size_t low, size_t high) {
        assert(low <= high);
        if (low + 1 == high) return;
        size_t mid = (high - low) / 2 + low;
        vectorMergeSort(input, low, mid);
        vectorMergeSort(input, mid, high);
        vectorMerge(input, low, mid, high);
        return;
    }

    // left close, right close
    // select the low index value to be compared value,
    // if want to use other compare value, fisrt swap the value to low index position
    // [below compare value][undefied low high][above compare value]
    // low index positon can be write ---> high index positon can be write ---> low index positon can be write
    // each itaration, keep low index positon can be write, and decrease the undefined [low, high] length
    static size_t partition1(std::vector<Key>& input, size_t low, size_t high) {
        Key compare_value = input[low];
        while (low < high) {
            // low index positon can be write
            while (low < high) {
                if (compare_value < input[high]) {
                    --high;
                } else {
                    // high index position can be wirte
                    input[low] = input[high];
                    ++low;
                    break;
                }
            }

            // high index positon can be write
            while (low < high) {
                if (input[low] < compare_value) {
                    ++low;
                } else {
                    // low index position can be write
                    input[high] = input[low];
                    --high;
                    break;
                }
            }
        }
        input[low] = compare_value;
        return low;
    }

    // left close, right close
    // [below compare value low mid] [above compare value ][undefied low high, k high]
    // image input[low] is minimum
    static size_t partition2(std::vector<Key>& input, size_t low, size_t high) {
        Key compare_value = input[low];
        // input[low] = min(input) - 1;
        int below_compare_value_index_end = low;
        for (int i = low + 1; i <= high; ++i) {
            if (input[i] < compare_value) {
                ++below_compare_value_index_end;
                std::swap(input[i], input[below_compare_value_index_end]);
            }
        }
        input[below_compare_value_index_end] = compare_value;
        return below_compare_value_index_end;
    }

    // left close, right close
    static void quickSort(std::vector<Key>& input, size_t low, size_t high) {
        if (low >= high) return;
        int pivot = partition1(input, low, high);
        quickSort(input, low, pivot);
        quickSort(input, pivot + 1, high);
    }

    // merge sorted list1 and sorted list2
    static void sortedListMerge(List<Key>* list1, List<Key>* list2) {
        if (list1 == nullptr || list2 == nullptr) return;
        ListNode<Key>* current_list1_node = list1->front();
        ListNode<Key>* current_list2_node = list2->front();

        while (current_list1_node->succ_ != nullptr && current_list2_node->succ_ != nullptr) {
            if (current_list1_node->data_ > current_list2_node->data_) {
                // remove current_list2_node from list2
                auto current_list2_node_pred = current_list2_node->pred_;
                auto current_list2_node_succ = current_list2_node->succ_;
                current_list2_node_pred->succ_ = current_list2_node_succ;
                current_list2_node_succ->pred_ = current_list2_node_pred;
                // insert current_list2_node before current_list1_node
                auto current_list1_node_pred = current_list1_node->pred_;
                current_list1_node_pred->succ_ = current_list2_node;
                current_list2_node->pred_ = current_list1_node_pred;
                current_list1_node->pred_ = current_list2_node;
                current_list2_node->succ_ = current_list1_node;

                current_list2_node = current_list2_node_succ;
            } else {
                current_list1_node = current_list1_node->succ_;
            }
        }

        while (current_list2_node->succ_ != nullptr) {
            // remove current_list2_node from list2
            auto current_list2_node_pred = current_list2_node->pred_;
            auto current_list2_node_succ = current_list2_node->succ_;
            current_list2_node_pred->succ_ = current_list2_node_succ;
            current_list2_node_succ->pred_ = current_list2_node_pred;
            // insert current_list2_node after current_list1_node
            auto current_list1_node_pred = current_list1_node->pred_;
            current_list1_node_pred->succ_ = current_list2_node;
            current_list2_node->pred_ = current_list1_node_pred;
            current_list2_node->succ_ = current_list1_node;
            current_list1_node->pred_ = current_list2_node;
            current_list2_node = current_list2_node_succ;
        }
    }

    // only use succ
    // merge algorithm case:
    // list1 4---->9---->10---->11
    // list2 2---->3---->7---->8----->12
    static ListNode<Key>* sortedListMerge(ListNode<Key>* head_node, ListNode<Key>* head_node1) {
        if (head_node == nullptr) return head_node1;
        if (head_node1 == nullptr) return head_node;

        ListNode<Key>* current_list1_node = head_node;
        ListNode<Key>* current_list2_node = head_node1;
        ListNode<Key>* pred_list1_node = nullptr;
        ListNode<Key>* new_head = head_node;
        while (current_list1_node != nullptr && current_list2_node != nullptr) {
            if (current_list1_node->data_ > current_list2_node->data_) {
                auto current_list2_node_succ = current_list2_node->succ_;
                current_list2_node->succ_ = current_list1_node;
                if (pred_list1_node == nullptr) {
                    new_head = current_list2_node;
                    pred_list1_node = current_list2_node;
                    
                } else {
                    pred_list1_node->succ_ = current_list2_node;
                    pred_list1_node = current_list2_node;
                }
                current_list2_node = current_list2_node_succ;
            } else {
                pred_list1_node = current_list1_node;
                current_list1_node = current_list1_node->succ_;
            }
        }

        if (current_list2_node != nullptr) {
            assert(pred_list1_node != nullptr);
            pred_list1_node->succ_ = current_list2_node;
        }

        return new_head;
    }

    static ListNode<Key>* listMergeSort(ListNode<Key>* head_node, size_t n) {
        if (n < 2) {
            if (head_node != nullptr) {
                head_node->succ_ = nullptr;
            }
            return head_node;
        }
        size_t mid = n / 2;
        ListNode<Key>* head_node1 = head_node;
        ListNode<Key>* pre_node = nullptr;
        for (int i = 0; i < mid; ++i) {
            pre_node = head_node1;
            head_node1 = head_node1->succ_;
        }
        pre_node->succ_ = nullptr;
        auto head1 = listMergeSort(head_node, mid);
        auto head2 = listMergeSort(head_node1, n - mid);
        return sortedListMerge(head1, head2);
    }
};

#endif