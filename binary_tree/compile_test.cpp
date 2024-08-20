#include <assert.h>

#include "binary_node.h"
#include "binary_tree.h"

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
    BinaryNode<int> test_node1(2);
    assert(int_node < test_node1);

    BinaryTree<int> int_tree;
    int_tree.set_root(&int_node);
    int_tree.insertLeftNode(2, &int_node);
    int_tree.insertRightNode(3, &int_node);
    return true;
}