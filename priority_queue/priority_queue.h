#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <assert.h>

#include "array/array.h"
#include "binary_tree/binary_tree.h"
#include "utility.h"

template <typename T>
class PriorityQueue {
   public:
    virtual void insert(T) = 0;
    virtual T getMax() = 0;
    virtual void delMax() = 0;
};

// complete binary heap
template <typename T>
class PriorityQueueArray : public PriorityQueue<T>, public Array<T> {
   public:
    PriorityQueueArray(){};
    PriorityQueueArray(T* vector, size_t size) {
        Array<T>::copyFrom(vector, 0, size);
        PriorityQueueArrayUtility<T>::heapify(elements_, size_);
    }
    virtual void insert(T val) override {
        pushBack(val);
        PriorityQueueArrayUtility<T>::heapNodeUp(elements_, size() - 1);
    }
    virtual T getMax() override { return elements_[0]; }
    virtual void delMax() override {
        if (empty()) return;
        std::swap(elements_[0], elements_[--size_]);
        if (empty()) return;
        PriorityQueueArrayUtility<T>::heapNodeDown(elements_, size(), 0);
    }
};

// leftist heap
template <typename T>
class PriorityQueueBinaryTree : public PriorityQueue<T>, public BinaryTree<T> {
   public:
    PriorityQueueBinaryTree() {}

    PriorityQueueBinaryTree(PriorityQueueBinaryTree* heap1, PriorityQueueBinaryTree* heap2) {
        root_ = merge(heap1->root_, heap2->root_);
        size_ = heap1->size_ + heap2_->size_;
        heap1->root_ = heap2->root_ = nullptr;
        heap1->size_ = heap2->size_ = 0;
    }

    PriorityQueueBinaryTree(T* elements, int n) {
        // if use floyd algorithm, key point is when create heap check children's null path length and adjust
        for (int i = 0; i < n; i++) {
            insert(elements[i]);
        }
    }

    virtual T getMax() override {
        if (root_ == nullptr) {
            T res;
            return res;
        }
        return root_->data();
    }

    virtual void insert(T val) override {
        BinaryNode<T>* new_heap_node = new BinaryNode<T>(val);
        root_ = merge(root_, new_heap_node);
        root_->set_parent(nullptr);
        ++size_;
    }

    virtual void delMax() override {
        if (root_ == nullptr) return;
        BinaryNode<T>* left_heap = root_->left_child();
        BinaryNode<T>* right_heap = root_->right_child();
        delete root_;
        --size_;
        root_ = merge(left_heap, right_heap);
        if (root_) root_->set_parent(nullptr);
    }

    static BinaryNode<T>* merge(BinaryNode<T>* left_heap_root, BinaryNode<T>* right_heap_root) {
        if (left_heap_root == nullptr) return right_heap_root;
        if (right_heap_root == nullptr) return left_heap_root;

        // make sure the value of left heap root is not less than the value of right heap root
        if (left_heap_root->data() < right_heap_root->data()) {
            BinaryNode<T>* temp = left_heap_root;
            left_heap_root = right_heap_root;
            right_heap_root = temp;
        }

        BinaryNode<T>* new_heap_root = merge(left_heap_root->right_child(), right_heap_root);
        left_heap_root->set_right_child(new_heap_root);
        new_heap_root->set_parent(left_heap_root);

        // hold left side(left child null path length is not less than the right child null path length)
        if (left_heap_root->left_child() == nullptr ||
            left_heap_root->left_child()->null_path_length() < new_heap_root->null_path_length()) {
            left_heap_root->set_right_child(left_heap_root->left_child());
            left_heap_root->set_left_child(new_heap_root);
        }

        BinaryNode<T>* left_child = left_heap_root->left_child();
        BinaryNode<T>* right_child = left_heap_root->right_child();
        left_heap_root->set_null_path_length(right_child == nullptr ? 1 : right_child->null_path_length() + 1);

        return left_heap_root;
    }
};

#endif