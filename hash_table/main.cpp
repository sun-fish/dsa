#include <iostream>

#include "hash_table.h"

int main(int argc, char** argv) {
    HashtableChain<int, char> hash_table_chain;
    for (size_t i = 0; i < 16; ++i) {
        hash_table_chain.put(i, 'a' + i);
    }
    hash_table_chain.put(30, 'T');
    hash_table_chain.traverse();
    hash_table_chain.remove(30);
    hash_table_chain.traverse();
    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}