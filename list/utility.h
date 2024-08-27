#ifndef LIST_UTILITY
#define LIST_UTILITY

#include <assert.h>

#include <iostream>

#include "list.h"

template <typename T>
class ListUtility {
   public:
    static void traverse(List<T>& list) {
        if (list.empty()) {
            std::cout << "list is empty!" << std::endl;
            return;
        }

        ListNode<T>* current_node = list.front();
        while (current_node != list.back()) {
            std::cout << current_node->data_ << "    ";
            current_node = current_node->succ_;
        }

        // print the last list node value
        std::cout << current_node->data_ << "    ";
        std::cout << std::endl << "list traverse finished!" << std::endl;
    }
};

#endif  // !LIST_UTILITY