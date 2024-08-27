#include <iostream>

#include "utility.h"

int main(int argc, char** argv) {
    Array<int> array_int;
    array_int.pushBack(2);
    ArrayUtility<int>::traverse(array_int);
    array_int.insert(0, 1);
    array_int.pushBack(3);
    ArrayUtility<int>::traverse(array_int);
    array_int.pushBack(4);
    array_int.pushBack(4);
    ArrayUtility<int>::traverse(array_int);
    array_int.pushBack(5);
    array_int.pushBack(6);
    ArrayUtility<int>::traverse(array_int);
    array_int.remove(4);
    ArrayUtility<int>::traverse(array_int);
    array_int.pushBack(7);
    array_int.pushBack(8);
    array_int.pushBack(9);
    array_int.pushBack(10);
    array_int.pushBack(11);
    array_int.pushBack(13);
    ArrayUtility<int>::traverse(array_int);

    size_t index = array_int.find(10);
    assert(index == 9);
    index = array_int.find(12);
    assert(index == array_int.size());

    array_int.search(10, index);
    assert(index == 9);
    array_int.search(12, index);
    assert(index == array_int.size());

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}