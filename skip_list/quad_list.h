#ifndef QUAD_LIST_H
#define QUAD_LIST_H

#include "quad_list_node.h"

/////////////////////////////////////////////////////
//                                               ////
//                     above_                    ////
//                      /\                       ////
//                      ||                       ////
//                 _____||_____                  ////
//                |            |                 ////
//      pred_<----|QuadListNode|---->succ_       ////
//                |____________|                 ////
//                      ||                       ////
//                      ||                       ////
//                      \/                       ////
//                     below_                    ////
//                                               ////
/////////////////////////////////////////////////////

template <typename T>
class QuadList {
   public:
    QuadList() { init(); }

    ~QuadList() {
        clear();
        delete header_;
        delete trailer_;
    }

    void init() {
        header_ = new QuadListNode<T>;
        trailer_ = new QuadListNode<T>;
        header_->succ_ = trailer_;
        header_->pred_ = nullptr;
        trailer_->pred_ = header_;
        trailer_->succ_ = nullptr;
        header_->above_ = trailer_->above_ = nullptr;
        header_->below_ = trailer_->below_ = nullptr;
        size_ = 0;
    }

    int clear() {
        int old_size = size_;
        while (0 < size_) {
            remove(header_->succ_);
        }
        return old_size;
    }

    T remove(QuadListNode<T>* p) {
        p->pred_->succ_ = p->succ_;
        p->succ_->pred_ = p->pred_;
        --size_;
        T e = p->entry_;
        delete p;
        return e;
    }

    // insert e as the successive of pred_node and the above node of below_node
    // key point: pred_node != nullptr and new_node->above_ == nullptr
    QuadListNode<T>* insert(T& e, QuadListNode<T>* pred_node, QuadListNode<T>* below_node = nullptr) {
        assert(pred_node != nullptr);

        ++size_;
        QuadListNode<T>* new_node = new QuadListNode<T>(e);
        QuadListNode<T>* succ_node = nullptr;
        succ_node = pred_node->succ_;
        pred_node->succ_ = new_node;
        if (succ_node != nullptr) {
            succ_node->pred_ = new_node;
        }
        new_node->succ_ = succ_node;

        new_node->above_ = nullptr;
        if (below_node) {
            below_node->above_ = new_node;
        }
        new_node->below_ = below_node;
        return new_node;
    }

    template <typename VST>
    void traverse(VST& visit) {
        QuadListNode<T>* p = header_;
        while ((p = p->succ_) != trailer_) {
            visit(p->data);
        }
    }

    size_t size_;
    QuadListNode<T>*header_, *trailer_;
};

#endif