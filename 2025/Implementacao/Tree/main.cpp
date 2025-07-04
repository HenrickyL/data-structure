#include<iostream>
#include "include/BinarySearchTree.h"
#include "develop/TestTree.h"
#include "develop/TestHash.h"


int main() {
    try {
        /*TestTree::Node_();
        TestTree::BST();
        TestTree::AVL();
        TestTree::RB();*/

        TestHash::ChainedHash();
        TestHash::OpenAddressHash();

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
