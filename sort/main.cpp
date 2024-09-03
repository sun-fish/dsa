#include <iostream>
#include <string>
#include <vector>

#include "sort.h"

int main(int argc, char** argv) {
    std::vector<Entry<size_t, std::string>> hash_sort_input;
    hash_sort_input.push_back(Entry<size_t, std::string>(8, "wang"));
    hash_sort_input.push_back(Entry<size_t, std::string>(7, "zheng"));
    hash_sort_input.push_back(Entry<size_t, std::string>(4, "li"));
    hash_sort_input.push_back(Entry<size_t, std::string>(2, "qian"));
    hash_sort_input.push_back(Entry<size_t, std::string>(1, "zhao"));
    hash_sort_input.push_back(Entry<size_t, std::string>(1, "zhao_1"));
    hash_sort_input.push_back(Entry<size_t, std::string>(3, "sun"));
    hash_sort_input.push_back(Entry<size_t, std::string>(8, "wang_1"));
    hash_sort_input.push_back(Entry<size_t, std::string>(5, "zhou"));
    hash_sort_input.push_back(Entry<size_t, std::string>(6, "wu"));
    hash_sort_input.push_back(Entry<size_t, std::string>(7, "zheng_1"));
    hash_sort_input.push_back(Entry<size_t, std::string>(3, "sun_1"));
    hash_sort_input.push_back(Entry<size_t, std::string>(4, "li_1"));
    hash_sort_input.push_back(Entry<size_t, std::string>(1, "zhao_2"));
    hash_sort_input.push_back(Entry<size_t, std::string>(1, "zhao_3"));
    hash_sort_input.push_back(Entry<size_t, std::string>(8, "wang_4"));
    auto hash_sort_output = Sort<size_t, std::string>::bucketSort(hash_sort_input);
    for (auto& entry : hash_sort_output) {
        std::cout << "key: " << entry.key << ", value: " << entry.value << std::endl;
    }

    size_t heap_sort_input[10] = {9, 8, 7, 1, 2, 3, 5, 4, 10, 6};
    auto heap_sort_output = Sort<>::heapSort(heap_sort_input, 10);
    for (auto& key : heap_sort_output) {
        std::cout << "key: " << key << std::endl;
    }

    std::vector<size_t> bubble_sort_input = {9, 8, 7, 1, 2, 3, 5, 4, 10, 6};
    auto bubble_sort_output = Sort<>::bubbleSort(bubble_sort_input);
    std::cout << "bubble sort:";
    for (auto& key : bubble_sort_output) {
        std::cout << key << ",";
    }
    std::cout << std::endl;

    std::vector<size_t> selection_sort_input = {9, 8, 7, 1, 2, 3, 5, 4, 10, 6};
    auto selection_sort_output = Sort<>::selectionSort(selection_sort_input);
    std::cout << "selection sort:";
    for (auto& key : selection_sort_output) {
        std::cout << key << ",";
    }
    std::cout << std::endl;

    std::vector<size_t> insertion_sort_input = {9, 8, 7, 1, 2, 3, 5, 4, 10, 6};
    auto insertion_sort_output = Sort<>::insertionSort(insertion_sort_input);
    std::cout << "insertion sort:";
    for (auto& key : insertion_sort_output) {
        std::cout << key << ",";
    }
    std::cout << std::endl;

    std::vector<size_t> vector_merge_sort_input = {9, 8, 7, 1, 2, 3, 5, 4, 10, 6};
    Sort<>::vectorMergeSort(vector_merge_sort_input, 0, 10);
    std::cout << "vector merge sort:";
    for (auto& key : vector_merge_sort_input) {
        std::cout << key << ",";
    }
    std::cout << std::endl;

    std::vector<size_t> quick_sort_input = {9, 8, 7, 1, 2, 3, 5, 4, 10, 6};
    Sort<>::quickSort(quick_sort_input, 0, 9);
    std::cout << "quick sort:";
    for (auto& key : quick_sort_input) {
        std::cout << key << ",";
    }
    std::cout << std::endl;

    List<size_t> list1;
    list1.insertAsLast(2);
    list1.insertAsLast(4);
    list1.insertAsLast(6);
    list1.insertAsLast(7);

    List<size_t> list2;
    list2.insertAsLast(1);
    list2.insertAsLast(3);
    list2.insertAsLast(5);
    list2.insertAsLast(8);
    list2.insertAsLast(9);
    list2.insertAsLast(10);

    Sort<>::sortedListMerge(&list1, &list2);
    ListNode<size_t>* current_list1_node = list1.front();
    std::cout << "merge two sorted list:";
    while (current_list1_node->succ_ != nullptr) {
        std::cout << current_list1_node->data_ << ",";
        current_list1_node = current_list1_node->succ_;
    }
    std::cout << std::endl;


    ListNode<size_t> l_node0(4);
    ListNode<size_t> l_node1(9);
    ListNode<size_t> l_node2(10);
    ListNode<size_t> l_node3(12);
    ListNode<size_t> l_node4(2);
    ListNode<size_t> l_node5(3);
    ListNode<size_t> l_node6(7);
    ListNode<size_t> l_node7(8);
    ListNode<size_t> l_node8(11);
    ListNode<size_t> l_node9(13);

    l_node0.succ_ = &l_node1;
    l_node1.succ_ = &l_node2;
    l_node2.succ_ = &l_node3;

    l_node4.succ_ = &l_node5;
    l_node5.succ_ = &l_node6;
    l_node6.succ_ = &l_node7;
    l_node7.succ_ = &l_node8;
    l_node8.succ_ = &l_node9;

    auto l_node = Sort<>::sortedListMerge(&l_node0, &l_node4);

    std::cout << "merge two sorted list:";
    while (l_node != nullptr) {
        std::cout << l_node->data_ << ",";
        l_node = l_node->succ_;
    }
    std::cout << std::endl;

    ListNode<size_t> node0(9);
    ListNode<size_t> node1(8);
    ListNode<size_t> node2(7);
    ListNode<size_t> node3(1);
    ListNode<size_t> node4(2);
    ListNode<size_t> node5(3);
    ListNode<size_t> node6(5);
    ListNode<size_t> node7(4);
    ListNode<size_t> node8(10);
    ListNode<size_t> node9(6);

    node0.succ_ = &node1;
    node1.succ_ = &node2;
    node2.succ_ = &node3;
    node3.succ_ = &node4;
    node4.succ_ = &node5;
    node5.succ_ = &node6;
    node6.succ_ = &node7;
    node7.succ_ = &node8;
    node8.succ_ = &node9;

    auto node = Sort<>::listMergeSort(&node0, 10);
    std::cout << "list merge sort:";
    while (node != nullptr) {
        std::cout << node->data_ << ",";
        node = node->succ_;
    }
    std::cout << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}