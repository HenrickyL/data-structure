#include <iostream>
#include "PriorityQueue.h"
#include "AVL.h"

using namespace std;


void testAVL(){
    EDA::AVL<int> tree;

    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(11);
    tree.Insert(17);
    tree.Insert(4);
    tree.Insert(6);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(22);
    tree.Insert(3);
    tree.Insert(50);
    tree.Print();

    tree.Remove(4);
    tree.Print();

    cout << endl;
}

void testPQueue(){
    EDA::PriorityQueue<int> p;
    p.First();
}


int main(){
    testAVL();
    return 0;
}