#include<iostream>
#include "include/BinarySearchTree.h"
#include "develop/TestTree.h"


int main() {
    try {
        TestTree::BST();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
