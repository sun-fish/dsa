#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_node.h"

template <typename T>
class BinaryTree {
   public:
    BinaryTree() : size_(0), root_(nullptr) {}
    ~BinaryTree() {
        if (0 < size_) deleteChildTree(root_);
    }

    size_t size() const { return size_; }
    bool empty() const { return root_ != nullptr; }

    size_t deleteChildTree(BinaryNode<T>*) {
        // parent pointer need to point nullptr
        // update ancestors' height
        // delete sub tree x
        // return size
        return 0;
    }

    BinaryTree<T>* datachChildTree(BinaryNode<T>*) { return nullptr; }

    BinaryNode<T>* root(){return root_};
    void set_root(BinaryNode<T>* root) { root_ = root;}

    BinaryNode<T>* insertLeftNode(T e, BinaryNode<T>* parent) {
        BinaryNode<T>* left_child = new BinaryNode<T>(e);
        parent->set_left_child(left_child);
        updateHeightAbove(left_child);
        ++size_;
        return parent->left_child();
    }

    BinaryNode<T>* insertRightNode(T e, BinaryNode<T>* parent) {
        BinaryNode<T>* right_child = new BinaryNode<T>(e);
        parent->set_right_child(right_child);
        updateHeightAbove(right_child);
        ++size_;
        return parent->right_child();
    }

    BinaryNode<T>* insertLeftTree(BinaryTree<T>* left_tree, BinaryNode<T>* parent) {}

    BinaryNode<T>* insertRightTree(BinaryTree<T>* right_tree, BinaryNode<T>* parent) {}

   protected:
    // update height of tree node x
    virtual size_t updateHeight(BinaryNode<T>* x) { return 0; }
    // update height of tree node x and its ancestors
    void updateHeightAbove(BinaryNode<T>* x) {}
    size_t size_;
    BinaryNode<T>* root_;
};

#endif