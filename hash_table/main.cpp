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
    std::cout << std::endl;

    HashtableOpenAddress<int, char> hash_table_open_address;
    for (size_t i = 0; i < 16; ++i) {
        hash_table_open_address.put(i, 'a' + i);
    }
    hash_table_open_address.put(30, 'T');
    hash_table_open_address.traverse();
    hash_table_open_address.remove(1);
    char *v = hash_table_open_address.get(30);
    assert(*v == 'T');
    hash_table_open_address.traverse();
    hash_table_open_address.put(1, 'b');
    hash_table_open_address.traverse();
    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}