#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <assert.h>
#include <stdlib.h>

#include "public/dictionary.h"
#include "public/entry.h"
#include "quad_list.h"

namespace Chen {
template <typename T>
struct ListNode {
    T data_;
    ListNode<T>* pred_;
    ListNode<T>* succ_;
    ListNode() {}
    ListNode(T e, ListNode<T>* pred = nullptr, ListNode<T>* succ = nullptr) : data_(e), pred_(pred), succ_(succ) {}
};

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

    ListNode<T>* insertBefore(ListNode<T>* node, T& e) {
        ListNode<T>* new_node = new ListNode<T>(e);

        new_node->pred_ = node->pred_;
        new_node->succ_ = node;

        node->pred_->succ_ = new_node;
        node->pred_ = new_node;

        return new_node;
    }

    ListNode<T>* insertAfter(ListNode<T>* node, T& e) {
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

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    ListNode<T>* first() const { return header_->succ_; }
    ListNode<T>* last() const { return trailer_->pred_; }

    ListNode<T>* insertAsFirst(T& e) {
        ++size_;
        return insertAfter(header_, e);
    }

    ListNode<T>* insertAsLast(T& e) {
        ++size_;
        return insertBefore(trailer_, e);
    }

    ListNode<T>* insert(ListNode<T>* node, T& e) {
        assert(node != header_ || node != trailer_);
        ++size_;
        return insertAfter(node, e);
    }

    ListNode<T>* insert(T& e, ListNode<T>* node) {
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

    ListNode<T>* find(T& e) {
        ListNode<T>* current_node = header_->succ_;
        while (current_node != trailer_) {
            if (e == current_node->data_) {
                return current_node;
            }
        }
        return nullptr;
    }

    ListNode<T>* front() { return header_->succ_; }
    ListNode<T>* back() { return trailer_->pred_; }
};

}  // namespace Chen

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
        Chen::ListNode<QuadList<Entry<Key, Value>>*>* list_node = list_.back();
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
        Chen::ListNode<QuadList<Entry<Key, Value>>*>* list_node = list_.back();

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
    Chen::List<QuadList<Entry<Key, Value>>*> list_;
};

#endif