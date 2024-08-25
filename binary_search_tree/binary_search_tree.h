#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <queue>
#include <stack>

#include "binary_tree/binary_tree.h"

template <typename T>
class BinarySearchTree : public BinaryTree<T> {
   public:
    // hot_ node is always the parent of return node if hot_ is not nullptr
    virtual BinaryNode<T>* search(const T& e) {
        if (!root_ || e == root_->data()) {
            hot_ = nullptr;
            return root_;
        }

        hot_ = root_;
        while (true) {
            BinaryNode<T>* node = (e < hot_->data()) ? hot_->left_child() : hot_->right_child();
            if (node == nullptr || e == node->data()) {
                // hot_ is the node parent
                return node;
            }
            hot_ = node;
        }
    }

    virtual BinaryNode<T>* insert(const T& e) {
        BinaryNode<T>* node = search(e);
        if (node != nullptr) {
            return node;
        }
        node = new BinaryNode<T>(e, hot_);
        if (e < hot_->data()) {
            e->set_left_child(node);
        } else {
            e->set_right_child(node);
        }
        ++size_;
        updateHeightAbove(node);
        return node;
    }

    static BinaryNode<T>* removeAt(BinaryNode<T>* node, BinaryNode<T>*& hot) {
        //native,easy for understanding solution1
        if (node->left_child() == nullptr) {
            BinaryNode<T>* right_child = node->right_child();
            node->set_data(right_child->data());
            node->set_left_child(right_child->left_child());
            node->set_right_child(right_child->right_child());
            delete right_child;
        } else if (node->right_child() == nullptr) {
            BinaryNode<T>* left_child = node->left_child();
            node->set_data(left_child->data());
            node->set_left_child(left_child->left_child());
            node->set_right_child(left_child->right_child());
            delete left_child;
        } else {
            T node_data = node->data();
            BinaryNode<T>* successive_node = node->successive();
            assert(successive_node != nullptr);
            node->set_data(successive_node->data());
            successive_node->set_data(data);
            //successive node must not exist left child
            //use successive node's right child node to replace successive node
            BinaryNode<T>* right_child = successive_node->right_child();
            hot = successive_node->parent();
            if (right_child != nullptr) {
                successive_node->set_left_child(right_child->left_child());
                successive_node->set_right_child(right_child->right_child());
                successive_node->set_data(right_child->data());
                delete right_child;
            }
        }

        return nullptr;
    }

    virtual bool remove(const T& e) {
        BinaryNode<T> * node = search(e);
        if (node == nullptr) {
            return false;
        }
        removeAt(node, hot_);
        --size_;
        updateHeightAbove(hot_);
        return true;
    }

   protected:
    BinaryNode<T>* hot_;  // hits node's parent

    /* BinaryTree<T>* connect34(BinaryTree<T>* tree11, BinaryTree<T>* tree12, BinaryTree<T>* tree13,
                                BinaryTree<T>* tree21, BinaryTree<T>* tree22, BinaryTree<T>* tree23, BinaryTree<T>*);
    BinaryTree<T>* rotateAt(BinaryTree<T>*<T> x);*/
};

#endif