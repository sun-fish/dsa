#include <iostream>
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
    hash_sort_input.push_back(Entry<size_t, std::string>(1, "zhao" ));
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
    for (auto& key : bubble_sort_output) {
        std::cout << key << ",";
    }
    std::cout << std::endl;



    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}