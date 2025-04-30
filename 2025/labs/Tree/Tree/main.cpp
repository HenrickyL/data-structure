#include <iostream>
#include "include/BinarySearchTree.h"
using namespace std;
#include<vector>
#include<sstream>


void TestRemove() {
    Perikan::TREE::BinarySearchTree t;
    t.add(5);
    t.add(3);
    t.add(2);
    t.add(4);
    t.add(8);
    t.add(7);
    t.add(6);
    t.add(9);
    std::cout << t.to_string() << std::endl;
    int removeKey = 5;
    t.remove(removeKey);
    std::cout << "Remove: " << removeKey << std::endl;
    std::cout << t.to_string() << std::endl;
}

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
    std::cout << "Count: " << t.size() << std::endl;
    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
    std::cout << "Count Intern Leafs: " << t.countInterNodes() << std::endl;
    std::cout << "Max key: " << t.max() << std::endl;

    int removeKey = 8;
    t.remove(removeKey);
    std::cout << "Remove: "<< removeKey << std::endl;
    std::cout << t.to_string() << std::endl;


    int key = 3;
    std::cout << "Finding key [" << key << "] ..." << std::endl;
    bool exist = t.find(key);
    std::cout << "Node: " << exist << std::endl;



    t.removeLeafs();
    std::cout << t.to_string() << std::endl;
    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
    t.clear();
    std::cout << "Count: " << t.size() << std::endl;
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

void test2() {
    int nLines;
    std::cin >> nLines;
    std::cin.ignore();

    std::vector<Perikan::TREE::BinarySearchTree*> trees;

    for (int i = 0; i < nLines; i++) {
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
        std::string s = i == 0 ? "" : "\n";
        std::cout << s<<"Case " << i + 1 << ":" << std::endl;
        t->printBFS();
        delete t;
    }
}

void test3() {
    int key;
    string line;
    Perikan::TREE::BinarySearchTree tree;

    getline(cin, line);
    stringstream ss(line);

    while (ss >> key) {
        tree.add(key);
    }

    cout << tree.height() << " " << tree.size() << endl;
}


int main() {
    try {
        //Test();
        //test1();
        //test2();
        //test3();
        TestRemove();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
