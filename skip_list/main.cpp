#include <iostream>

#include "skip_list.h"

int main(int argc, char** argv) {
    
    Skiplist<int, char> skip_list;

    skip_list.put(3, 'c');
    skip_list.put(2, 'b');
    skip_list.put(8, 'e');
    skip_list.put(34,'f');
    skip_list.put(1, 'g');
    skip_list.put(21, 'h');
    skip_list.put(13, 'g');
    skip_list.traverse();
    char* res = skip_list.get(13);
    std::cout << "key 13 is " << *res << std::endl;
    skip_list.remove(3);
    skip_list.traverse();
    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}