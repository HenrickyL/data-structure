#include <iostream>
#include "include/BinarySearchTree.h"
using namespace std;

int main() {
    Perikan::TREE::BinarySearchTree t;

    try {
        std::cout << "Max key: " << t.max() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    t.add(5);
    t.add(2);
    t.add(1);
    t.add(3);

    t.add(8);
    t.add(6);
    t.add(9);
    t.add(7);

    std::cout << t.to_string() << std::endl;
    t.print();
    std::cout << "Count: " << t.countNodes() << std::endl;
    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
    std::cout << "Count Intern Leafs: " << t.countInterNodes() << std::endl;
    std::cout << "Max key: " << t.max() << std::endl;


    int key = 3;
    std::cout << "Finding key [" << key << "] ..." << std::endl;
    bool exist = t.find(key);
    std::cout << "Node: " << exist << std::endl;



    t.removeLeafs();
    std::cout << t.to_string() << std::endl;
    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
    t.clear();
    std::cout << "Count: " << t.countNodes() << std::endl;

    return 0;
}