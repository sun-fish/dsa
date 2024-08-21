#include <iostream>

#include "binary_tree.h"
#include "utility.h"

int main(int argc, char** argv)
{
    BinaryNode<int> *node1 = new BinaryNode<int>();
    node1->set_data(1);

    BinaryTree<int> tree;
    tree.set_root(node1);

    auto node2 = tree.insertLeftNode(2, node1);
    auto node3 = tree.insertRightNode(3, node1);

    auto node4 = tree.insertLeftNode(4, node2);
    auto node5 = tree.insertRightNode(5, node2);

    auto node6 = tree.insertLeftNode(6, node3);

    auto node7 = tree.insertLeftNode(7, node4);
    auto node8 = tree.insertRightNode(8, node4);

    auto node9 = tree.insertLeftNode(9, node6);
    auto node10 = tree.insertRightNode(10, node6);


    BinaryTreeUtility<BinaryNode<int>>::TravellingLevel(node1);
    BinaryTreeUtility<BinaryNode<int>>::TravellingPreOrderRecursively(node1);
    std::cout << "Previous order recursively end!" << std::endl;
    BinaryTreeUtility<BinaryNode<int>>::TravellingPreOrderIteratively1(node1);
    BinaryTreeUtility<BinaryNode<int>>::TravellingPreOrderIteratively2(node1);
    std::cout << std::endl;

    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderRecursively(node1);
    std::cout << "Middle order recursively end!" << std::endl;
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderIteratively1(node1);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderIteratively2(node1);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderIteratively3(node1);
    std::cout << std::endl;

    BinaryTreeUtility<BinaryNode<int>>::TravellingPostOrderRecursively(node1);
    std::cout << "Post order recursively end!" << std::endl;
    BinaryTreeUtility<BinaryNode<int>>::TravellingPostIteratively(node1);

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}