#include <iostream>

#include "binary_tree/utility.h"
#include "binary_search_tree.h"

int main(int argc, char** argv) {
    
    BinarySearchTree<int> int_search_tree;
    int_search_tree.insert(6);
    int_search_tree.insert(36);
    int_search_tree.insert(27);
    int_search_tree.insert(58);
    int_search_tree.insert(53);
    int_search_tree.insert(69);
    int_search_tree.insert(64);
    int_search_tree.insert(40);
    int_search_tree.insert(46);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderRecursively(int_search_tree.root());
    std::cout << "Middle order recursively end!" << std::endl;

    int_search_tree.remove(64);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderRecursively(int_search_tree.root());
    std::cout << "Middle order recursively end!" << std::endl;
    int_search_tree.insert(64);

    int_search_tree.remove(69);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderRecursively(int_search_tree.root());
    std::cout << "Middle order recursively end!" << std::endl;
    int_search_tree.insert(69);

    int_search_tree.remove(46);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderRecursively(int_search_tree.root());
    std::cout << "Middle order recursively end!" << std::endl;
    int_search_tree.insert(46);

    int_search_tree.remove(40);
    BinaryTreeUtility<BinaryNode<int>>::TravellingMidOrderRecursively(int_search_tree.root());
    std::cout << "Middle order recursively end!" << std::endl;
    int_search_tree.insert(40);

    BinarySearchTree<int> int_search_tree2;
    int_search_tree.insert(6);
    int_search_tree.remove(6);

    BinarySearchTree<int> int_search_tree3;
    int_search_tree.remove(6);


    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}