#ifndef LIST_H
#define LIST_H

#include <assert.h>

#include "list_node.h"

template <typename T>
class List {
   private:
    size_t size_;
    ListNode<T>* header_;
    ListNode<T>* trailer_;

   protected:
    void init() {
        header_ = new ListNode<T>;
        trailer_ = new ListNode<T>;
        header_->succ_ = trailer_;
        header_->pred_ = nullptr;
        trailer_->pred_ = header_;
        trailer_->succ_ = nullptr;
        size_ = 0;
    }

    size_t clear() {
        size_t oldSize = size_;
        while (0 < size_) {
            remove(header_->succ_);
        }
        return oldSize;
    }

    ListNode<T>* insertBefore(ListNode<T>* node, T const& e) {
        ListNode<T>* new_node = new ListNode<T>(e);

        new_node->pred_ = node->pred_;
        new_node->succ_ = node;

        node->pred_->succ_ = new_node;
        node->pred_ = new_node;

        return new_node;
    }

    ListNode<T>* insertAfter(ListNode<T>* node, T const& e) {
        ListNode<T>* new_node = new ListNode<T>(e);

        new_node->pred_ = node;
        new_node->succ_ = node->succ_;

        node->succ_->pred_ = new_node;
        node->succ_ = new_node;

        return new_node;
    }

   public:
    List() { init(); }
    ~List() {
        clear();
        delete header_;
        delete trailer_;
    }

    size_t size() { return size_; }
    bool empty() { return size_ == 0; }

    ListNode<T>* insertAsFirst(T const& e) {
        ++size_;
        return insertAfter(header_, e);
    }

    ListNode<T>* insertAsLast(T const& e) {
        ++size_;
        return insertBefore(trailer_, e);
    }

    ListNode<T>* insert(ListNode<T>* node, T const& e) {
        assert(node != header_ || node != trailer_);
        ++size_;
        return insertAfter(node, e);
    }

    ListNode<T>* insert(T const& e, ListNode<T>* node) {
        assert(node != header_ || node != trailer_);
        ++size_;
        return insertBefore(node, e);
    }

    T remove(ListNode<T>* node) {
        assert(node != header_ || node != trailer_);
        T e = node->data_;
        ListNode<T>* succ_node = node->succ_;
        ListNode<T>* pred_node = node->pred_;
        pred_node->succ_ = succ_node;
        succ_node->pred_ = pred_node;
        delete node;
        --size_;
        return e;
    }

    ListNode<T>* find(T const& e) {
        ListNode<T>* current_node = header_->succ_;
        while (current_node != trailer_) {
            if (e == current_node->data_) {
                return current_node;
            }
            current_node = current_node->succ_;
        }
        return nullptr;
    }

    ListNode<T>* front() { return header_->succ_; }
    ListNode<T>* back() { return trailer_->pred_; }
};

#endif  // !LIST_H