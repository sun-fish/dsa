#include <iostream>

#include "list.h"
#include "utility.h"

int main(int argc, char** argv) {
    List<int> list;
    ListUtility<int>::traverse(list);
    int node_value = 2;
    ListNode<int>* list_node = list.insertAsFirst(node_value);
    ListUtility<int>::traverse(list);
    node_value = 1;
    list.insert(node_value, list_node);
    ListUtility<int>::traverse(list);
    node_value = 3;
    list.insert(list_node, node_value);
    ListUtility<int>::traverse(list);
    node_value = 4;
    list.insertAsLast(node_value);
    ListUtility<int>::traverse(list);

    list.insertAsLast(5);
    ListUtility<int>::traverse(list);
    std::cout << "list size is " << list.size() << std::endl;

    list.remove(list_node);
    ListUtility<int>::traverse(list);
    std::cout << "list size is " << list.size() << std::endl;

    list_node = list.find(2);
    if (list_node == nullptr) {
        std::cout << "can not find value 2 in list" << std::endl;
    }

    list_node = list.find(1);
    if (list_node != nullptr) {
        std::cout << "find value 1 in list" << std::endl;
    }

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}