#include <iostream>

#include "priority_queue.h"
#include <vector>

int main(int argc, char** argv) {
    int a[5] = {4, 2, 5, 1, 3};
    auto priority_queue_array = PriorityQueueArray<int>(a, 5);
    priority_queue_array.insert(6);
    priority_queue_array.insert(10);
    while (!priority_queue_array.empty()) {
        std::cout << priority_queue_array.getMax() << "    ";
        priority_queue_array.delMax();
    }
    std::cout << std::endl << "priority queue array traverse finished!" << std::endl;
    PriorityQueueBinaryTree<int> priority_queue_binary_tree(a, 5);
    priority_queue_binary_tree.insert(6);
    priority_queue_binary_tree.insert(10);
    while (!priority_queue_binary_tree.empty()) {
        std::cout << priority_queue_binary_tree.getMax() << "    ";
        priority_queue_binary_tree.delMax();
    }
    std::cout << std::endl << "priority queue array traverse finished!" << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}