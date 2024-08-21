#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <algorithm>

#include "binary_node.h"

template <typename T>
class BinaryTree {
   public:
    BinaryTree() : size_(0), root_(nullptr) {}
    ~BinaryTree() {
        if (0 < size_) deleteChildTree(root_);
    }

    size_t size() { return size_; }
    void set_size(size_t size) { size_ = size; }

    BinaryNode<T>* root() { return root_; }
    void set_root(BinaryNode<T>* root) { root_ = root; }

    bool empty() { return root_ != nullptr; }

    size_t deleteChildTreeNodes(BinaryNode<T>* node) {
        if (node == nullptr) return 0;
        size_t size = 1 + deleteChildTreeNodes(node->left_child()) + deleteChildTreeNodes(node->right_child());
        delete (node);
        return size;
    }

    size_t deleteChildTree(BinaryNode<T>* node) {
        if (node == nullptr) return size_;

        if (node != root_)
        {
            auto parent = node->parent();
            if (parent->left_child() == node)
                parent->set_left_child(nullptr);
            else
                parent->set_right_child(nullptr);
            updateHeightAbove(parent);
        }

        size_t sub_tree_size = deleteChildTreeNodes(node);
        size_ -= sub_tree_size;
        return sub_tree_size;
    }

    BinaryTree<T>* datachChildTree(BinaryNode<T>* node) {
        if (node == nullptr) return nullptr;

        auto parent = node->parent();
        if (parent->left_child() == node)
            parent->set_left_child(nullptr);
        else
            parent->set_right_child(nullptr);

        updateHeightAbove(parent);

        BinaryTree<T>* new_tree = new BinaryTree<T>;
        new_tree->set_root(node);
        node->set_parent(nullptr);
        new_tree->set_size(node->size());
        size_ -= new_tree->size();
        return new_tree;
    }

    BinaryNode<T>* insertLeftNode(T e, BinaryNode<T>* parent) {
        if (parent == nullptr) return nullptr;
        BinaryNode<T>* left_child = new BinaryNode<T>(e);
        parent->set_left_child(left_child);
        left_child->set_parent(parent);
        updateHeightAbove(left_child);
        ++size_;
        return parent->left_child();
    }

    BinaryNode<T>* insertRightNode(T e, BinaryNode<T>* parent) {
        if (parent == nullptr) return nullptr;
        BinaryNode<T>* right_child = new BinaryNode<T>(e);
        parent->set_right_child(right_child);
        right_child->set_parent(parent);
        updateHeightAbove(right_child);
        ++size_;
        return parent->right_child();
    }

    BinaryNode<T>* insertLeftTree(BinaryTree<T>*& left_tree, BinaryNode<T>* parent) {
        if (left_tree == nullptr || parent == nullptr) return nullptr;
        size_ += left_tree->size();
        parent->set_left_child(left_tree->root());
        parent->left_child()->set_parent(parent);
        updateHeightAbove(parent);

        left_tree->set_root(nullptr);
        left_tree->set_size(0);
        delete left_tree;
        left_tree == nullptr;
        return parent;
    }

    BinaryNode<T>* insertRightTree(BinaryTree<T>*& right_tree, BinaryNode<T>* parent) {
        if (right_tree == nullptr || parent == nullptr) return nullptr;
        size_ += right_tree->size();
        parent->set_right_child(right_tree->root());
        parent->right_child()->set_parent(parent);
        updateHeightAbove(parent);

        right_tree->set_root(nullptr);
        right_tree->set_size(0);
        delete right_tree;
        right_tree == nullptr;
        return parent;
    }

   protected:
    virtual size_t updateHeight(BinaryNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        size_t left_height = node->left_child() != nullptr ? 1 + node->left_child()->height() : 0;
        size_t right_height = node->right_child() != nullptr ? 1 + node->right_child()->height() : 0;
        node->set_height(std::max<int>(left_height, right_height));
        return node->height();
    }

    void updateHeightAbove(BinaryNode<T>* node) {
        while (node != nullptr) {
            updateHeight(node);
            node = node->parent();
        }
    }
    size_t size_;
    BinaryNode<T>* root_;
};

#endif