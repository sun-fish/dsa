#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <iostream>

#include "list/list.h"
#include "public/dictionary.h"
#include "public/entry.h"
#include "quad_list.h"

template <typename Key, typename Value>
class Skiplist : public Dictionary<Key, Value> {
   public:
    Skiplist() {
        QuadList<Entry<Key, Value>>* temp = new QuadList<Entry<Key, Value>>;
        list_.insertAsFirst(temp);
    }  // at least have one empty list node

    size_t size() { return list_.empty() ? 0 : list_.back()->data_->size_; }

    size_t height() { return list_.size(); }

    QuadListNode<Entry<Key, Value>>* search(Key k) {
        for (QuadListNode<Entry<Key, Value>>* node = list_.front()->data_->header_;;) {
            if ((node->succ_->succ_) && (node->succ_->entry_.key <= k)) {
                node = node->succ_;
            } else if (node->below_) {
                node = node->below_;
            } else {
                return node;
            }
        }
    }

    Value* get(Key k) {
        QuadListNode<Entry<Key, Value>>* node = search(k);
        return (node->pred_ && node->entry_.key == k) ? &(node->entry_.value) : nullptr;
    }

    bool put(Key k, Value v) {
        Entry<Key, Value> e = Entry<Key, Value>(k, v);
        QuadListNode<Entry<Key, Value>>* node = search(k);
        ListNode<QuadList<Entry<Key, Value>>*>* list_node = list_.back();
        QuadListNode<Entry<Key, Value>>* new_node1 = list_node->data_->insert(e, node);

        // pao ying bi
        // rand() & 1 = rand() % 2
        while (rand() & 1) {
            // find the nearest pred_ node which above node is not nullptr
            while (node->pred_ != nullptr && node->above_ == nullptr) {
                node = node->pred_;
            }

            // one of the following condition should be satisfied
            // node->pred_ == nullptr or node->above_ != nullptr

            // left top node, create a new list node
            if (node->pred_ == nullptr && node->above_ == nullptr) {
                QuadList<Entry<Key, Value>>* temp = new QuadList<Entry<Key, Value>>;
                list_.insertAsFirst(temp);
                list_.front()->data_->header_->below_ = list_node->data_->header_;
                list_node->data_->header_->above_ = list_.front()->data_->header_;
            }

            node = node->above_;
            list_node = list_node->pred_;
            // add a new new_node1 after node and above old new_node1
            new_node1 = list_node->data_->insert(e, node, new_node1);
        }

        return true;  // dictionary allow duplicated entry
    }

    bool remove(Key k) {
        QuadListNode<Entry<Key, Value>>* node = search(k);
        if (node->pred_ == nullptr || (k != node->entry_.key)) {
            return false;
        }
        ListNode<QuadList<Entry<Key, Value>>*>* list_node = list_.back();

        // climb to the highest node
        while (node->above_ != nullptr) {
            list_node = list_node->pred_;
            node = node->above_;
        }

        // from the highest node, down to the lowest, do delete
        do {
            QuadListNode<Entry<Key, Value>>* lower = node->below_;
            list_node->data_->remove(node);
            node = lower;
            list_node = list_node->succ_;
        } while (list_node->succ_ != nullptr);

        // remove the list node if the node data size is 0
        // at least have one empty list node
        while ((1 < height()) && (list_.front()->data_->size_ < 1)) {
            list_.remove(list_.front());
            list_.front()->data_->header_->above_ = nullptr;
        }
        return true;
    }

    void traverse() {
        ListNode<QuadList<Entry<Key, Value>>*>* list_node = list_.front();
        QuadList<Entry<Key, Value>>* quad_list = list_node->data_;
        QuadListNode<Entry<Key, Value>>* head = quad_list->header_;
        while (head != nullptr) {
            QuadListNode<Entry<Key, Value>>* node = head->succ_;
            quad_list = list_node->data_;
            while (node != quad_list->trailer_)
            {
                std::cout << node->entry_.key << "    ";
                node = node->succ_;
            }
            std::cout << std::endl;
            head = head->below_;
            list_node = list_node->succ_;
        }

        std::cout << "skip list traverse finished!" << std::endl;
    }

   protected:
    List<QuadList<Entry<Key, Value>>*> list_;
};

#endif