#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_node.h"

template <typename T>
class BinaryTree {
   public:
    BinaryTree(){};

   private:
    size_t size_;
    BinaryNode<T>* root_;
};

#endif