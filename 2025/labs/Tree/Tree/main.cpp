#include <iostream>
#include "include/BinarySearchTree.h"
using namespace std;
#include<vector>
#include<sstream>
void Test() {
    Perikan::TREE::BinarySearchTree t;

    //std::cout << "Max key: " << t.max() << std::endl;

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
}

void test1(){
    int nLines;
    std::cin >> nLines;
    std::cin.ignore();

    std::vector<Perikan::TREE::BinarySearchTree*> trees;

    for (int i=0; i < nLines; i++) {
        int qtd;
        std::cin >> qtd;
        Perikan::TREE::BinarySearchTree* t = new Perikan::TREE::BinarySearchTree();

        for (int j = 0; j < qtd; j++) {
            int x;
            std::cin >> x;
            t->add(x);
        }

        trees.push_back(t);
    }

    for (int i = 0; i < trees.size(); i++) {
        Perikan::TREE::BinarySearchTree* t = trees[i];
        std::cout << "Case " << i+1 << ":" << std::endl;
        t->printPreOrder();
        t->printInOrder();
        t->printPosOrder();
        delete t;
    }
}


int main() {
    try {
        //Test();
        test1();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
