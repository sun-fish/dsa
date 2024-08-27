#ifndef ARRAY_UTILITY
#define ARRAY_UTILITY

#include <assert.h>
#include <iostream>

#include "array.h"

template <typename T>
class ArrayUtility {
    // void sort(Rank lo, Rank hi);
    // void sort() { sort(0, _size); }
    // void unsort(Rank lo, Rank hi);
    // void unsort() { unsort(0, _size); }
    // Rank dedup();
    // Rank uniquify();

   public:
    static void traverse(Array<T>& array) {
        for (int i = 0; i < array.size(); ++i) {
            std::cout << array[i] << "    ";
        }
        std::cout << std::endl << "Array traverse finished!" << std::endl;
    }
};

#endif  // !ARRAY_UTILITY