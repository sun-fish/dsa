#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
struct ListNode {
    T data_;
    ListNode<T>* pred_;
    ListNode<T>* succ_;
    ListNode() {}
    ListNode(T e, ListNode<T>* pred = nullptr, ListNode<T>* succ = nullptr) : data_(e), pred_(pred), succ_(succ) {}
};

#endif //LIST_NODE_H