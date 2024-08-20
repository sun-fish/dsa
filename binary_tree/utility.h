#ifndef BINARY_TREE_UTILITY
#define BINARY_TREE_UTILITY

#include <assert.h>

template <typename T>
class BinaryNodeUtility {
   public:
    static bool isRoot(T node) { return node.parent() == nullptr; }
    static bool isLeftChild(T node) { return !isRoot(node) && node.parent()->left_child() == &node; }
    static bool isRightChild(T node) { return !isRoot(node) && node.parent()->right_child() == &node; }
    static bool hasParent(T node) { return !isRoot(node); }
    static bool hasLeftChild(T node) { return node.left_child() != nullptr; }
    static bool hasRightChild(T node) { return node.right_child() != nullptr; }
    static bool hasChild(T node) { return hasLeftChild(node) || hasRightChild(node); }
    static bool hasBothChild(T node) { return hasLeftChild(node) && hasRightChild(node); }
    static bool isLeaf(T node) { return !hasChild(node); }
    static T* sibling(T node) {
        if (isRoot(node))
            return nullptr;
        else
            return isLeftChild(node) ? node.parent()->right_child() : node.parent()->left_child();
    }
    static T* uncle(T node) {
        if (isRoot(node))
            return nullptr;
        else
            return sibling(*(node.parent()));
    }
};

#endif  // !BINARY_TREE_UTILITY