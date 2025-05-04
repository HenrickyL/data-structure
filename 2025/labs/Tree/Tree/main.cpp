#include <iostream>
#include "include/AVLTree.h"
#include "include/BinarySearchTree.h"
#include "include/Set.h"


using namespace std;
#include<vector>
#include<sstream>


void TestSet() {
    std::cout << "=== TESTING SET OPERATIONS ===" << std::endl;

    // Criando conjuntos de teste
    Set setA, setB;

    // Inserindo elementos
    for (int i = 1; i <= 5; i++) setA.insert(i);
    for (int i = 3; i <= 7; i++) setB.insert(i);

    setA.print("Set A");
    setB.print("Set B");

    // Testando Union
    Set unionAB = Set::unionSet(setA, setB);
    unionAB.print("A union B");

    // Testando Intersection
    Set intersectAB = Set::intersection(setA, setB);
    intersectAB.print("A intersect B");

    // Testando Difference
    Set diffAB = Set::difference(setA, setB);
    diffAB.print("A - B");

    Set diffBA = Set::difference(setB, setA);
    diffBA.print("B - A");

    // Testando outras operações
    std::cout << "\nAdditional tests:" << std::endl;
    std::cout << "Minimum of A: " << setA.minimum() << std::endl;
    std::cout << "Maximum of B: " << setB.maximum() << std::endl;
    std::cout << "Size of A: " << setA.size() << std::endl;
    std::cout << "Is 4 in A? " << (setA.contains(4) ? "Yes" : "No") << std::endl;

    // Testando clear
    Set setC = setA;
    setC.print("Set C (copy of A)");
    //setC.clear();
    std::cout << "After clear, size of C: " << setC.size() << std::endl;

    std::cout << "=== TESTING COMPLETED ===" << std::endl;
}

//void TestAVL() {
//    Perikan::TREE::AVLTree<int> t;
//    int n = 11;
//    int v[11] = { 5, 7, 11, 17, 4, 6, 2, 1, 22, 3, 50 };
//    for (int i = 0; i < n; i++) {
//        t.add(v[i]);
//    }
//    
//    std::cout << t.to_string() << std::endl;
//
//    t.remove(4);
//    std::cout << t.to_string() << std::endl;
//}

//void TestRemove() {
//    Perikan::TREE::BinarySearchTree<int> t;
//    t.add(5);
//    t.add(3);
//    t.add(2);
//    t.add(4);
//    t.add(8);
//    t.add(7);
//    t.add(6);
//    t.add(9);
//    std::cout << t.to_string() << std::endl;
//    int removeKey = 5;
//    t.remove(removeKey);
//    std::cout << "Remove: " << removeKey << std::endl;
//    std::cout << t.to_string() << std::endl;
//}

//void Test() {
//    Perikan::TREE::BinarySearchTree<int> t;
//
//    //std::cout << "Max key: " << t.max() << std::endl;
//
//    t.add(5);
//    t.add(2);
//    t.add(1);
//    t.add(3);
//
//    t.add(8);
//    t.add(6, 11);
//    t.add(9);
//    t.add(7);
//
//    t.printOrdered();
//
//    std::cout << "KeyMin: " << t.keyMinimum() << std::endl;
//    std::cout << "KeyMax: " << t.keyMaximum() << std::endl;
//
//    int keyBase = 6;
//    std::cout << "BaseKey: " << keyBase << std::endl;
//    std::cout << "Successor: " << t.keySuccessor(6) << std::endl;
//    std::cout << "Predecessor: " << t.keyPredecessor(6) << std::endl;
//
//
//
//    t.print();
//    std::cout << "Count:  " << t.size() << std::endl;
//    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
//    std::cout << "Count Intern Leafs: " << t.countInterNodes() << std::endl;
//    std::cout << "Max key: " << t.max() << std::endl;
//
//    int removeKey = 8;
//    t.remove(removeKey);
//    std::cout << "Remove: "<< removeKey << std::endl;
//    std::cout << t.to_string() << std::endl;
//
//
//    int key = 3;
//    std::cout << "Finding key [" << key << "] ..." << std::endl;
//    int findKey = t.findByValue(11);
//    std::cout << "Finding value in key [" << findKey << "] ..." << std::endl;
//    bool exist = t.find(key);
//    std::cout << "Node: " << exist << std::endl;
//
//
//
//    t.removeLeafs();
//    std::cout << t.to_string() << std::endl;
//    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
//    t.clear();
//    std::cout << "Count: " << t.size() << std::endl;
//}

//void test1(){
//    int nLines;
//    std::cin >> nLines;
//    std::cin.ignore();
//
//    std::vector<Perikan::TREE::BinarySearchTree<int>*> trees;
//
//    for (int i=0; i < nLines; i++) {
//        int qtd;
//        std::cin >> qtd;
//        Perikan::TREE::BinarySearchTree<int>* t = new Perikan::TREE::BinarySearchTree<int>();
//
//        for (int j = 0; j < qtd; j++) {
//            int x;
//            std::cin >> x;
//            t->add(x);
//        }
//
//        trees.push_back(t);
//    }
//
//    for (int i = 0; i < trees.size(); i++) {
//        Perikan::TREE::BinarySearchTree<int>* t = trees[i];
//        std::cout << "Case " << i+1 << ":" << std::endl;
//        t->printPreOrder();
//        t->printInOrder();
//        t->printPosOrder();
//        delete t;
//    }
//}
//
//void test2() {
//    int nLines;
//    std::cin >> nLines;
//    std::cin.ignore();
//
//    std::vector<Perikan::TREE::BinarySearchTree<int>*> trees;
//
//    for (int i = 0; i < nLines; i++) {
//        int qtd;
//        std::cin >> qtd;
//        Perikan::TREE::BinarySearchTree<int>* t = new Perikan::TREE::BinarySearchTree<int>();
//
//        for (int j = 0; j < qtd; j++) {
//            int x;
//            std::cin >> x;
//            t->add(x);
//        }
//
//        trees.push_back(t);
//    }
//
//    for (int i = 0; i < trees.size(); i++) {
//        Perikan::TREE::BinarySearchTree<int>* t = trees[i];
//        std::string s = i == 0 ? "" : "\n";
//        std::cout << s<<"Case " << i + 1 << ":" << std::endl;
//        t->printBFS();
//        delete t;
//    }
//}
//
//void test3() {
//    int key;
//    string line;
//    Perikan::TREE::BinarySearchTree<int> tree;
//
//    getline(cin, line);
//    stringstream ss(line);
//
//    while (ss >> key) {
//        tree.add(key);
//    }
//
//    cout << tree.height() << " " << tree.size() << endl;
//}


int main() {
    try {
        //Test();
        //test1();
        //test2();
        //test3();
        //TestRemove(); 
        //TestAVL();
        TestSet();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
