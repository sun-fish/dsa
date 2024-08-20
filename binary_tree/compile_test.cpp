#include <assert.h>

#include "binary_node.h"
#include "binary_tree.h"
#include "utility.h"

bool binary_tree_test() {
    BinaryNode<int> int_node;
    int_node.set_data(1);
    int_node.set_height(0);
    int_node.set_left_child(nullptr);
    int_node.set_right_child(nullptr);
    int_node.set_null_path_length(1);
    int_node.set_parent(nullptr);
    int_node.set_color(RBColor::RB_RED);
    int_node.data();
    int_node.color();
    int_node.height();
    int_node.left_child();
    int_node.right_child();
    int_node.parent();
    int_node.null_path_length();
    int_node.size();
    int_node.successive();
    BinaryNode<int> test_node1(2);
    assert(int_node < test_node1);

    BinaryNodeUtility<BinaryNode<int> >::isRoot(int_node);
    BinaryNodeUtility<BinaryNode<int> >::isLeftChild(int_node);
    BinaryNodeUtility<BinaryNode<int> >::isLeaf(int_node);
    BinaryNodeUtility<BinaryNode<int> >::isRightChild(int_node);
    BinaryNodeUtility<BinaryNode<int> >::hasBothChild(int_node);
    BinaryNodeUtility<BinaryNode<int> >::hasChild(int_node);
    BinaryNodeUtility<BinaryNode<int> >::hasLeftChild(int_node);
    BinaryNodeUtility<BinaryNode<int> >::hasRightChild(int_node);
    BinaryNodeUtility<BinaryNode<int> >::hasParent(int_node);
    BinaryNodeUtility<BinaryNode<int> >::sibling(int_node);
    BinaryNodeUtility<BinaryNode<int> >::uncle(int_node);

    BinaryTree<int> int_tree;
    int_tree.set_root(&int_node);
    auto int_node1 = int_tree.insertLeftNode(2, &int_node);
    auto int_node2 = int_tree.insertRightNode(3, &int_node);
    int_tree.datachChildTree(int_node1);
    int_tree.deleteChildTree(int_node2);
    int_tree.empty();
    return true;
}