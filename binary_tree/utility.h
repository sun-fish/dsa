#ifndef BINARY_TREE_UTILITY
#define BINARY_TREE_UTILITY

#include <assert.h>

#include <iostream>
#include <queue>

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

template <typename T>
class BinaryTreeUtility {
   public:
    static void TravellingPreOrderRecursively(T* const root) {
        if (root == nullptr) return;
        std::cout << root->data() << "    ";
        TravellingPreOrderRecursively(root->left_child());
        TravellingPreOrderRecursively(root->right_child());
    }

    static void TravellingMidOrderRecursively(T* const root) {
        if (root == nullptr) return;
        TravellingMidOrderRecursively(root->left_child());
        std::cout << root->data() << "    ";
        TravellingMidOrderRecursively(root->right_child());
        return;
    }

    static void TravellingPostOrderRecursively(T* const root) {
        if (root == nullptr) return;
        TravellingPostOrderRecursively(root->left_child());
        TravellingPostOrderRecursively(root->right_child());
        std::cout << root->data() << "    ";
        return;
    }

    static void TravellingLevel(T* const root) {
        if (root == nullptr) return;
        std::cout << "data:" << root->data() << " height:" << root->height() << ",";

        std::queue<T*> help_queue;
        help_queue.push(root);
        while (!help_queue.empty()) {
            auto node = help_queue.front();
            help_queue.pop();

            if (node->left_child() != nullptr) {
                std::cout << "data:" << node->left_child()->data() << " height:" << node->left_child()->height() << ",";
                help_queue.push(node->left_child());
            }

            if (node->right_child() != nullptr) {
                std::cout << "data:" << node->right_child()->data() << " height:" << node->right_child()->height()
                          << ",";
                help_queue.push(node->right_child());
            }
        }

        std::cout << "Travel level end!" << std::endl;
        return;
    }

    static void TravellingPreOrderIteratively1(T* const root) {
        if (root == nullptr) return;
        std::cout << "Previous order iteratively1 end!" << std::endl;
        return;
    }

    static void TravellingPreOrderIteratively2(T* const root) {
        if (root == nullptr) return;
        std::cout << "Previous order iteratively2 end!" << std::endl;
        return;
    }

    static void TravellingMidOrderIteratively1(T* const root) {
        if (root == nullptr) return;
        std::cout << "Middle order iteratively1 end!" << std::endl;
        return;
    }

    static void TravellingMidOrderIteratively2(T* const root) {
        if (root == nullptr) return;
        std::cout << "Middle order iteratively3 end!" << std::endl;
        return;
    }

    static void TravellingMidPostIteratively(T* const root) {
        if (root == nullptr) return;
        std::cout << "Post order iteratively end!" << std::endl;
        return;
    }
};

#endif  // !BINARY_TREE_UTILITY