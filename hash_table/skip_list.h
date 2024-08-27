#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <assert.h>
#include <stdlib.h>

#include "public/dictionary.h"
#include "public/entry.h"
#include "list/list.h"
#include "quad_list.h"

template <typename Key, typename Value>
class Skiplist : public Dictionary<Key, Value> {
   public:
    Skiplist() {
        QuadList<Entry<Key, Value>> *temp = new QuadList<Entry<Key, Value>>;
        list_.insertAsFirst(temp);
    }

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

        while (rand() & 1) {
            while (node->pred_ && !node->above_) {
                node = node->pred_;
            }

            if (!node->pred_ && !node->above_) {
                QuadList<Entry<Key, Value>>* temp = new QuadList<Entry<Key, Value>>;
                list_.insertAsFirst(temp);
                list_.front()->data_->header_->below_ = list_node->data_->header_;
                list_node->data_->header_->above_ = list_.front()->data_->header_;
            }

            node = node->above_;
            list_node = list_node->pred_;
            new_node1 = list_node->data_->insert(e, node, new_node1);
        }

        return true;
    }

    bool remove(Key k) {
        QuadListNode<Entry<Key, Value>>* node = search(k);
        if (node->pred_ == nullptr || (k != node->entry_.key)) {
            return false;
        }
        ListNode<QuadList<Entry<Key, Value>>*>* list_node = list_.back();

        while (node->above_) {
            list_node = list_node->pred_;
            node = node->above_;
        }
        do {
            QuadListNode<Entry<Key, Value>>* lower = node->below_;
            list_node->data_->remove(node);
            node = lower;
            list_node = list_node->succ_;
        } while (list_node->succ_);
        while ((1 < height()) && (list_.front()->data_->size_ < 1)) {
            list_.remove(list_.front());
            list_.front()->data_->header_->above_ = nullptr;
        }
        return true;
    }

   protected:
    List<QuadList<Entry<Key, Value>>*> list_;
};

#endif