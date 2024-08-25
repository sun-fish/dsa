#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <queue>
#include <stack>

#include "binary_tree/binary_tree.h"

template <typename T>
class BinarySearchTree : public BinaryTree<T> {
   public:
    virtual BinaryTree<T>* search(const T& e);
    virtual BinaryTree<T>* insert(const T& e);
    virtual BinaryTree<T>* remove(const T& e);

   protected:
    BinaryTree<T>* hot_;  // hits node's parent

    /* BinaryTree<T>* connect34(BinaryTree<T>* tree11, BinaryTree<T>* tree12, BinaryTree<T>* tree13,
                                BinaryTree<T>* tree21, BinaryTree<T>* tree22, BinaryTree<T>* tree23, BinaryTree<T>*);
    BinaryTree<T>* rotateAt(BinaryTree<T>*<T> x);*/
};

#endif