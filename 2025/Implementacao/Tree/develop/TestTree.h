#ifndef TEST_TREE_H
#define TEST_TREE_H

#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"
#include "../include/RBTree.h"


#include<iostream>
#include<string>
using namespace Perikan::TREE;

class TestTree {

public:

    static void Node_() {
        Node<int> node(1,1);
        std::cout << "> Node sizeof: " << sizeof(node) << std::endl;

        AVLNode<int> avlNode(1, 1);
        std::cout << "> AVLNode sizeof: " << sizeof(avlNode) << std::endl;

        RBNode<int> rbNode(1, 1);
        std::cout << "> rbNode sizeof: " << sizeof(rbNode) << std::endl;
        std::cout << "----------------\n\n";
    }

	static void BST() {
        BinarySearchTree<int> t;
        std::cout << "sizeof( BinarySearchTree<int> ): " << sizeof(BinarySearchTree<int>) << std::endl;
        std::cout << "sizeof( BinarySearchTree<string> ): " << sizeof(BinarySearchTree<std::string>) << std::endl;


        std::cout << "> BST sizeof tree: " << sizeof(t) << std::endl;

        //std::cout << "Max key: " << t.max() << std::endl;

        t.add(5,1);
        t.add(2,2);
        t.add(1,3);
        t.add(3,4);

        t.add(8,5);
        t.add(6,6);
        t.add(9,7);
        t.add(7,8);
        std::cout << "> BST sizeof tree: " << sizeof(t) << std::endl;


        t.printOrdered();

        std::cout << "KeyMin: " << t.keyMinimum() << std::endl;
        std::cout << "KeyMax: " << t.keyMaximum() << std::endl;
        std::cout << "height: " << t.height() << std::endl;


        int keyBase = 6;
        std::cout << "BaseKey: " << keyBase << std::endl;
        std::cout << "Successor: " << t.keySuccessor(6) << std::endl;
        std::cout << "Predecessor: " << t.keyPredecessor(6) << std::endl;



        t.print();
        std::cout << "Count:  " << t.size() << std::endl;
        std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
        std::cout << "Count Intern Leafs: " << t.countInterNodes() << std::endl;
        std::cout << "Max key: " << t.max() << std::endl;

        int removeKey = 8;
        t.remove(removeKey);
        std::cout << "Remove: " << removeKey << std::endl;
        std::cout << t.to_string() << std::endl;


        int key = 3;
        std::cout << "Finding key [" << key << "] ..." << std::endl;
        //int findKey = t.findByValue(11);
        //std::cout << "Finding value in key [" << findKey << "] ..." << std::endl;
        bool exist = t.contain(key);
        std::cout << "Node: " << exist << std::endl;



        t.removeLeafs();
        std::cout << t.to_string() << std::endl;
        std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
        t.clear();
        std::cout << "Count: " << t.size() << std::endl;
        std::cout << "----------------\n\n";
	}


    static void AVL() {
        AVLTree<int> t;
        std::cout << "sizeof( AVLTree<int> ): " << sizeof(AVLTree<int>) << std::endl;
        std::cout << "sizeof( AVLTree<string> ): " << sizeof(AVLTree<std::string>) << std::endl;


        std::cout << "> AVLTree sizeof tree: " << sizeof(t) << std::endl;

        //std::cout << "Max key: " << t.max() << std::endl;

        t.add(5, 1);
        t.add(2, 2);
        t.add(1, 3);
        t.add(3, 4);
        t.print();
        std::cout << "> Balance: " << t.balance() << std::endl;

        t.add(8, 5);
        t.add(6, 6);
        t.add(9, 7);
        t.add(7, 8);
        std::cout << "> AVLTree sizeof tree: " << sizeof(t) << std::endl;
        std::cout << "> Balance: " << t.balance() << std::endl;

        t.print();

        std::cout << "KeyMin: " << t.keyMinimum() << std::endl;
        std::cout << "KeyMax: " << t.keyMaximum() << std::endl;
        std::cout << "height: " << t.height() << std::endl;


        int keyBase = 6;
        std::cout << "BaseKey: " << keyBase << std::endl;
        std::cout << "Successor: " << t.keySuccessor(6) << std::endl;
        std::cout << "Predecessor: " << t.keyPredecessor(6) << std::endl;



        t.print();
        std::cout << "Count:  " << t.size() << std::endl;
        std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
        std::cout << "Count Intern Leafs: " << t.countInterNodes() << std::endl;
        std::cout << "Max key: " << t.max() << std::endl;

        int removeKey = 8;
        t.remove(removeKey);
        std::cout << "Remove: " << removeKey << std::endl;
        std::cout << t.to_string() << std::endl;


        int key = 3;
        std::cout << "Finding key [" << key << "] ..." << std::endl;
        //int findKey = t.findByValue(11);
        //std::cout << "Finding value in key [" << findKey << "] ..." << std::endl;
        bool exist = t.contain(key);
        std::cout << "Node: " << exist << std::endl;



        t.removeLeafs();
        std::cout << t.to_string() << std::endl;
        std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
        t.clear();
        std::cout << "Count: " << t.size() << std::endl;
        std::cout << "----------------\n\n";
    }

    static void RB() {
        RBTree<int> t;
        std::cout << "sizeof( RBTree<int> ): " << sizeof(RBTree<int>) << std::endl;
        std::cout << "sizeof( RBTree<string> ): " << sizeof(RBTree<std::string>) << std::endl;

        int values[] = {10, 20, 30, 15, 25, 5, 1, 6, 12, 18, 17, 19};
        for (int value : values) {
            t.add(value, 1);
        }
        t.print();

        std::cout << "----------------\n\n";
    }


};



#endif // !TEST_TREE_H
